#ifndef TILO_IS_NONBOOL_INTEGRAL_HPP
#define TILO_IS_NONBOOL_INTEGRAL_HPP

#include <type_traits>
#include "types.hpp"

namespace te {
	template <typename T>
	inline constexpr TEbool is_nonbool_integral = std::is_integral_v<T> && !std::is_same_v<std::remove_cv_t<T>, TEbool>;
}

#endif