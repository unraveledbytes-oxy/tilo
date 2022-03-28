#ifndef TILO_INIT_HPP
#define TILO_INIT_HPP

#include "static_checks.hpp"
#include "types.hpp"
#include "CPUInfo.hpp"

namespace te {
	TEvoid init() {
		cpuInfoInit();
	}
}

#endif
