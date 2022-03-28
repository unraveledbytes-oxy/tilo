#ifndef TILO_ADDRESSOF_HPP
#define TILO_ADDRESSOF_HPP

#include <memory>
#include "attributes.hpp"

namespace te {
	template <typename T>
	[[nodiscard]] TILO_INLINE constexpr T* addressof(T& val) noexcept {
		return std::addressof(val);
	}
}

#endif