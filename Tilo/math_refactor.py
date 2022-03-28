with open("math.hpp.bak", "r") as file:
    code = file.read()

lines = code.split("\n")
replaceNext = False

for i, line in enumerate(lines):
    if "if" in line and ("SSE" in line or "SSE2" in line or "SSE3" in line or "SSSE3" in line or "AVX" in line or "AVX512f" in line or "AVX512BW" in line or "AVX512VL" in line):
        lines[i] = line.replace("if (", "if (TILO_EXPECT_WITH_PROBABILITY(")
        line = lines[i]
        if "Svml" in line:
            lines[i] = line.replace("simdEnabledSvmlSupported", "TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION)")
        else:
            lines[i] = line.replace("simdEnabled", "TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION)")
        line = lines[i]
        if "SSE" in line:
            if "Svml" in line:
                lines[i] = line.replace(") [[", ", 1, TILO_SVML_SSE_PROBABILITY)) [[")
            else:
                lines[i] = line.replace(") [[", ", 1, TILO_SSE_PROBABILITY)) [[")
        elif "SSE2" in line:
            lines[i] = line.replace(") [[", ", 1, TILO_SSE2_PROBABILITY)) [[")
        elif "SSE3" in line:
            lines[i] = line.replace(") [[", ", 1, TILO_SSE3_PROBABILITY)) [[")
        elif "SSSE3" in line:
            lines[i] = line.replace(") [[", ", 1, TILO_SSSE3_PROBABILITY)) [[")
        elif "AVX" in line:
            if "Svml" in line:
                lines[i] = line.replace(") [[", ", 1, TILO_SVML_AVX_PROBABILITY)) [[")
            else:
                lines[i] = line.replace(") [[", ", 1, TILO_AVX_PROBABILITY)) [[")
        elif "AVX512f" in line:
            if "Svml" in line:
                lines[i] = line.replace(") [[", ", 1, TILO_SVML_AVX512F_PROBABILITY)) [[")
            else:
                lines[i] = line.replace(") [[", ", 1, TILO_AVX512F_PROBABILITY)) [[")
        elif "AVX512BW" in line:
            lines[i] = line.replace(") [[", ", 1, TILO_AVX512BW_PROBABILITY)) [[")
        elif "AVX512VL" in line:
            lines[i] = line.replace(") [[", ", 1, TILO_AVX512VL_PROBABILITY)) [[")
        line = lines[i]
        if "Svml" in line:
            lines[i] = "\t\tTILO_ASSUME(simdEnabledSvmlSupported)\n" + line
        else:
            lines[i] = "\t\tTILO_ASSUME(simdEnabled)\n" + line
        line = lines[i]
    if "simdEnabledSvmlSupported" in line and "TILO_SIMD_ATTR" in line:
        lines[i] = line.replace("TILO_SIMD_ATTR", "TILO_SVML_ATTR")
        replaceNext = True
        line = lines[i]
    if replaceNext and "TILO_NO_SIMD_ATTR" in line:
        lines[i] = line.replace("TILO_NO_SIMD_ATTR", "TILO_NO_SVML_ATTR")
        replaceNext = False

with open("math.hpp", "w") as file:
    file.write("\n".join(lines))