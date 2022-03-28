// Do nothing
#ifndef TILO_NOTHING_HPP
#define TILO_NOTHING_HPP

#include "types.hpp"
#include "attributes.hpp"

namespace te {
	extern "C" {
		TILO_INLINE TEvoid nothing() {
			((volatile void) 0);
		}
	}
}

#endif