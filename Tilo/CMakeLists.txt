cmake_minimum_required(VERSION 3.10)

project(Tilo)

add_executable(Tilo main.cpp)

if (UNIX)
	target_compile_options(Tilo PRIVATE -O3 -std=c++20 -mssse3 -mavx -mavx512f -mavx512bw -mavx512vl -Wall -Wno-register)
endif (UNIX)
