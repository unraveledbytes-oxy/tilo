#ifndef TILO_RUNTIMEASSERT_HPP
#define TILO_RUNTIMEASSERT_HPP

#include "types.hpp"

namespace te {
	inline TEvoid runtimeAssert(TEbool val, const char* msg) {
		if (!val)
			throw msg;
	}
}

#endif