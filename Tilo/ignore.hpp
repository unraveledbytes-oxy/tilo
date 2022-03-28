#ifndef TILO_IGNORE_HPP
#define TILO_IGNORE_HPP

#include "types.hpp"
#include "attributes.hpp"
#include "compilers.hpp"

namespace te {
	template <typename... T>
	TILO_INLINE TEvoid ignore(T... args) {
#ifdef TILO_COMPILER_MS
		__noop(args...);
#endif
	}
}

#endif