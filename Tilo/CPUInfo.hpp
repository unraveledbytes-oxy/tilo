// Union that holds information about the CPU

#ifndef TILO_CPUINFO_HPP
#define TILO_CPUINFO_HPP

#include "types.hpp"
#include "cpuid.hpp"
#include "compilers.hpp"
#include "fill.hpp"

namespace te {
	union CPUInfo {
	public:
		TEbool value[31] = {0};
		struct {
			TEbool AVX512VL;
			TEbool AVX512BW;
			TEbool SHA;
			TEbool AVX512CD;
			TEbool AVX512ER;
			TEbool AVX512PF;
			TEbool FMA4;
			TEbool SSE2;
			TEbool SSE;
			TEbool MMX;
			TEbool AVX512IFMA;
			TEbool RDRAND;
			TEbool ADX;
			TEbool AVX;
			TEbool AVX512DQ;
			TEbool AVX512F;
			TEbool AES;
			TEbool SSE42;
			TEbool SSE41;
			TEbool FMA3;
			TEbool XOP;
			TEbool SSSE3;
			TEbool SSE4a;
			TEbool BMI2;
			TEbool ABM;
			TEbool SSE3;
			TEbool AVX2;
			TEbool BMI1;
			TEbool x64;
			TEbool AVX512VBMI;
			TEbool PREFETCHWT1;
		} flags;

		// Suppress the "flags not initialized" MSVC warning
		// This is a union => &value == &flags => flags is also initialized when value is initialized
#ifdef TILO_COMPILER_MS
#	pragma warning(disable: 26495)
		CPUInfo() {
#	pragma warning(default: 26495)
			fill(value, &value[31], false);
			TEint info[4];
			cpuid(info, 0);
			TEint nIds = info[0];

			cpuid(info, 0x80000000);
			TEuint nExIds = info[0];

			if (nIds >= 0x00000001) {
				cpuid(info, 0x00000001);
				flags.MMX = (info[3] & (static_cast<TEuint>(1 << 23))) != 0;
				flags.SSE = (info[3] & (static_cast<TEuint>(1 << 25))) != 0;
				flags.SSE2 = (info[3] & (static_cast<TEuint>(1 << 26))) != 0;
				flags.SSE3 = (info[2] & (static_cast<TEuint>(1 << 0))) != 0;

				flags.SSSE3 = (info[2] & (static_cast<TEuint>(1 << 9))) != 0;
				flags.SSE41 = (info[2] & (static_cast<TEuint>(1 << 19))) != 0;
				flags.SSE42 = (info[2] & (static_cast<TEuint>(1 << 20))) != 0;
				flags.AES = (info[2] & (static_cast<TEuint>(1 << 25))) != 0;

				flags.AVX = (info[2] & (static_cast<TEuint>(1 << 28))) != 0;
				flags.FMA3 = (info[2] & (static_cast<TEuint>(1 << 12))) != 0;

				flags.RDRAND = (info[2] & (static_cast<TEuint>(1 << 30))) != 0;
			}
			if (nIds >= 0x00000007) {
				cpuid(info, 0x00000007);
				flags.AVX2 = (info[1] & (static_cast<TEuint>(1 << 5))) != 0;

				flags.BMI1 = (info[1] & (static_cast<TEuint>(1 << 3))) != 0;
				flags.BMI2 = (info[1] & (static_cast<TEuint>(1 << 8))) != 0;
				flags.ADX = (info[1] & (static_cast<TEuint>(1 << 19))) != 0;
				flags.SHA = (info[1] & (static_cast<TEuint>(1 << 29))) != 0;
				flags.PREFETCHWT1 = (info[2] & (static_cast<TEuint>(1 << 0))) != 0;

				flags.AVX512F = (info[1] & (static_cast<TEuint>(1 << 16))) != 0;
				flags.AVX512CD = (info[1] & (static_cast<TEuint>(1 << 28))) != 0;
				flags.AVX512PF = (info[1] & (static_cast<TEuint>(1 << 26))) != 0;
				flags.AVX512ER = (info[1] & (static_cast<TEuint>(1 << 27))) != 0;
				flags.AVX512VL = (info[1] & (static_cast<TEuint>(1 << 31))) != 0;
				flags.AVX512BW = (info[1] & (static_cast<TEuint>(1 << 30))) != 0;
				flags.AVX512DQ = (info[1] & (static_cast<TEuint>(1 << 17))) != 0;
				flags.AVX512IFMA = (info[1] & (static_cast<TEuint>(1 << 21))) != 0;
				flags.AVX512VBMI = (info[2] & (static_cast<TEuint>(1 << 1))) != 0;
			}
			if (nExIds >= 0x80000001) {
				cpuid(info, 0x80000001);
				flags.x64 = (info[3] & (static_cast<TEuint>(1 << 29))) != 0;
				flags.ABM = (info[2] & (static_cast<TEuint>(1 << 5))) != 0;
				flags.SSE4a = (info[2] & (static_cast<TEuint>(1 << 6))) != 0;
				flags.FMA4 = (info[2] & (static_cast<TEuint>(1 << 16))) != 0;
				flags.XOP = (info[2] & (static_cast<TEuint>(1 << 11))) != 0;
			}
		}
#endif

#if defined(TILO_COMPILER_GNU) || defined(TILO_COMPILER_CLANG)
		CPUInfo() {
			fill(value, &value[31], false);

			flags.MMX = __builtin_cpu_supports("mmx");
			flags.SSE = __builtin_cpu_supports("sse");
			flags.SSE2 = __builtin_cpu_supports("sse2");
			flags.SSE3 = __builtin_cpu_supports("sse3");
			flags.SSSE3 = __builtin_cpu_supports("ssse3");
			flags.SSE41 = __builtin_cpu_supports("sse4.1");
			flags.SSE42 = __builtin_cpu_supports("sse4.2");
			flags.AVX = __builtin_cpu_supports("avx");
			flags.AVX2 = __builtin_cpu_supports("avx2");
			flags.SSE4a = __builtin_cpu_supports("sse4a");
			flags.FMA4 = __builtin_cpu_supports("fma4");
			flags.XOP = __builtin_cpu_supports("xop");
			flags.AVX512F = __builtin_cpu_supports("avx512f");
			flags.BMI2 = __builtin_cpu_supports("bmi");
			flags.AES = __builtin_cpu_supports("aes");
			flags.AVX512VL = __builtin_cpu_supports("avx512vl");
			flags.AVX512BW = __builtin_cpu_supports("avx512bw");
			flags.AVX512DQ = __builtin_cpu_supports("avx512dq");
			flags.AVX512CD = __builtin_cpu_supports("avx512cd");
			flags.AVX512ER = __builtin_cpu_supports("avx512er");
			flags.AVX512PF = __builtin_cpu_supports("avx512pf");
			flags.AVX512VBMI = __builtin_cpu_supports("avx512vbmi");
			flags.AVX512IFMA = __builtin_cpu_supports("avx512ifma");
#if defined(__x86_64__) || defined(_M_X64)
			flags.x64 = true;
#endif
		}
#endif

		~CPUInfo() {}
	};



	CPUInfo* cpuInfo;

	inline TEvoid cpuInfoInit() {
		cpuInfo = new CPUInfo();
	}
}

#endif
