// Perform checks at compile-time to avoid problems at run-time
#ifndef TILO_STATIC_CHECKS_HPP
#define TILO_STATIC_CHECLS_HPP

#include <limits>
#include "compilers.hpp"
#include "types.hpp"

#ifndef __cplusplus
#	error "C++ is required!"
#endif



#if !defined(TILO_COMPILER_MS)
__attribute__((unused)) static inline constexpr bool throw_float_error = !std::numeric_limits<te::TEfloat>::is_iec559;
#	if throw_float_error
#		error "Unsupported platform! \"TEfloat\" does not follow the IEC559 standard!"
#	endif

__attribute__((unused)) static inline constexpr bool throw_double_error = !std::numeric_limits<te::TEdouble>::is_iec559;
#	if throw_double_error
#		error "Unsupported platform! \"TEdouble\" does not follow the IEC559 standard!"
#	endif
#endif

#endif
