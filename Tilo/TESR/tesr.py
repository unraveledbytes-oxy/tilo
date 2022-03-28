from argparse import ArgumentParser
import os
import sys
import zlib
import math
import tarfile
import io
import numpy as np
from matplotlib import pyplot as plt
from matplotlib import widgets as pltw
import collections
import struct
from PIL import Image

channel_types = "GrgbaBxyzSsdfEezutc"
channel_type_names = {
    "G": "GRAY",
    "r": "RED",
    "g": "GREEN",
    "b": "BLUE",
    "a": "ALPHA",
    "B": "BUMP",
    "x": "NORMAL_X",
    "y": "NORMAL_Y",
    "z": "NORMAL_Z",
    "S": "SPECULAR_GRAYSCALE",
    "s": "SPECULAR_RED",
    "d": "SPECULAR_GREEN",
    "f": "SPECULAR_BLUE",
    "E": "EMISSION_GRAYSCALE",
    "e": "EMISSION_RED",
    "z": "EMISSION_GREEN",
    "u": "EMISSION_BLUE",
    "t": "TRANSMISSION",
    "c": "CUSTOM"
}

channel_type_letters = dict()

for key, value in channel_type_names.items():
    channel_type_letters[value] = key

parser = ArgumentParser()
parser.add_argument("-v", "--view", metavar="FILE")
parser.add_argument("-e", "--encode", metavar="FILE")
parser.add_argument("-d", "--decode", metavar="FILE")
parser.add_argument("-o", "--output", metavar="FILE")
parser.add_argument("-f", "--fps")
args = vars(parser.parse_args("-e intro -o intro/out.tesr -f 60".split()))
action_counter = 0
if args["view"] is not None:
    action_counter += 1
    if args["output"] is not None or args["fps"] is not None:
        action_counter += 1
    action = "view"
if args["decode"] is not None and args["output"] is not None:
    action_counter += 1
    if args["fps"] is not None:
        action_counter += 1
    action = "decode"
if args["encode"] is not None and args["output"] is not None and args["fps"] is not None:
    action_counter += 1
    action = "encode"

if action_counter < 1:
    print("Not enough arguments specified")
    sys.exit()
elif action_counter > 1:
    print("Too many arguments specified")
    sys.exit()

def channel_letter_from_file_name(file_name: str) -> str:
    if file_name[0] == "c":
        return "c" + str(int(file_name[1:3], 16))
    else:
        return file_name[0]

def frame_number_from_file_name(file_name: str) -> int:
    if file_name[0] == "c":
        return int(file_name[4:], 16)
    else:
        return int(file_name[1:], 16)
    
def bit_depth_from_file_name(file_name: str, channel_info) -> int:
    try:
        return channel_info[channel_letter_from_file_name(file_name)]
    except IndexError:
        print("Corrupted channel data")
        sys.exit()
    
def channel_type_name_from_file_name(file_name: str) -> str:
    try:
        return channel_type_names[channel_letter_from_file_name(file_name)]
    except IndexError:
        print("Corrupted channel data")
        sys.exit()

