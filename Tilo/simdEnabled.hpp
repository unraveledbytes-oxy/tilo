#ifndef TILO_SIMDENABLED_HPP
#define TILO_SIMDENABLED_HPP

#include "types.hpp"
#include "CPUInfo.hpp"

namespace te {
#ifdef TILO_NO_SIMD
	constexpr TEbool simdDisabled = false;
#else
	constexpr TEbool simdEnabled = true;
#endif
}

#endif