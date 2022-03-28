// CPUID
#ifndef TILO_CPUID_HPP
#define TILO_CPUID_HPP

#include "compilers.hpp"
#include "types.hpp"

namespace te {
#if defined(TILO_COMPILER_MS)

#include <intrin.h>

	inline TEvoid cpuid(TEint info[4], TEint infoType) {
		__cpuidex(info, infoType, 0);
	}

#elif defined(TILO_COMPILER_GCC) || defined(TILO_COMPILER_CLANG)

#include <cpuid.h>

	inline TEvoid TILO_CPUID(TEint info[4], TEint infoType) {
		__cpuid_count(infoType, 0, info[0], info[1], info[2], info[3]);
	}

#endif
}

#endif