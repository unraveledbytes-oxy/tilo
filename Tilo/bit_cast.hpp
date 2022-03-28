#ifndef TILO_BIT_CAST_HPP
#define TILO_BIT_CAST_HPP

#include <type_traits>
#include <bit>
#include "attributes.hpp"

namespace te {
	template <typename T1, typename T2>
	[[nodiscard]] TILO_INLINE constexpr T1 bit_cast(const T2& val) noexcept requires std::conjunction_v<std::bool_constant<sizeof(T1) == sizeof(T2)>, std::is_trivially_copyable<T1>, std::is_trivially_copyable<T2>> {
		return std::bit_cast<T1>(val);
	}
}

#endif