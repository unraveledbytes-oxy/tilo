#if !defined(TILO_SIMD_TYPES_HPP) && !defined(TILO_NO_SIMD)
#define TILO_SIMD_TYPES_HPP

#include <xmmintrin.h>
#include <emmintrin.h>
#include "CPUInfo.hpp"

namespace te {
	typedef __m128i TE16byte;
	typedef __m256i TE32byte;
	typedef __m512i TE64byte;

	typedef __m128i TE8short;
	typedef __m256i TE16short;
	typedef __m512i TE32short;

	typedef __m128i TE4int;
	typedef __m256i TE8int;
	typedef __m512i TE16int;

	typedef __m128i TE2long;
	typedef __m256i TE4long;
	typedef __m512i TE8long;

	typedef __m128 TE4float;
	typedef __m256 TE8float;
	typedef __m512 TE16float;

	typedef __m128d TE2double;
	typedef __m256d TE4double;
	typedef __m512d TE8double;
}

#endif