def open_tesr(arg: str):
    if not os.path.isfile(arg):
        print("The specified file does not exist")
        sys.exit()

    with open(arg, "rb") as file:
        content = file.read()

    if content[0:4] != b"TESR":
        print("File is corrupted")
        sys.exit()

    if int(content[4]) != 1 or int(content[5]) != 0:
        print("Unsupported version")
        sys.exit()

    width = int.from_bytes(content[6:10], "big", signed=False)
    height = int.from_bytes(content[10:14], "big", signed=False)
    fps = struct.unpack("f", content[14:18])[0]
    frame_count = int.from_bytes(content[18:22], "big", signed=False)
    channels = int(content[22])
    
    bit_depth_bytes = math.ceil(channels / 8)
    bit_depth = []
    for i in range(bit_depth_bytes):
        bit_depth.append(int(content[23 + i]))
        
    channel_info = dict()
    i = 0
    custom_counter = 0
    while True:
        tmp = int(content[23 + bit_depth_bytes + i])
        d = 16 if (bit_depth[i // 8] & ((1 << 8) >> (i % 8))) != 0 else 8
        
        try:
            if tmp == 0xff:
                channel_letter = "c"
            else:
                channel_letter = channel_types[tmp]
        except IndexError:
            print("Corrupted channel information")
            sys.exit()
            
        if channel_letter == "c":
            i += 1
            custom_counter += 1
            channel_letter += str(int(content[23 + bit_depth_bytes + i]))
        channel_info[channel_letter] = d
        i += 1
        if i == channels + custom_counter:
            break
    
    file_like_object = io.BytesIO(content[23 + bit_depth_bytes + channels + custom_counter:])
    tar = tarfile.open(fileobj=file_like_object, mode="r:gz")
    tar_names = tar.getnames()
    tar_files = dict()
    i = 0
    for member in tar.getmembers():
        f = tar.extractfile(member)
        if f is not None:
            dtype = "uint8" if bit_depth_from_file_name(tar_names[i], channel_info) == 8 else "uint16"
            tar_files[tar_names[i]] = np.reshape(np.frombuffer(f.read()[:(width + 1) * height], dtype=dtype), (height, width + 1))
        else:
            tar_files[tar_names[i]] = None
        i += 1

    animation = dict()
    for ch in channel_info:
        dtype = dtype = np.uint8 if channel_info[ch] == 8 else np.uint16
        animation[ch] = np.empty((frame_count, height, width), dtype=dtype)
        
    for file_name, file_content in tar_files.items():
        dtype = dtype = "uint8" if bit_depth_from_file_name(file_name, channel_info) == 8 else "uint16"
        ch = channel_letter_from_file_name(file_name)
        frame = frame_number_from_file_name(file_name)
        for idx, item in enumerate(file_content):
            # LITERAL
            if item[0] == 0:
                animation[ch][frame][idx] = item[1:]
            # LEFT
            elif item[0] == 1:
                tmp = [item[1]]
                for i in range(1, width):
                    tmp.append((item[i + 1] + tmp[i - 1]) % (2 ** bit_depth_from_file_name(file_name, channel_info)))
                animation[ch][frame][idx] = tmp[:]
            # RIGHT
            elif item[0] == 2:
                item_r = item[1:]
                item_r = np.flip(item_r)
                item_r = np.insert(item_r, 0, item[0])
                tmp = [item_r[1]]
                for i in range(1, width):
                    tmp.append((item_r[i + 1] + tmp[i - 1]) % (2 ** bit_depth_from_file_name(file_name, channel_info)))
                tmp = np.flip(tmp)
                animation[ch][frame][idx] = tmp[:]
            # TOP
            elif item[0] == 3:
                tmp = [item[1]]
                if idx == 0:
                    line_above = np.zeros(width, dtype=dtype)
                else:
                    line_above = animation[ch][frame][idx - 1]
                for i in range(1, width):
                    tmp.append((item[i + 1] + line_above[i]) % (2 ** bit_depth_from_file_name(file_name)))
                animation[ch][frame][idx] = tmp[:]
    del tar_files
    
    return animation, channel_info

if action == "view":
    animation, channel_info = open_tesr(args["view"])
    rgb = "r" in dict.keys(animation) and "g" in dict.keys(animation) and "b" in dict.keys(animation) and channel_info["r"] == channel_info["g"] == channel_info["b"]
    rows_and_cols = math.ceil(math.sqrt(len(animation) + (1 if rgb else 0)))
    prev_button = None
    next_button = None
    fig = None
    axs = None

    def prev_clicked(i: int) -> None:
        if i - 1 >= 0:
            try:
                animation[list(dict.keys(animation))[0]][i - 1]
                display_frame(i - 1)
            except IndexError:
                pass

    def next_clicked(i: int) -> None:
        try:
            animation[list(dict.keys(animation))[0]][i + 1]
            display_frame(i + 1)
        except IndexError:
            pass
    
    def display_frame(i: int) -> None:
        global prev_button
        global next_button
        global fig
        global axs
        plt.close()
        fig, axs = plt.subplots(rows_and_cols + 1, rows_and_cols, constrained_layout=True)
        flat_axs = axs.flatten()
        prev_button = pltw.Button(plt.axes([0.1, 0.1, 0.35, 0.1]), 'Prev')
        next_button = pltw.Button(plt.axes([0.55, 0.1, 0.35, 0.1]), 'Next')
        for idx, item in enumerate(animation):
            axs_id = list(channel_info.keys()).index(item)
            flat_axs[axs_id].imshow(animation[item][i], interpolation="nearest", cmap="gray", vmin=0, vmax=2 ** channel_info[item])
            flat_axs[axs_id].axis("off")
            flat_axs[axs_id].set_title(channel_type_name_from_file_name(item))
        if rgb:
            flat_axs[-rows_and_cols - 1].imshow(np.dstack((animation["r"][i], animation["g"][i], animation["b"][i])).squeeze(), interpolation="nearest", vmin=0, vmax=2 ** channel_info["r"])
            flat_axs[-rows_and_cols - 1].axis("off")
            flat_axs[-rows_and_cols - 1].set_title("RGB")
        for j in range(1, rows_and_cols + 1):
            flat_axs[-j].axis("off")
        prev_button.on_clicked(lambda *args: prev_clicked(i))
        next_button.on_clicked(lambda *args: next_clicked(i))
        pltw.TextBox(plt.axes([0.45, 0.1, 0.1, 0.1]), "", initial=str(i))
        plt.show()

    display_frame(0)
elif action == "encode":
    def is_int(val: str) -> bool:
        try:
            int(val)
            return True
        except ValueError:
            return False
    
    dir_name = args["encode"]
    output_file_name = args["output"]
    try:
        fps = float(args["fps"])
    except ValueError:
        print("FPS must be a number")
        sys.exit()
    if not os.path.isdir(dir_name):
        print("The specified directory does not exist")
        sys.exit()

    dirs = [os.path.join(dir_name, d) for d in os.listdir(dir_name) if os.path.isdir(os.path.join(dir_name, d)) and (d == "RGB" or d == "RGBA" or d in dict.keys(channel_type_letters) or (d.contains("CUSTOM") and len(d.split("CUSTOM")) == 2 and is_int(d.split("CUSTOM")[1])))]
    width = None
    height = None
    frame_count = None
    animation = None
    dtypes = dict()
    for dir in dirs:
        channel_name = dir.split(os.path.sep)[-1]
        channel_files = [os.path.join(dir, f) for f in os.listdir(dir) if os.path.isfile(os.path.join(dir, f)) and f.endswith(".png") and is_int(f.split(".")[0])]
        if frame_count is None:
            frame_count = len(channel_files)
        elif len(channel_files) != frame_count:
            print("All channels must have the same number of frames")
            sys.exit()
        for channel_file in channel_files:
            frame = int(channel_file.split(os.path.sep)[-1].split(".")[0]) - 1
            print(frame)
            with Image.open(channel_file) as img:
                if animation is None:
                    width, height = img.size
                    animation = dict()
                elif img.size != (width, height):
                    print("All frames must have the same dimensions")
                    sys.exit()

                dtype = np.uint8 if img.mode == "RGB" else np.uint16
                dtypes[channel_name] = dtype
                if "RGB" in channel_name and "RED" not in dict.keys(animation):
                    animation["RED"] = np.empty((frame_count, height, width), dtype=dtype)
                    animation["GREEN"] = np.empty((frame_count, height, width), dtype=dtype)
                    animation["BLUE"] = np.empty((frame_count, height, width), dtype=dtype)
                    if channel_name == "RGBA":
                        animation["ALPHA"] = np.empty((frame_count, height, width), dtype=dtype)
                elif channel_name not in dict.keys(animation):
                    animation[channel_name] = np.empty((frame_count, height, width), dtype=dtype)
                
                if channel_name == "RGB":
                    animation["RED"][frame], animation["GREEN"][frame], animation["BLUE"][frame] = (np.reshape(c, (height, width)) for c in np.split(np.asarray(img.getdata()), 3, axis=1))
                elif channel_name == "RGBA":
                    animation["RED"][frame], animation["GREEN"][frame], animation["BLUE"][frame], animation["ALPHA"][frame] = (np.reshape(c, (height, width)) for c in np.split(np.asarray(img.getdata()), 4, axis=1))
                else:
                    animation[channel_name][frame] = np.reshape(np.split(np.asarray(img.getdata()), 3, axis=1)[0], (height, width))

    gzipped = io.BytesIO()
    tar = tarfile.open(mode="w:gz", fileobj=gzipped)
    for ch in list(dict.keys(animation)):
        tmp = np.empty((height, width + 1), dtype=dtypes[ch])
        for frame in frame_count:
            for line in height:
                tmp[0] = 0
                tmp[1:] = animation[ch][frame][line]

            tmp_bytes = tmp.tobytes()
            tmp_file = io.BytesIO(initial_bytes=tmp_bytes)
            tmp_file_info = tarfile.TarInfo(ch + hex(frame)[2:])
            tmp_file_info.size = len(tmp_bytes)
            tar.addfile(tmp_file_info, tmp_file)

    tar.close()


    






















            
