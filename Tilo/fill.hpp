#ifndef TILO_FILL_HPP
#define TILO_FILL_HPP

#include <algorithm>
#include "attributes.hpp"

namespace te {
	template <typename T1, typename T2>
	TILO_INLINE constexpr void fill(const T1 first, const T1 last, const T2& end) {
		std::fill(first, last, end);
	}
}

#endif