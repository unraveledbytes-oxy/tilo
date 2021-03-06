// Math with SIMD support
#ifndef TILO_MATH_HPP
#define TILO_MATH_HPP

#include <cmath>
#include<numeric>
#include <type_traits>
#ifndef TILO_NO_SIMD
#	include <xmmintrin.h>
#	include <emmintrin.h>
#	include <immintrin.h>
#endif
#include "types.hpp"
#include "simd_types.hpp"
#include "CPUInfo.hpp"
#include "simdEnabled.hpp"
#include "bit_cast.hpp"
#include "attributes.hpp"

#ifdef TILO_NO_SIMD
#	define TILO_SSE_PROBABILITY 0
#	define TILO_SVML_SSE_PROBABILITY 0
#	define TILO_SSE2_PROBABILITY 0
#	define TILO_SSE3_PROBABILITY 0
#	define TILO_SSSE3_PROBABILITY 0
#	define TILO_AVX_PROBABILITY 0
#	define TILO_SVML_AVX_PROBABILITY 0
#	define TILO_AVX512F_PROBABILITY 0
#	define TILO_SVML_AVX512F_PROBABILITY 0
#	define TILO_AVX512BW_PROBABILITY 0
#	define TILO_AVX512VL_PROBABILITY 0
#	define TILO_SIMD_ATTR unlikely
#	define TILO_NO_SIMD_ATTR likely
#else
#	define TILO_SSE_PROBABILITY 1
#	define TILO_SVML_SSE_PROBABILITY 1
#	define TILO_SSE2_PROBABILITY 1
#	define TILO_SSE3_PROBABILITY 0.999999999998
#	define TILO_SSSE3_PROBABILITY 0.999999999897
#	define TILO_AVX_PROBABILITY 0.999810624604
#	define TILO_SVML_AVX_PROBABILITY 0.999810624604
#	define TILO_AVX512F_PROBABILITY 0.801191114813
#	define TILO_SVML_AVX512F_PROBABILITY 0.801191114813
#	define TILO_AVX512BW_PROBABILITY 0.910146234571
#	define TILO_AVX512VL_PROBABILITY 0.910146234571
#	define TILO_SIMD_ATTR likely
#	define TILO_NO_SIMD_ATTR unlikely
#endif

#define TILO_SVML_ATTR TILO_SIMD_ATTR
#define TILO_NO_SVML_ATTR TILO_NO_SIMD_ATTR

#if simdEnabled
#	define TILO_ASSUME_SIMD TILO_ASSUME(simdEnabled)
#	define TILO_SIMD_ENABLED_EXPECTATION 1
#else
#	define TILO_ASSUME_SIMD TILO_ASSUME(!simdEnabled)
#	define TILO_SIMD_ENABLED_EXPECTATION 0
#endif

namespace te {
#ifdef TILO_COMPILER_MS
	static inline constexpr TEbool& simdEnabledSvmlSupported = simdEnabled;
#else
#	undef TILO_SVML_ATTR
#	undef TILO_NO_SVML_ATTR
#	undef TILO_SVML_SSE_PROBABILITY
#	undef TILO_SVML_AVX_PROBABILITY
#	undef TILO_SVML_AVX512F_PROBABILITY
#	define TILO_SVML_ATTR unlikely
#	define TILO_NO_SVML_ATTR likely
#	define TILO_SVML_SSE_PROBABILITY 0
#	define TILO_SVML_AVX_PROBABILITY 0
#	define TILO_SVML_AVX512F_PROBABILITY 0
	static inline constexpr TEbool simdEnabledSvmlSupported = false;

	[[maybe_unused]] TILO_NAKED static inline TE4float _mm_sin_ps(TE4float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8float _mm256_sin_ps(TE8float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE16float _mm512_sin_ps(TE16float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE2double _mm_sin_pd(TE2double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4double _mm256_sin_pd(TE4double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8double _mm512_sin_pd(TE8double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4float _mm_cos_ps(TE4float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8float _mm256_cos_ps(TE8float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE16float _mm512_cos_ps(TE16float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE2double _mm_cos_pd(TE2double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4double _mm256_cos_pd(TE4double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8double _mm512_cos_pd(TE8double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4float _mm_tan_ps(TE4float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8float _mm256_tan_ps(TE8float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE16float _mm512_tan_ps(TE16float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE2double _mm_tan_pd(TE2double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4double _mm256_tan_pd(TE4double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8double _mm512_tan_pd(TE8double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4float _mm_asin_ps(TE4float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8float _mm256_asin_ps(TE8float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE16float _mm512_asin_ps(TE16float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE2double _mm_asin_pd(TE2double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4double _mm256_asin_pd(TE4double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8double _mm512_asin_pd(TE8double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4float _mm_acos_ps(TE4float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8float _mm256_acos_ps(TE8float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE16float _mm512_acos_ps(TE16float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE2double _mm_acos_pd(TE2double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4double _mm256_acos_pd(TE4double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8double _mm512_acos_pd(TE8double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4float _mm_atan_ps(TE4float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8float _mm256_atan_ps(TE8float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE16float _mm512_atan_ps(TE16float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE2double _mm_atan_pd(TE2double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4double _mm256_atan_pd(TE4double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8double _mm512_atan_pd(TE8double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4float _mm_sinh_ps(TE4float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8float _mm256_sinh_ps(TE8float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE16float _mm512_sinh_ps(TE16float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE2double _mm_sinh_pd(TE2double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4double _mm256_sinh_pd(TE4double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8double _mm512_sinh_pd(TE8double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4float _mm_cosh_ps(TE4float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8float _mm256_cosh_ps(TE8float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE16float _mm512_cosh_ps(TE16float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE2double _mm_cosh_pd(TE2double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4double _mm256_cosh_pd(TE4double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8double _mm512_cosh_pd(TE8double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4float _mm_tanh_ps(TE4float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8float _mm256_tanh_ps(TE8float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE16float _mm512_tanh_ps(TE16float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE2double _mm_tanh_pd(TE2double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4double _mm256_tanh_pd(TE4double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8double _mm512_tanh_pd(TE8double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4float _mm_asinh_ps(TE4float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8float _mm256_asinh_ps(TE8float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE16float _mm512_asinh_ps(TE16float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE2double _mm_asinh_pd(TE2double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4double _mm256_asinh_pd(TE4double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8double _mm512_asinh_pd(TE8double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4float _mm_acosh_ps(TE4float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8float _mm256_acosh_ps(TE8float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE16float _mm512_acosh_ps(TE16float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE2double _mm_acosh_pd(TE2double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4double _mm256_acosh_pd(TE4double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8double _mm512_acosh_pd(TE8double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4float _mm_atanh_ps(TE4float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8float _mm256_atanh_ps(TE8float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE16float _mm512_atanh_ps(TE16float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE2double _mm_atanh_pd(TE2double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4double _mm256_atanh_pd(TE4double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8double _mm512_atanh_pd(TE8double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4float _mm_sincos_ps(TE4float* out, TE4float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8float _mm256_sincos_ps(TE8float* out, TE8float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE16float _mm512_sincos_ps(TE16float* out, TE16float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE2double _mm_sincos_pd(TE2double* out, TE2double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4double _mm256_sincos_pd(TE4double* out, TE4double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8double _mm512_sincos_pd(TE8double* out, TE8double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4float _mm_svml_round_ps(TE4float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8float _mm256_svml_round_ps(TE8float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE16float _mm512_svml_round_ps(TE16float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE2double _mm_svml_round_pd(TE2double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4double _mm256_svml_round_pd(TE4double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8double _mm512_svml_round_pd(TE8double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4float _mm_svml_ceil_ps(TE4float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8float _mm256_svml_ceil_ps(TE8float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE16float _mm512_svml_ceil_ps(TE16float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE2double _mm_svml_ceil_pd(TE2double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4double _mm256_svml_ceil_pd(TE4double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8double _mm512_svml_ceil_pd(TE8double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4float _mm_svml_floor_ps(TE4float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8float _mm256_svml_floor_ps(TE8float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE16float _mm512_svml_floor_ps(TE16float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE2double _mm_svml_floor_pd(TE2double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4double _mm256_svml_floor_pd(TE4double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8double _mm512_svml_floor_pd(TE8double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE2double _mm_svml_sqrt_pd(TE2double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE16byte _mm_div_epi8(TE16byte val1, TE16byte val2) {
		return val1;
	}

	[[maybe_unused]] TILO_NAKED static inline TE32byte _mm256_div_epi8(TE32byte val1, TE32byte val2) {
		return val1;
	}

	[[maybe_unused]] TILO_NAKED static inline TE64byte _mm512_div_epi8(TE64byte val1, TE64byte val2) {
		return val1;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8short _mm_div_epi16(TE8short val1, TE8short val2) {
		return val1;
	}

	[[maybe_unused]] TILO_NAKED static inline TE16short _mm256_div_epi16(TE16short val1, TE16short val2) {
		return val1;
	}

	[[maybe_unused]] TILO_NAKED static inline TE32short _mm512_div_epi16(TE32short val1, TE32short val2) {
		return val1;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4int _mm_div_epi32(TE4int val1, TE4int val2) {
		return val1;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8int _mm256_div_epi32(TE8int val1, TE8int val2) {
		return val1;
	}

	[[maybe_unused]] TILO_NAKED static inline TE16int _mm512_div_epi32(TE16int val1, TE16int val2) {
		return val1;
	}

	[[maybe_unused]] TILO_NAKED static inline TE2long _mm_div_epi64(TE2long val1, TE2long val2) {
		return val1;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4long _mm256_div_epi64(TE4long val1, TE4long val2) {
		return val1;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8long _mm512_div_epi64(TE8long val1, TE8long val2) {
		return val1;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4float _mm_invsqrt_ps(TE4float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8float _mm256_invsqrt_ps(TE8float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE16float _mm512_invsqrt_ps(TE16float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE2double _mm_invsqrt_pd(TE2double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4double _mm256_invsqrt_pd(TE4double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8double _mm512_invsqrt_pd(TE8double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4float _mm_cbrt_ps(TE4float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8float _mm256_cbrt_ps(TE8float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE16float _mm512_cbrt_ps(TE16float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE2double _mm_cbrt_pd(TE2double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4double _mm256_cbrt_pd(TE4double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8double _mm512_cbrt_pd(TE8double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4float _mm_invcbrt_ps(TE4float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8float _mm256_invcbrt_ps(TE8float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE16float _mm512_invcbrt_ps(TE16float val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE2double _mm_invcbrt_pd(TE2double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE4double _mm256_invcbrt_pd(TE4double val) {
		return val;
	}

	[[maybe_unused]] TILO_NAKED static inline TE8double _mm512_invcbrt_pd(TE8double val) {
		return val;
	}
#endif

#if simdEnabledSvmlSupported
#	define TILO_ASSUME_SVML TILO_ASSUME(simdEnabledSvmlSupported)
#	define TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION 1
#else
#	define TILO_ASSUME_SVML TILO_ASSUME(!simdEnabledSvmlSupported)
#	define TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION 0
#endif

	[[nodiscard]] TILO_INLINE TEfloat TILO_FASTCALL sin(
		TEfloat val) {
		return std::sin(val);
	}

	TILO_INLINE TEvoid sin(
		TEfloat& out,
		TEfloat val) {
		out = sin(val);
	}

	TEvoid TILO_VECTORCALL sin_2(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2) { 
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_sin_ps(_mm_set_ps(0, 0, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = sin(val1);
			out[1] = sin(val2);
		}
	}

	TEvoid TILO_VECTORCALL sin_4(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_sin_ps(_mm_set_ps(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = sin(val1);
			out[1] = sin(val2);
			out[2] = sin(val3);
			out[3] = sin(val4);
		}
	}

	TEvoid TILO_VECTORCALL sin_8(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_ps(out, _mm256_sin_ps(_mm256_set_ps(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			sin_4(out,
				val1,
				val2,
				val3,
				val4);
			sin_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	TEvoid TILO_VECTORCALL sin_16(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8,
		TEfloat val9,
		TEfloat val10,
		TEfloat val11,
		TEfloat val12,
		TEfloat val13,
		TEfloat val14,
		TEfloat val15,
		TEfloat val16) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm512_store_ps(out, _mm512_sin_ps(_mm512_set_ps(val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			sin_8(out,
				val1,
				val2,
				val3,
				val4,
				val5,
				val6,
				val7,
				val8);
			sin_8(&out[8],
				val9,
				val10,
				val11,
				val12,
				val13,
				val14,
				val15,
				val16);
		}
	}

	[[nodiscard]] TILO_INLINE TEdouble TILO_FASTCALL sin(
		TEdouble val) {
		return std::sin(val);
	}

	TILO_INLINE TEvoid sin(
		TEdouble& out,
		TEdouble val) {
		out = sin(val);
	}

	TEvoid TILO_VECTORCALL sin_2(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_pd(out, _mm_sin_pd(_mm_set_pd(val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = sin(val1);
			out[1] = sin(val2);
		}
	}

	TEvoid TILO_VECTORCALL sin_4(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_pd(out, _mm256_sin_pd(_mm256_set_pd(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			sin_2(out,
				val1,
				val2);
			sin_2(&out[2],
				val3,
				val4);
		}
	}

	TEvoid TILO_VECTORCALL sin_8(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4,
		TEdouble val5,
		TEdouble val6,
		TEdouble val7,
		TEdouble val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm512_store_pd(out, _mm512_sin_pd(_mm512_set_pd(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			sin_4(out,
				val1,
				val2,
				val3,
				val4);
			sin_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	[[nodiscard]] TILO_INLINE TEfloat TILO_FASTCALL cos(
		TEfloat val) {
		return std::cos(val);
	}

	TILO_INLINE TEvoid cos(
		TEfloat& out,
		TEfloat val) {
		out = cos(val);
	}

	TEvoid TILO_VECTORCALL cos_2(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_cos_ps(_mm_set_ps(0, 0, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = cos(val1);
			out[1] = cos(val2);
		}
	}

	TEvoid TILO_VECTORCALL cos_4(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_cos_ps(_mm_set_ps(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = cos(val1);
			out[1] = cos(val2);
			out[2] = cos(val3);
			out[3] = cos(val4);
		}
	}

	TEvoid TILO_VECTORCALL cos_8(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_ps(out, _mm256_cos_ps(_mm256_set_ps(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			cos_4(out,
				val1,
				val2,
				val3,
				val4);
			cos_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	TEvoid TILO_VECTORCALL cos_16(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8,
		TEfloat val9,
		TEfloat val10,
		TEfloat val11,
		TEfloat val12,
		TEfloat val13,
		TEfloat val14,
		TEfloat val15,
		TEfloat val16) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm512_store_ps(out, _mm512_cos_ps(_mm512_set_ps(val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			cos_8(out,
				val1,
				val2,
				val3,
				val4,
				val5,
				val6,
				val7,
				val8);
			cos_8(&out[8],
				val9,
				val10,
				val11,
				val12,
				val13,
				val14,
				val15,
				val16);
		}
	}

	[[nodiscard]] TILO_INLINE TEdouble TILO_FASTCALL cos(
		TEdouble val) {
		return std::cos(val);
	}

	TILO_INLINE TEvoid cos(
		TEdouble& out,
		TEdouble val) {
		out = cos(val);
	}

	TEvoid TILO_VECTORCALL cos_2(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_pd(out, _mm_cos_pd(_mm_set_pd(val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = cos(val1);
			out[1] = cos(val2);
		}
	}

	TEvoid TILO_VECTORCALL cos_4(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_pd(out, _mm256_cos_pd(_mm256_set_pd(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			cos_2(out,
				val1,
				val2);
			cos_2(&out[2],
				val3,
				val4);
		}
	}

	TEvoid TILO_VECTORCALL cos_8(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4,
		TEdouble val5,
		TEdouble val6,
		TEdouble val7,
		TEdouble val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm512_store_pd(out, _mm512_cos_pd(_mm512_set_pd(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			cos_4(out,
				val1,
				val2,
				val3,
				val4);
			cos_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	[[nodiscard]] TILO_INLINE TEfloat TILO_FASTCALL tan(
		TEfloat val) {
		return std::tan(val);
	}

	TILO_INLINE TEvoid tan(
		TEfloat& out,
		TEfloat val) {
		out = tan(val);
	}

	TEvoid TILO_VECTORCALL tan_2(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_tan_ps(_mm_set_ps(0, 0, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = tan(val1);
			out[1] = tan(val2);
		}
	}

	TEvoid TILO_VECTORCALL tan_4(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_tan_ps(_mm_set_ps(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = tan(val1);
			out[1] = tan(val2);
			out[2] = tan(val3);
			out[3] = tan(val4);
		}
	}

	TEvoid TILO_VECTORCALL tan_8(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_ps(out, _mm256_tan_ps(_mm256_set_ps(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			tan_4(out,
				val1,
				val2,
				val3,
				val4);
			tan_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	TEvoid TILO_VECTORCALL tan_16(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8,
		TEfloat val9,
		TEfloat val10,
		TEfloat val11,
		TEfloat val12,
		TEfloat val13,
		TEfloat val14,
		TEfloat val15,
		TEfloat val16) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm512_store_ps(out, _mm512_tan_ps(_mm512_set_ps(val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			tan_8(out,
				val1,
				val2,
				val3,
				val4,
				val5,
				val6,
				val7,
				val8);
			tan_8(&out[8],
				val9,
				val10,
				val11,
				val12,
				val13,
				val14,
				val15,
				val16);
		}
	}

	[[nodiscard]] TILO_INLINE TEdouble TILO_FASTCALL tan(
		TEdouble val) {
		return std::tan(val);
	}

	TILO_INLINE TEvoid tan(
		TEdouble& out,
		TEdouble val) {
		out = tan(val);
	}

	TEvoid TILO_VECTORCALL tan_2(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_pd(out, _mm_tan_pd(_mm_set_pd(val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = tan(val1);
			out[1] = tan(val2);
		}
	}

	TEvoid TILO_VECTORCALL tan_4(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_pd(out, _mm256_tan_pd(_mm256_set_pd(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			tan_2(out,
				val1,
				val2);
			tan_2(&out[2],
				val3,
				val4);
		}
	}

	TEvoid TILO_VECTORCALL tan_8(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4,
		TEdouble val5,
		TEdouble val6,
		TEdouble val7,
		TEdouble val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm512_store_pd(out, _mm512_tan_pd(_mm512_set_pd(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			tan_4(out,
				val1,
				val2,
				val3,
				val4);
			tan_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	[[nodiscard]] TILO_INLINE TEfloat TILO_FASTCALL asin(
		TEfloat val) {
		return std::asin(val);
	}

	TILO_INLINE TEvoid asin(
		TEfloat& out,
		TEfloat val) {
		out = asin(val);
	}

	TEvoid TILO_VECTORCALL asin_2(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_asin_ps(_mm_set_ps(0, 0, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = asin(val1);
			out[1] = asin(val2);
		}
	}

	TEvoid TILO_VECTORCALL asin_4(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_asin_ps(_mm_set_ps(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = asin(val1);
			out[1] = asin(val2);
			out[2] = asin(val3);
			out[3] = asin(val4);
		}
	}

	TEvoid TILO_VECTORCALL asin_8(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_ps(out, _mm256_asin_ps(_mm256_set_ps(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			asin_4(out,
				val1,
				val2,
				val3,
				val4);
			asin_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	TEvoid TILO_VECTORCALL asin_16(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8,
		TEfloat val9,
		TEfloat val10,
		TEfloat val11,
		TEfloat val12,
		TEfloat val13,
		TEfloat val14,
		TEfloat val15,
		TEfloat val16) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm512_store_ps(out, _mm512_asin_ps(_mm512_set_ps(val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			asin_8(out,
				val1,
				val2,
				val3,
				val4,
				val5,
				val6,
				val7,
				val8);
			asin_8(&out[8],
				val9,
				val10,
				val11,
				val12,
				val13,
				val14,
				val15,
				val16);
		}
	}

	[[nodiscard]] TILO_INLINE TEdouble TILO_FASTCALL asin(
		TEdouble val) {
		return std::asin(val);
	}

	TILO_INLINE TEvoid asin(
		TEdouble& out,
		TEdouble val) {
		out = asin(val);
	}

	TEvoid TILO_VECTORCALL asin_2(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_pd(out, _mm_asin_pd(_mm_set_pd(val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = asin(val1);
			out[1] = asin(val2);
		}
	}

	TEvoid TILO_VECTORCALL asin_4(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_pd(out, _mm256_asin_pd(_mm256_set_pd(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			asin_2(out,
				val1,
				val2);
			asin_2(&out[2],
				val3,
				val4);
		}
	}

	TEvoid TILO_VECTORCALL asin_8(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4,
		TEdouble val5,
		TEdouble val6,
		TEdouble val7,
		TEdouble val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm512_store_pd(out, _mm512_asin_pd(_mm512_set_pd(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			asin_4(out,
				val1,
				val2,
				val3,
				val4);
			asin_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	[[nodiscard]] TILO_INLINE TEfloat TILO_FASTCALL acos(
		TEfloat val) {
		return std::acos(val);
	}

	TILO_INLINE TEvoid acos(
		TEfloat& out,
		TEfloat val) {
		out = acos(val);
	}

	TEvoid TILO_VECTORCALL acos_2(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_acos_ps(_mm_set_ps(0, 0, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = acos(val1);
			out[1] = acos(val2);
		}
	}

	TEvoid TILO_VECTORCALL acos_4(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_acos_ps(_mm_set_ps(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = acos(val1);
			out[1] = acos(val2);
			out[2] = acos(val3);
			out[3] = acos(val4);
		}
	}

	TEvoid TILO_VECTORCALL acos_8(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_ps(out, _mm256_acos_ps(_mm256_set_ps(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			acos_4(out,
				val1,
				val2,
				val3,
				val4);
			acos_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	TEvoid TILO_VECTORCALL acos_16(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8,
		TEfloat val9,
		TEfloat val10,
		TEfloat val11,
		TEfloat val12,
		TEfloat val13,
		TEfloat val14,
		TEfloat val15,
		TEfloat val16) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm512_store_ps(out, _mm512_acos_ps(_mm512_set_ps(val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			acos_8(out,
				val1,
				val2,
				val3,
				val4,
				val5,
				val6,
				val7,
				val8);
			acos_8(&out[8],
				val9,
				val10,
				val11,
				val12,
				val13,
				val14,
				val15,
				val16);
		}
	}

	[[nodiscard]] TILO_INLINE TEdouble TILO_FASTCALL acos(
		TEdouble val) {
		return std::acos(val);
	}

	TILO_INLINE TEvoid acos(
		TEdouble& out,
		TEdouble val) {
		out = acos(val);
	}

	TEvoid TILO_VECTORCALL acos_2(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_pd(out, _mm_acos_pd(_mm_set_pd(val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = acos(val1);
			out[1] = acos(val2);
		}
	}

	TEvoid TILO_VECTORCALL acos_4(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_pd(out, _mm256_acos_pd(_mm256_set_pd(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			acos_2(out,
				val1,
				val2);
			acos_2(&out[2],
				val3,
				val4);
		}
	}

	TEvoid TILO_VECTORCALL acos_8(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4,
		TEdouble val5,
		TEdouble val6,
		TEdouble val7,
		TEdouble val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm512_store_pd(out, _mm512_acos_pd(_mm512_set_pd(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			acos_4(out,
				val1,
				val2,
				val3,
				val4);
			acos_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	[[nodiscard]] TILO_INLINE TEfloat TILO_FASTCALL atan(
		TEfloat val) {
		return std::atan(val);
	}

	TILO_INLINE TEvoid atan(
		TEfloat& out,
		TEfloat val) {
		out = atan(val);
	}

	TEvoid TILO_VECTORCALL atan_2(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_atan_ps(_mm_set_ps(0, 0, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = atan(val1);
			out[1] = atan(val2);
		}
	}

	TEvoid TILO_VECTORCALL atan_4(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_atan_ps(_mm_set_ps(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = atan(val1);
			out[1] = atan(val2);
			out[2] = atan(val3);
			out[3] = atan(val4);
		}
	}

	TEvoid TILO_VECTORCALL atan_8(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_ps(out, _mm256_atan_ps(_mm256_set_ps(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			atan_4(out,
				val1,
				val2,
				val3,
				val4);
			atan_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	TEvoid TILO_VECTORCALL atan_16(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8,
		TEfloat val9,
		TEfloat val10,
		TEfloat val11,
		TEfloat val12,
		TEfloat val13,
		TEfloat val14,
		TEfloat val15,
		TEfloat val16) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm512_store_ps(out, _mm512_atan_ps(_mm512_set_ps(val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			atan_8(out,
				val1,
				val2,
				val3,
				val4,
				val5,
				val6,
				val7,
				val8);
			atan_8(&out[8],
				val9,
				val10,
				val11,
				val12,
				val13,
				val14,
				val15,
				val16);
		}
	}

	[[nodiscard]] TILO_INLINE TEdouble TILO_FASTCALL atan(
		TEdouble val) {
		return std::atan(val);
	}

	TILO_INLINE TEvoid atan(
		TEdouble& out,
		TEdouble val) {
		out = atan(val);
	}

	TEvoid TILO_VECTORCALL atan_2(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_pd(out, _mm_atan_pd(_mm_set_pd(val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = atan(val1);
			out[1] = atan(val2);
		}
	}

	TEvoid TILO_VECTORCALL atan_4(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_pd(out, _mm256_atan_pd(_mm256_set_pd(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			atan_2(out,
				val1,
				val2);
			atan_2(&out[2],
				val3,
				val4);
		}
	}

	TEvoid TILO_VECTORCALL atan_8(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4,
		TEdouble val5,
		TEdouble val6,
		TEdouble val7,
		TEdouble val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm512_store_pd(out, _mm512_atan_pd(_mm512_set_pd(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			atan_4(out,
				val1,
				val2,
				val3,
				val4);
			atan_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	[[nodiscard]] TILO_INLINE TEfloat TILO_FASTCALL sinh(
		TEfloat val) {
		return std::sinh(val);
	}

	TILO_INLINE TEvoid sinh(
		TEfloat& out,
		TEfloat val) {
		out = sinh(val);
	}

	TEvoid TILO_VECTORCALL sinh_2(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_sinh_ps(_mm_set_ps(0, 0, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = sinh(val1);
			out[1] = sinh(val2);
		}
	}

	TEvoid TILO_VECTORCALL sinh_4(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_sinh_ps(_mm_set_ps(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = sinh(val1);
			out[1] = sinh(val2);
			out[2] = sinh(val3);
			out[3] = sinh(val4);
		}
	}

	TEvoid TILO_VECTORCALL sinh_8(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_ps(out, _mm256_sinh_ps(_mm256_set_ps(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			sinh_4(out,
				val1,
				val2,
				val3,
				val4);
			sinh_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	TEvoid TILO_VECTORCALL sinh_16(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8,
		TEfloat val9,
		TEfloat val10,
		TEfloat val11,
		TEfloat val12,
		TEfloat val13,
		TEfloat val14,
		TEfloat val15,
		TEfloat val16) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm512_store_ps(out, _mm512_sinh_ps(_mm512_set_ps(val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			sinh_8(out,
				val1,
				val2,
				val3,
				val4,
				val5,
				val6,
				val7,
				val8);
			sinh_8(&out[8],
				val9,
				val10,
				val11,
				val12,
				val13,
				val14,
				val15,
				val16);
		}
	}

	[[nodiscard]] TILO_INLINE TEdouble TILO_FASTCALL sinh(
		TEdouble val) {
		return std::sinh(val);
	}

	TILO_INLINE TEvoid sinh(
		TEdouble& out,
		TEdouble val) {
		out = sinh(val);
	}

	TEvoid TILO_VECTORCALL sinh_2(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_pd(out, _mm_sinh_pd(_mm_set_pd(val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = sinh(val1);
			out[1] = sinh(val2);
		}
	}

	TEvoid TILO_VECTORCALL sinh_4(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_pd(out, _mm256_sinh_pd(_mm256_set_pd(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			sinh_2(out,
				val1,
				val2);
			sinh_2(&out[2],
				val3,
				val4);
		}
	}

	TEvoid TILO_VECTORCALL sinh_8(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4,
		TEdouble val5,
		TEdouble val6,
		TEdouble val7,
		TEdouble val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm512_store_pd(out, _mm512_sinh_pd(_mm512_set_pd(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			sinh_4(out,
				val1,
				val2,
				val3,
				val4);
			sinh_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	[[nodiscard]] TILO_INLINE TEfloat TILO_FASTCALL cosh(
		TEfloat val) {
		return std::cosh(val);
	}

	TILO_INLINE TEvoid cosh(
		TEfloat& out,
		TEfloat val) {
		out = cosh(val);
	}

	TEvoid TILO_VECTORCALL cosh_2(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_cosh_ps(_mm_set_ps(0, 0, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = cosh(val1);
			out[1] = cosh(val2);
		}
	}

	TEvoid TILO_VECTORCALL cosh_4(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_cosh_ps(_mm_set_ps(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = cosh(val1);
			out[1] = cosh(val2);
			out[2] = cosh(val3);
			out[3] = cosh(val4);
		}
	}

	TEvoid TILO_VECTORCALL cosh_8(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_ps(out, _mm256_cosh_ps(_mm256_set_ps(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			cosh_4(out,
				val1,
				val2,
				val3,
				val4);
			cosh_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	TEvoid TILO_VECTORCALL cosh_16(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8,
		TEfloat val9,
		TEfloat val10,
		TEfloat val11,
		TEfloat val12,
		TEfloat val13,
		TEfloat val14,
		TEfloat val15,
		TEfloat val16) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm512_store_ps(out, _mm512_cosh_ps(_mm512_set_ps(val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			cosh_8(out,
				val1,
				val2,
				val3,
				val4,
				val5,
				val6,
				val7,
				val8);
			cosh_8(&out[8],
				val9,
				val10,
				val11,
				val12,
				val13,
				val14,
				val15,
				val16);
		}
	}

	[[nodiscard]] TILO_INLINE TEdouble TILO_FASTCALL cosh(
		TEdouble val) {
		return std::cosh(val);
	}

	TILO_INLINE TEvoid cosh(
		TEdouble& out,
		TEdouble val) {
		out = cosh(val);
	}

	TEvoid TILO_VECTORCALL cosh_2(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_pd(out, _mm_cosh_pd(_mm_set_pd(val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = cosh(val1);
			out[1] = cosh(val2);
		}
	}

	TEvoid TILO_VECTORCALL cosh_4(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_pd(out, _mm256_cosh_pd(_mm256_set_pd(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			cosh_2(out,
				val1,
				val2);
			cosh_2(&out[2],
				val3,
				val4);
		}
	}

	TEvoid TILO_VECTORCALL cosh_8(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4,
		TEdouble val5,
		TEdouble val6,
		TEdouble val7,
		TEdouble val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm512_store_pd(out, _mm512_cosh_pd(_mm512_set_pd(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			cosh_4(out,
				val1,
				val2,
				val3,
				val4);
			cosh_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	[[nodiscard]] TILO_INLINE TEfloat TILO_FASTCALL tanh(
		TEfloat val) {
		return std::tanh(val);
	}

	TILO_INLINE TEvoid tanh(
		TEfloat& out,
		TEfloat val) {
		out = tanh(val);
	}

	TEvoid TILO_VECTORCALL tanh_2(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_tanh_ps(_mm_set_ps(0, 0, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = tanh(val1);
			out[1] = tanh(val2);
		}
	}

	TEvoid TILO_VECTORCALL tanh_4(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_tanh_ps(_mm_set_ps(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = tanh(val1);
			out[1] = tanh(val2);
			out[2] = tanh(val3);
			out[3] = tanh(val4);
		}
	}

	TEvoid TILO_VECTORCALL tanh_8(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_ps(out, _mm256_tanh_ps(_mm256_set_ps(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			tanh_4(out,
				val1,
				val2,
				val3,
				val4);
			tanh_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	TEvoid TILO_VECTORCALL tanh_16(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8,
		TEfloat val9,
		TEfloat val10,
		TEfloat val11,
		TEfloat val12,
		TEfloat val13,
		TEfloat val14,
		TEfloat val15,
		TEfloat val16) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm512_store_ps(out, _mm512_tanh_ps(_mm512_set_ps(val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			tanh_8(out,
				val1,
				val2,
				val3,
				val4,
				val5,
				val6,
				val7,
				val8);
			tanh_8(&out[8],
				val9,
				val10,
				val11,
				val12,
				val13,
				val14,
				val15,
				val16);
		}
	}

	[[nodiscard]] TILO_INLINE TEdouble TILO_FASTCALL tanh(
		TEdouble val) {
		return std::tanh(val);
	}

	TILO_INLINE TEvoid tanh(
		TEdouble& out,
		TEdouble val) {
		out = tanh(val);
	}

	TEvoid TILO_VECTORCALL tanh_2(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_pd(out, _mm_tanh_pd(_mm_set_pd(val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = tanh(val1);
			out[1] = tanh(val2);
		}
	}

	TEvoid TILO_VECTORCALL tanh_4(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_pd(out, _mm256_tanh_pd(_mm256_set_pd(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			tanh_2(out,
				val1,
				val2);
			tanh_2(&out[2],
				val3,
				val4);
		}
	}

	TEvoid TILO_VECTORCALL tanh_8(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4,
		TEdouble val5,
		TEdouble val6,
		TEdouble val7,
		TEdouble val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm512_store_pd(out, _mm512_tanh_pd(_mm512_set_pd(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			tanh_4(out,
				val1,
				val2,
				val3,
				val4);
			tanh_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	[[nodiscard]] TILO_INLINE TEfloat TILO_FASTCALL asinh(
		TEfloat val) {
		return std::asinh(val);
	}

	TILO_INLINE TEvoid asinh(
		TEfloat& out,
		TEfloat val) {
		out = asinh(val);
	}

	TEvoid TILO_VECTORCALL asinh_2(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_asinh_ps(_mm_set_ps(0, 0, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = asinh(val1);
			out[1] = asinh(val2);
		}
	}

	TEvoid TILO_VECTORCALL asinh_4(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_asinh_ps(_mm_set_ps(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = asinh(val1);
			out[1] = asinh(val2);
			out[2] = asinh(val3);
			out[3] = asinh(val4);
		}
	}

	TEvoid TILO_VECTORCALL asinh_8(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_ps(out, _mm256_asinh_ps(_mm256_set_ps(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			asinh_4(out,
				val1,
				val2,
				val3,
				val4);
			asinh_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	TEvoid TILO_VECTORCALL asinh_16(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8,
		TEfloat val9,
		TEfloat val10,
		TEfloat val11,
		TEfloat val12,
		TEfloat val13,
		TEfloat val14,
		TEfloat val15,
		TEfloat val16) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm512_store_ps(out, _mm512_asinh_ps(_mm512_set_ps(val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			asinh_8(out,
				val1,
				val2,
				val3,
				val4,
				val5,
				val6,
				val7,
				val8);
			asinh_8(&out[8],
				val9,
				val10,
				val11,
				val12,
				val13,
				val14,
				val15,
				val16);
		}
	}

	[[nodiscard]] TILO_INLINE TEdouble TILO_FASTCALL asinh(
		TEdouble val) {
		return std::asinh(val);
	}

	TILO_INLINE TEvoid asinh(
		TEdouble& out,
		TEdouble val) {
		out = asinh(val);
	}

	TEvoid TILO_VECTORCALL asinh_2(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_pd(out, _mm_asinh_pd(_mm_set_pd(val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = asinh(val1);
			out[1] = asinh(val2);
		}
	}

	TEvoid TILO_VECTORCALL asinh_4(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_pd(out, _mm256_asinh_pd(_mm256_set_pd(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			asinh_2(out,
				val1,
				val2);
			asinh_2(&out[2],
				val3,
				val4);
		}
	}

	TEvoid TILO_VECTORCALL asinh_8(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4,
		TEdouble val5,
		TEdouble val6,
		TEdouble val7,
		TEdouble val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm512_store_pd(out, _mm512_asinh_pd(_mm512_set_pd(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			asinh_4(out,
				val1,
				val2,
				val3,
				val4);
			asinh_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	[[nodiscard]] TILO_INLINE TEfloat TILO_FASTCALL acosh(
		TEfloat val) {
		return std::acosh(val);
	}

	TILO_INLINE TEvoid acosh(
		TEfloat& out,
		TEfloat val) {
		out = acosh(val);
	}

	TEvoid TILO_VECTORCALL acosh_2(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_acosh_ps(_mm_set_ps(0, 0, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = acosh(val1);
			out[1] = acosh(val2);
		}
	}

	TEvoid TILO_VECTORCALL acosh_4(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_acosh_ps(_mm_set_ps(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = acosh(val1);
			out[1] = acosh(val2);
			out[2] = acosh(val3);
			out[3] = acosh(val4);
		}
	}

	TEvoid TILO_VECTORCALL acosh_8(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_ps(out, _mm256_acosh_ps(_mm256_set_ps(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			acosh_4(out,
				val1,
				val2,
				val3,
				val4);
			acosh_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	TEvoid TILO_VECTORCALL acosh_16(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8,
		TEfloat val9,
		TEfloat val10,
		TEfloat val11,
		TEfloat val12,
		TEfloat val13,
		TEfloat val14,
		TEfloat val15,
		TEfloat val16) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm512_store_ps(out, _mm512_acosh_ps(_mm512_set_ps(val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			acosh_8(out,
				val1,
				val2,
				val3,
				val4,
				val5,
				val6,
				val7,
				val8);
			acosh_8(&out[8],
				val9,
				val10,
				val11,
				val12,
				val13,
				val14,
				val15,
				val16);
		}
	}

	[[nodiscard]] TILO_INLINE TEdouble TILO_FASTCALL acosh(
		TEdouble val) {
		return std::acosh(val);
	}

	TILO_INLINE TEvoid acosh(
		TEdouble& out,
		TEdouble val) {
		out = acosh(val);
	}

	TEvoid TILO_VECTORCALL acosh_2(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_pd(out, _mm_acosh_pd(_mm_set_pd(val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = acosh(val1);
			out[1] = acosh(val2);
		}
	}

	TEvoid TILO_VECTORCALL acosh_4(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_pd(out, _mm256_acosh_pd(_mm256_set_pd(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			acosh_2(out,
				val1,
				val2);
			acosh_2(&out[2],
				val3,
				val4);
		}
	}

	TEvoid TILO_VECTORCALL acosh_8(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4,
		TEdouble val5,
		TEdouble val6,
		TEdouble val7,
		TEdouble val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm512_store_pd(out, _mm512_acosh_pd(_mm512_set_pd(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			acosh_4(out,
				val1,
				val2,
				val3,
				val4);
			acosh_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	[[nodiscard]] TILO_INLINE TEfloat TILO_FASTCALL atanh(
		TEfloat val) {
		return std::atanh(val);
	}

	TILO_INLINE TEvoid atanh(
		TEfloat& out,
		TEfloat val) {
		out = atanh(val);
	}

	TEvoid TILO_VECTORCALL atanh_2(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_atanh_ps(_mm_set_ps(0, 0, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = atanh(val1);
			out[1] = atanh(val2);
		}
	}

	TEvoid TILO_VECTORCALL atanh_4(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_atanh_ps(_mm_set_ps(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = atanh(val1);
			out[1] = atanh(val2);
			out[2] = atanh(val3);
			out[3] = atanh(val4);
		}
	}

	TEvoid TILO_VECTORCALL atanh_8(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_ps(out, _mm256_atanh_ps(_mm256_set_ps(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			atanh_4(out,
				val1,
				val2,
				val3,
				val4);
			atanh_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	TEvoid TILO_VECTORCALL atanh_16(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8,
		TEfloat val9,
		TEfloat val10,
		TEfloat val11,
		TEfloat val12,
		TEfloat val13,
		TEfloat val14,
		TEfloat val15,
		TEfloat val16) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm512_store_ps(out, _mm512_atanh_ps(_mm512_set_ps(val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			atanh_8(out,
				val1,
				val2,
				val3,
				val4,
				val5,
				val6,
				val7,
				val8);
			atanh_8(&out[8],
				val9,
				val10,
				val11,
				val12,
				val13,
				val14,
				val15,
				val16);
		}
	}

	[[nodiscard]] TILO_INLINE TEdouble TILO_FASTCALL atanh(
		TEdouble val) {
		return std::atanh(val);
	}

	TILO_INLINE TEvoid atanh(
		TEdouble& out,
		TEdouble val) {
		out = atanh(val);
	}

	TEvoid TILO_VECTORCALL atanh_2(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_pd(out, _mm_atanh_pd(_mm_set_pd(val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = atanh(val1);
			out[1] = atanh(val2);
		}
	}

	TEvoid TILO_VECTORCALL atanh_4(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_pd(out, _mm256_atanh_pd(_mm256_set_pd(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			atanh_2(out,
				val1,
				val2);
			atanh_2(&out[2],
				val3,
				val4);
		}
	}

	TEvoid TILO_VECTORCALL atanh_8(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4,
		TEdouble val5,
		TEdouble val6,
		TEdouble val7,
		TEdouble val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm512_store_pd(out, _mm512_atanh_pd(_mm512_set_pd(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			atanh_4(out,
				val1,
				val2,
				val3,
				val4);
			atanh_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	TEvoid TILO_VECTORCALL sincos_2(
		TEfloat* out1,
		TEfloat* out2,
		TEfloat val1,
		TEfloat val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			auto* _out2 = reinterpret_cast<TE4float*>(&out2);
			_mm_store_ps(out1, _mm_sincos_ps(_out2, _mm_set_ps(0, 0, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out1[0] = sin(val1);
			out1[1] = sin(val2);
			out2[0] = cos(val1);
			out2[1] = cos(val2);
		}
	}

	TEvoid TILO_VECTORCALL sincos_4(
		TEfloat* out1,
		TEfloat* out2,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			auto* _out2 = reinterpret_cast<TE4float*>(&out2);
			_mm_store_ps(out1, _mm_sincos_ps(_out2, _mm_set_ps(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out1[0] = sin(val1);
			out1[1] = sin(val2);
			out1[2] = sin(val3);
			out1[3] = sin(val4);
			out2[0] = cos(val1);
			out2[1] = cos(val2);
			out2[2] = cos(val3);
			out2[3] = cos(val4);
		}
	}

	TEvoid TILO_VECTORCALL sincos_8(
		TEfloat* out1,
		TEfloat* out2,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			auto* _out2 = reinterpret_cast<TE8float*>(&out2);
			_mm256_store_ps(out1, _mm256_sincos_ps(_out2, _mm256_set_ps(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			sincos_4(out1,
				out2,
				val1,
				val2,
				val3,
				val4);
			sincos_4(out1,
				out2,
				val5,
				val6,
				val7,
				val8);
		}
	}

	TEvoid TILO_VECTORCALL sincos_16(
		TEfloat* out1,
		TEfloat* out2,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8,
		TEfloat val9,
		TEfloat val10,
		TEfloat val11,
		TEfloat val12,
		TEfloat val13,
		TEfloat val14,
		TEfloat val15,
		TEfloat val16) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			auto* _out2 = reinterpret_cast<TE16float*>(&out2);
			_mm512_store_ps(out1, _mm512_sincos_ps(_out2, _mm512_set_ps(val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			sincos_4(out1,
				out2,
				val1,
				val2,
				val3,
				val4);
			sincos_4(out1,
				out2,
				val5,
				val6,
				val7,
				val8);
		}
	}

	TEvoid TILO_VECTORCALL sincos_2(
		TEdouble* out1,
		TEdouble* out2,
		TEdouble val1,
		TEdouble val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			auto* _out2 = reinterpret_cast<TE2double*>(&out2);
			_mm_store_pd(out1, _mm_sincos_pd(_out2, _mm_set_pd(val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out1[0] = sin(val1);
			out1[1] = sin(val2);
			out2[0] = cos(val1);
			out2[1] = cos(val2);
		}
	}

	TEvoid TILO_VECTORCALL sincos_4(
		TEdouble* out1,
		TEdouble* out2,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			auto* _out2 = reinterpret_cast<TE4double*>(&out2);
			_mm256_store_pd(out1, _mm256_sincos_pd(_out2, _mm256_set_pd(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			sincos_2(out1,
				out2,
				val1,
				val2);
			sincos_2(out1,
				out2,
				val1,
				val2);
		}
	}

	TEvoid TILO_VECTORCALL sincos_8(
		TEdouble* out1,
		TEdouble* out2,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4,
		TEdouble val5,
		TEdouble val6,
		TEdouble val7,
		TEdouble val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			auto* _out2 = reinterpret_cast<TE8double*>(&out2);
			_mm512_store_pd(out1, _mm512_sincos_pd(_out2, _mm512_set_pd(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			sincos_4(out1,
				out2,
				val1,
				val2,
				val3,
				val4);
			sincos_4(out1,
				out2,
				val5,
				val6,
				val7,
				val8);
		}
	}

	[[nodiscard]] TILO_INLINE TEfloat TILO_FASTCALL round(
		TEfloat val) {
		return std::round(val);
	}

	TILO_INLINE TEvoid round(
		TEfloat& out,
		TEfloat val) {
		out = round(val);
	}

	TEvoid TILO_VECTORCALL round_2(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_svml_round_ps(_mm_set_ps(0, 0, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = round(val1);
			out[1] = round(val2);
		}
	}

	TEvoid TILO_VECTORCALL round_4(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_svml_round_ps(_mm_set_ps(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = round(val1);
			out[1] = round(val2);
			out[2] = round(val3);
			out[3] = round(val4);
		}
	}

	TEvoid TILO_VECTORCALL round_8(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_ps(out, _mm256_svml_round_ps(_mm256_set_ps(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			round_4(out,
				val1,
				val2,
				val3,
				val4);
			round_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	TEvoid TILO_VECTORCALL round_16(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8,
		TEfloat val9,
		TEfloat val10,
		TEfloat val11,
		TEfloat val12,
		TEfloat val13,
		TEfloat val14,
		TEfloat val15,
		TEfloat val16) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm512_store_ps(out, _mm512_svml_round_ps(_mm512_set_ps(val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			round_8(out,
				val1,
				val2,
				val3,
				val4,
				val5,
				val6,
				val7,
				val8);
			round_8(&out[8],
				val9,
				val10,
				val11,
				val12,
				val13,
				val14,
				val15,
				val16);
		}
	}

	[[nodiscard]] TILO_INLINE TEdouble TILO_FASTCALL round(
		TEdouble val) {
		return std::round(val);
	}

	TILO_INLINE TEvoid round(
		TEdouble& out,
		TEdouble val) {
		out = round(val);
	}

	TEvoid TILO_VECTORCALL round_2(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_pd(out, _mm_svml_round_pd(_mm_set_pd(val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = round(val1);
			out[1] = round(val2);
		}
	}

	TEvoid TILO_VECTORCALL round_4(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_pd(out, _mm256_svml_round_pd(_mm256_set_pd(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			round_2(out,
				val1,
				val2);
			round_2(out,
				val3,
				val4);
		}
	}

	TEvoid TILO_VECTORCALL round_8(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4,
		TEdouble val5,
		TEdouble val6,
		TEdouble val7,
		TEdouble val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm512_store_pd(out, _mm512_svml_round_pd(_mm512_set_pd(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			round_4(out,
				val1,
				val2,
				val3,
				val4);
			round_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	[[nodiscard]] TILO_INLINE TEfloat TILO_FASTCALL floor(
		TEfloat val) {
		return std::floor(val);
	}

	TILO_INLINE TEvoid floor(
		TEfloat& out,
		TEfloat val) {
		out = floor(val);
	}

	TEvoid TILO_VECTORCALL floor_2(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_svml_floor_ps(_mm_set_ps(0, 0, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = floor(val1);
			out[1] = floor(val2);
		}
	}

	TEvoid TILO_VECTORCALL floor_4(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_svml_floor_ps(_mm_set_ps(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = floor(val1);
			out[1] = floor(val2);
			out[2] = floor(val3);
			out[3] = floor(val4);
		}
	}

	TEvoid TILO_VECTORCALL floor_8(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_ps(out, _mm256_svml_floor_ps(_mm256_set_ps(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			floor_4(out,
				val1,
				val2,
				val3,
				val4);
			floor_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	TEvoid TILO_VECTORCALL floor_16(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8,
		TEfloat val9,
		TEfloat val10,
		TEfloat val11,
		TEfloat val12,
		TEfloat val13,
		TEfloat val14,
		TEfloat val15,
		TEfloat val16) {
		floor_8(out,
			val1,
			val2,
			val3,
			val4,
			val5,
			val6,
			val7,
			val8);
		floor_8(&out[8],
			val9,
			val10,
			val11,
			val12,
			val13,
			val14,
			val15,
			val16);
	}

	[[nodiscard]] TILO_INLINE TEdouble TILO_FASTCALL floor(
		TEdouble val) {
		return std::floor(val);
	}

	TILO_INLINE TEvoid floor(
		TEdouble& out,
		TEdouble val) {
		out = floor(val);
	}

	TEvoid TILO_VECTORCALL floor_2(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_pd(out, _mm_svml_floor_pd(_mm_set_pd(val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = floor(val1);
			out[1] = floor(val2);
		}
	}

	TEvoid TILO_VECTORCALL floor_4(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_pd(out, _mm256_svml_floor_pd(_mm256_set_pd(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			floor_2(out,
				val1,
				val2);
			floor_2(out,
				val3,
				val4);
		}
	}

	TEvoid TILO_VECTORCALL floor_8(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4,
		TEdouble val5,
		TEdouble val6,
		TEdouble val7,
		TEdouble val8) {
		floor_4(out,
			val1,
			val2,
			val3,
			val4);
		floor_4(&out[4],
			val5,
			val6,
			val7,
			val8);
	}

	[[nodiscard]] TILO_INLINE TEfloat TILO_FASTCALL ceil(
		TEfloat val) {
		return std::ceil(val);
	}

	TILO_INLINE TEvoid ceil(
		TEfloat& out,
		TEfloat val) {
		out = ceil(val);
	}

	TEvoid TILO_VECTORCALL ceil_2(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_svml_ceil_ps(_mm_set_ps(0, 0, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = ceil(val1);
			out[1] = ceil(val2);
		}
	}

	TEvoid TILO_VECTORCALL ceil_4(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_ps(out, _mm_svml_ceil_ps(_mm_set_ps(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = ceil(val1);
			out[1] = ceil(val2);
			out[2] = ceil(val3);
			out[3] = ceil(val4);
		}
	}

	TEvoid TILO_VECTORCALL ceil_8(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_SVML_AVX_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_ps(out, _mm256_svml_ceil_ps(_mm256_set_ps(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			ceil_4(out,
				val1,
				val2,
				val3,
				val4);
			ceil_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	TEvoid TILO_VECTORCALL ceil_16(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8,
		TEfloat val9,
		TEfloat val10,
		TEfloat val11,
		TEfloat val12,
		TEfloat val13,
		TEfloat val14,
		TEfloat val15,
		TEfloat val16) {
		ceil_8(out,
			val1,
			val2,
			val3,
			val4,
			val5,
			val6,
			val7,
			val8);
		ceil_8(&out[8],
			val9,
			val10,
			val11,
			val12,
			val13,
			val14,
			val15,
			val16);
	}

	[[nodiscard]] TILO_INLINE TEdouble TILO_FASTCALL ceil(
		TEdouble val) {
		return std::ceil(val);
	}

	TILO_INLINE TEvoid ceil(
		TEdouble& out,
		TEdouble val) {
		out = ceil(val);
	}

	TEvoid TILO_VECTORCALL ceil_2(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_pd(out, _mm_svml_ceil_pd(_mm_set_pd(val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = ceil(val1);
			out[1] = ceil(val2);
		}
	}

	TEvoid TILO_VECTORCALL ceil_4(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4) {
		TILO_ASSUME(simdEnabledSvmlSupported)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm256_store_pd(out, _mm256_svml_ceil_pd(_mm256_set_pd(val4, val3, val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			ceil_2(out,
				val1,
				val2);
			ceil_2(out,
				val3,
				val4);
		}
	}

	TEvoid TILO_VECTORCALL ceil_8(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4,
		TEdouble val5,
		TEdouble val6,
		TEdouble val7,
		TEdouble val8) {
		ceil_4(out,
			val1,
			val2,
			val3,
			val4);
		ceil_4(&out[4],
			val5,
			val6,
			val7,
			val8);
	}

	__attribute__ ((noinline)) TEvoid TILO_VECTORCALL add_16(
		TEbyte* out,
		TEbyte val1_1,
		TEbyte val1_2,
		TEbyte val1_3,
		TEbyte val1_4,
		TEbyte val1_5,
		TEbyte val1_6,
		TEbyte val1_7,
		TEbyte val1_8,
		TEbyte val1_9,
		TEbyte val1_10,
		TEbyte val1_11,
		TEbyte val1_12,
		TEbyte val1_13,
		TEbyte val1_14,
		TEbyte val1_15,
		TEbyte val1_16,
		TEbyte val2_1,
		TEbyte val2_2,
		TEbyte val2_3,
		TEbyte val2_4,
		TEbyte val2_5,
		TEbyte val2_6,
		TEbyte val2_7,
		TEbyte val2_8,
		TEbyte val2_9,
		TEbyte val2_10,
		TEbyte val2_11,
		TEbyte val2_12,
		TEbyte val2_13,
		TEbyte val2_14,
		TEbyte val2_15,
		TEbyte val2_16) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSE2 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			TE16byte tmp = _mm_add_epi8(_mm_set_epi8(val1_16, val1_15, val1_14, val1_13, val1_12, val1_11, val1_10, val1_9, val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm_set_epi8(val2_16, val2_15, val2_14, val2_13, val2_12, val2_11, val2_10, val2_9, val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1));
			_mm_storeu_epi8(out, tmp);
			//_mm_storeu_epi8(out, _mm_add_epi8(_mm_set_epi8(val1_16, val1_15, val1_14, val1_13, val1_12, val1_11, val1_10, val1_9, val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
			//	_mm_set_epi8(val2_16, val2_15, val2_14, val2_13, val2_12, val2_11, val2_10, val2_9, val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = val1_1 + val2_1;
			out[1] = val1_2 + val2_2;
			out[2] = val1_3 + val2_3;
			out[3] = val1_4 + val2_4;
			out[4] = val1_5 + val2_5;
			out[5] = val1_6 + val2_6;
			out[6] = val1_7 + val2_7;
			out[7] = val1_8 + val2_8;
			out[8] = val1_9 + val2_9;
			out[9] = val1_10 + val2_10;
			out[10] = val1_11 + val2_11;
			out[11] = val1_12 + val2_12;
			out[12] = val1_13 + val2_13;
			out[13] = val1_14 + val2_14;
			out[14] = val1_15 + val2_15;
			out[15] = val1_16 + val2_16;
		}
	}

	TEvoid TILO_VECTORCALL add_32(
		TEbyte* out,
		TEbyte val1_1,
		TEbyte val1_2,
		TEbyte val1_3,
		TEbyte val1_4,
		TEbyte val1_5,
		TEbyte val1_6,
		TEbyte val1_7,
		TEbyte val1_8,
		TEbyte val1_9,
		TEbyte val1_10,
		TEbyte val1_11,
		TEbyte val1_12,
		TEbyte val1_13,
		TEbyte val1_14,
		TEbyte val1_15,
		TEbyte val1_16,
		TEbyte val1_17,
		TEbyte val1_18,
		TEbyte val1_19,
		TEbyte val1_20,
		TEbyte val1_21,
		TEbyte val1_22,
		TEbyte val1_23,
		TEbyte val1_24,
		TEbyte val1_25,
		TEbyte val1_26,
		TEbyte val1_27,
		TEbyte val1_28,
		TEbyte val1_29,
		TEbyte val1_30,
		TEbyte val1_31,
		TEbyte val1_32,
		TEbyte val2_1,
		TEbyte val2_2,
		TEbyte val2_3,
		TEbyte val2_4,
		TEbyte val2_5,
		TEbyte val2_6,
		TEbyte val2_7,
		TEbyte val2_8,
		TEbyte val2_9,
		TEbyte val2_10,
		TEbyte val2_11,
		TEbyte val2_12,
		TEbyte val2_13,
		TEbyte val2_14,
		TEbyte val2_15,
		TEbyte val2_16,
		TEbyte val2_17,
		TEbyte val2_18,
		TEbyte val2_19,
		TEbyte val2_20,
		TEbyte val2_21,
		TEbyte val2_22,
		TEbyte val2_23,
		TEbyte val2_24,
		TEbyte val2_25,
		TEbyte val2_26,
		TEbyte val2_27,
		TEbyte val2_28,
		TEbyte val2_29,
		TEbyte val2_30,
		TEbyte val2_31,
		TEbyte val2_32) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX2 && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm256_storeu_epi8(out, _mm256_add_epi8(_mm256_set_epi8(val1_32, val1_31, val1_30, val1_29, val1_28, val1_27, val1_26, val1_25, val1_24, val1_23, val1_22, val1_21, val1_20, val1_19, val1_18, val1_17, val1_16, val1_15, val1_14, val1_13, val1_12, val1_11, val1_10, val1_9, val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm256_set_epi8(val2_32, val2_31, val2_30, val2_29, val2_28, val2_27, val2_26, val2_25, val2_24, val2_23, val2_22, val2_21, val2_20, val2_19, val2_18, val2_17, val2_16, val2_15, val2_14, val2_13, val2_12, val2_11, val2_10, val2_9, val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			add_16(out,
				val1_1,
				val1_2,
				val1_3,
				val1_4,
				val1_5,
				val1_6,
				val1_7,
				val1_8,
				val1_9,
				val1_10,
				val1_11,
				val1_12,
				val1_13,
				val1_14,
				val1_15,
				val1_16,
				val2_1,
				val2_2,
				val2_3,
				val2_4,
				val2_5,
				val2_6,
				val2_7,
				val2_8,
				val2_9,
				val2_10,
				val2_11,
				val2_12,
				val2_13,
				val2_14,
				val2_15,
				val2_16);
			add_16(&out[16],
				val1_17,
				val1_18,
				val1_19,
				val1_20,
				val1_21,
				val1_22,
				val1_23,
				val1_24,
				val1_25,
				val1_26,
				val1_27,
				val1_28,
				val1_29,
				val1_30,
				val1_31,
				val1_31,
				val2_17,
				val2_18,
				val2_19,
				val2_20,
				val2_21,
				val2_22,
				val2_23,
				val2_24,
				val2_25,
				val2_26,
				val2_27,
				val2_28,
				val2_29,
				val2_30,
				val2_31,
				val2_31);
		}
	}

	TEvoid TILO_VECTORCALL add_64(
		TEbyte* out,
		TEbyte val1_1,
		TEbyte val1_2,
		TEbyte val1_3,
		TEbyte val1_4,
		TEbyte val1_5,
		TEbyte val1_6,
		TEbyte val1_7,
		TEbyte val1_8,
		TEbyte val1_9,
		TEbyte val1_10,
		TEbyte val1_11,
		TEbyte val1_12,
		TEbyte val1_13,
		TEbyte val1_14,
		TEbyte val1_15,
		TEbyte val1_16,
		TEbyte val1_17,
		TEbyte val1_18,
		TEbyte val1_19,
		TEbyte val1_20,
		TEbyte val1_21,
		TEbyte val1_22,
		TEbyte val1_23,
		TEbyte val1_24,
		TEbyte val1_25,
		TEbyte val1_26,
		TEbyte val1_27,
		TEbyte val1_28,
		TEbyte val1_29,
		TEbyte val1_30,
		TEbyte val1_31,
		TEbyte val1_32,
		TEbyte val1_33,
		TEbyte val1_34,
		TEbyte val1_35,
		TEbyte val1_36,
		TEbyte val1_37,
		TEbyte val1_38,
		TEbyte val1_39,
		TEbyte val1_40,
		TEbyte val1_41,
		TEbyte val1_42,
		TEbyte val1_43,
		TEbyte val1_44,
		TEbyte val1_45,
		TEbyte val1_46,
		TEbyte val1_47,
		TEbyte val1_48,
		TEbyte val1_49,
		TEbyte val1_50,
		TEbyte val1_51,
		TEbyte val1_52,
		TEbyte val1_53,
		TEbyte val1_54,
		TEbyte val1_55,
		TEbyte val1_56,
		TEbyte val1_57,
		TEbyte val1_58,
		TEbyte val1_59,
		TEbyte val1_60,
		TEbyte val1_61,
		TEbyte val1_62,
		TEbyte val1_63,
		TEbyte val1_64,
		TEbyte val2_1,
		TEbyte val2_2,
		TEbyte val2_3,
		TEbyte val2_4,
		TEbyte val2_5,
		TEbyte val2_6,
		TEbyte val2_7,
		TEbyte val2_8,
		TEbyte val2_9,
		TEbyte val2_10,
		TEbyte val2_11,
		TEbyte val2_12,
		TEbyte val2_13,
		TEbyte val2_14,
		TEbyte val2_15,
		TEbyte val2_16,
		TEbyte val2_17,
		TEbyte val2_18,
		TEbyte val2_19,
		TEbyte val2_20,
		TEbyte val2_21,
		TEbyte val2_22,
		TEbyte val2_23,
		TEbyte val2_24,
		TEbyte val2_25,
		TEbyte val2_26,
		TEbyte val2_27,
		TEbyte val2_28,
		TEbyte val2_29,
		TEbyte val2_30,
		TEbyte val2_31,
		TEbyte val2_32,
		TEbyte val2_33,
		TEbyte val2_34,
		TEbyte val2_35,
		TEbyte val2_36,
		TEbyte val2_37,
		TEbyte val2_38,
		TEbyte val2_39,
		TEbyte val2_40,
		TEbyte val2_41,
		TEbyte val2_42,
		TEbyte val2_43,
		TEbyte val2_44,
		TEbyte val2_45,
		TEbyte val2_46,
		TEbyte val2_47,
		TEbyte val2_48,
		TEbyte val2_49,
		TEbyte val2_50,
		TEbyte val2_51,
		TEbyte val2_52,
		TEbyte val2_53,
		TEbyte val2_54,
		TEbyte val2_55,
		TEbyte val2_56,
		TEbyte val2_57,
		TEbyte val2_58,
		TEbyte val2_59,
		TEbyte val2_60,
		TEbyte val2_61,
		TEbyte val2_62,
		TEbyte val2_63,
		TEbyte val2_64) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm512_storeu_epi8(out, _mm512_add_epi8(_mm512_set_epi8(val1_64, val1_63, val1_62, val1_61, val1_60, val1_59, val1_58, val1_57, val1_56, val1_55, val1_54, val1_53, val1_52, val1_51, val1_50, val1_49, val1_48, val1_47, val1_46, val1_45, val1_44, val1_43, val1_42, val1_41, val1_40, val1_39, val1_38, val1_37, val1_36, val1_35, val1_34, val1_33, val1_32, val1_31, val1_30, val1_29, val1_28, val1_27, val1_26, val1_25, val1_24, val1_23, val1_22, val1_21, val1_20, val1_19, val1_18, val1_17, val1_16, val1_15, val1_14, val1_13, val1_12, val1_11, val1_10, val1_9, val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm512_set_epi8(val2_64, val2_63, val2_62, val2_61, val2_60, val2_59, val2_58, val2_57, val2_56, val2_55, val2_54, val2_53, val2_52, val2_51, val2_50, val2_49, val2_48, val2_47, val2_46, val2_45, val2_44, val2_43, val2_42, val2_41, val2_40, val2_39, val2_38, val2_37, val2_36, val2_35, val2_34, val2_33, val2_32, val2_31, val2_30, val2_29, val2_28, val2_27, val2_26, val2_25, val2_24, val2_23, val2_22, val2_21, val2_20, val2_19, val2_18, val2_17, val2_16, val2_15, val2_14, val2_13, val2_12, val2_11, val2_10, val2_9, val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			add_32(out,
				val1_1,
				val1_2,
				val1_3,
				val1_4,
				val1_5,
				val1_6,
				val1_7,
				val1_8,
				val1_9,
				val1_10,
				val1_11,
				val1_12,
				val1_13,
				val1_14,
				val1_15,
				val1_16,
				val1_17,
				val1_18,
				val1_19,
				val1_20,
				val1_21,
				val1_22,
				val1_23,
				val1_24,
				val1_25,
				val1_26,
				val1_27,
				val1_28,
				val1_29,
				val1_30,
				val1_31,
				val1_32,
				val2_1,
				val2_2,
				val2_3,
				val2_4,
				val2_5,
				val2_6,
				val2_7,
				val2_8,
				val2_9,
				val2_10,
				val2_11,
				val2_12,
				val2_13,
				val2_14,
				val2_15,
				val2_16,
				val2_17,
				val2_18,
				val2_19,
				val2_20,
				val2_21,
				val2_22,
				val2_23,
				val2_24,
				val2_25,
				val2_26,
				val2_27,
				val2_28,
				val2_29,
				val2_30,
				val2_31,
				val2_32);
			add_32(&out[32],
				val1_33,
				val1_34,
				val1_35,
				val1_36,
				val1_37,
				val1_38,
				val1_39,
				val1_40,
				val1_41,
				val1_42,
				val1_43,
				val1_44,
				val1_45,
				val1_46,
				val1_47,
				val1_48,
				val1_49,
				val1_50,
				val1_51,
				val1_52,
				val1_53,
				val1_54,
				val1_55,
				val1_56,
				val1_57,
				val1_58,
				val1_59,
				val1_60,
				val1_61,
				val1_62,
				val1_63,
				val1_64,
				val2_33,
				val2_34,
				val2_35,
				val2_36,
				val2_37,
				val2_38,
				val2_39,
				val2_40,
				val2_41,
				val2_42,
				val2_43,
				val2_44,
				val2_45,
				val2_46,
				val2_47,
				val2_48,
				val2_49,
				val2_50,
				val2_51,
				val2_52,
				val2_53,
				val2_54,
				val2_55,
				val2_56,
				val2_57,
				val2_58,
				val2_59,
				val2_60,
				val2_61,
				val2_62,
				val2_63,
				val2_64
			);
		}
	}

	TEvoid TILO_VECTORCALL add_8(
		TEshort* out,
		TEshort val1_1,
		TEshort val1_2,
		TEshort val1_3,
		TEshort val1_4,
		TEshort val1_5,
		TEshort val1_6,
		TEshort val1_7,
		TEshort val1_8,
		TEshort val2_1,
		TEshort val2_2,
		TEshort val2_3,
		TEshort val2_4,
		TEshort val2_5,
		TEshort val2_6,
		TEshort val2_7,
		TEshort val2_8) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSE2 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_storeu_epi16(out, _mm_add_epi16(_mm_set_epi16(val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm_set_epi16(val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = val1_1 + val2_1;
			out[1] = val1_2 + val2_2;
			out[2] = val1_3 + val2_3;
			out[3] = val1_4 + val2_4;
			out[4] = val1_5 + val2_5;
			out[5] = val1_6 + val2_6;
			out[6] = val1_7 + val2_7;
			out[7] = val1_8 + val2_8;
		}
	}

	TEvoid TILO_VECTORCALL add_16(
		TEshort* out,
		TEshort val1_1,
		TEshort val1_2,
		TEshort val1_3,
		TEshort val1_4,
		TEshort val1_5,
		TEshort val1_6,
		TEshort val1_7,
		TEshort val1_8,
		TEshort val1_9,
		TEshort val1_10,
		TEshort val1_11,
		TEshort val1_12,
		TEshort val1_13,
		TEshort val1_14,
		TEshort val1_15,
		TEshort val1_16,
		TEshort val2_1,
		TEshort val2_2,
		TEshort val2_3,
		TEshort val2_4,
		TEshort val2_5,
		TEshort val2_6,
		TEshort val2_7,
		TEshort val2_8,
		TEshort val2_9,
		TEshort val2_10,
		TEshort val2_11,
		TEshort val2_12,
		TEshort val2_13,
		TEshort val2_14,
		TEshort val2_15,
		TEshort val2_16) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX2 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm256_storeu_epi16(out, _mm256_add_epi16(_mm256_set_epi16(val1_16, val1_15, val1_14, val1_13, val1_12, val1_11, val1_10, val1_9, val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm256_set_epi16(val2_16, val2_15, val2_14, val2_13, val2_12, val2_11, val2_10, val2_9, val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			add_8(out,
				val1_1,
				val1_2,
				val1_3,
				val1_4,
				val1_5,
				val1_6,
				val1_7,
				val1_8,
				val2_1,
				val2_2,
				val2_3,
				val2_4,
				val2_5,
				val2_6,
				val2_7,
				val2_8);
			add_8(&out[8],
				val1_9,
				val1_10,
				val1_11,
				val1_12,
				val1_13,
				val1_14,
				val1_15,
				val1_16,
				val2_9,
				val2_10,
				val2_11,
				val2_12,
				val2_13,
				val2_14,
				val2_15,
				val2_16);
		}
	}

	TEvoid TILO_VECTORCALL add_32(
		TEshort* out,
		TEshort val1_1,
		TEshort val1_2,
		TEshort val1_3,
		TEshort val1_4,
		TEshort val1_5,
		TEshort val1_6,
		TEshort val1_7,
		TEshort val1_8,
		TEshort val1_9,
		TEshort val1_10,
		TEshort val1_11,
		TEshort val1_12,
		TEshort val1_13,
		TEshort val1_14,
		TEshort val1_15,
		TEshort val1_16,
		TEshort val1_17,
		TEshort val1_18,
		TEshort val1_19,
		TEshort val1_20,
		TEshort val1_21,
		TEshort val1_22,
		TEshort val1_23,
		TEshort val1_24,
		TEshort val1_25,
		TEshort val1_26,
		TEshort val1_27,
		TEshort val1_28,
		TEshort val1_29,
		TEshort val1_30,
		TEshort val1_31,
		TEshort val1_32,
		TEshort val2_1,
		TEshort val2_2,
		TEshort val2_3,
		TEshort val2_4,
		TEshort val2_5,
		TEshort val2_6,
		TEshort val2_7,
		TEshort val2_8,
		TEshort val2_9,
		TEshort val2_10,
		TEshort val2_11,
		TEshort val2_12,
		TEshort val2_13,
		TEshort val2_14,
		TEshort val2_15,
		TEshort val2_16,
		TEshort val2_17,
		TEshort val2_18,
		TEshort val2_19,
		TEshort val2_20,
		TEshort val2_21,
		TEshort val2_22,
		TEshort val2_23,
		TEshort val2_24,
		TEshort val2_25,
		TEshort val2_26,
		TEshort val2_27,
		TEshort val2_28,
		TEshort val2_29,
		TEshort val2_30,
		TEshort val2_31,
		TEshort val2_32) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm512_storeu_epi16(out, _mm512_add_epi16(_mm512_set_epi16(val1_32, val1_31, val1_30, val1_29, val1_28, val1_27, val1_26, val1_25, val1_24, val1_23, val1_22, val1_21, val1_20, val1_19, val1_18, val1_17, val1_16, val1_15, val1_14, val1_13, val1_12, val1_11, val1_10, val1_9, val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm512_set_epi16(val2_32, val2_31, val2_30, val2_29, val2_28, val2_27, val2_26, val2_25, val2_24, val2_23, val2_22, val2_21, val2_20, val2_19, val2_18, val2_17, val2_16, val2_15, val2_14, val2_13, val2_12, val2_11, val2_10, val2_9, val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			add_16(out,
				val1_1,
				val1_2,
				val1_3,
				val1_4,
				val1_5,
				val1_6,
				val1_7,
				val1_8,
				val1_9,
				val1_10,
				val1_11,
				val1_12,
				val1_13,
				val1_14,
				val1_15,
				val1_16,
				val2_1,
				val2_2,
				val2_3,
				val2_4,
				val2_5,
				val2_6,
				val2_7,
				val2_8,
				val2_9,
				val2_10,
				val2_11,
				val2_12,
				val2_13,
				val2_14,
				val2_15,
				val2_16);
			add_16(&out[16],
				val1_17,
				val1_18,
				val1_19,
				val1_20,
				val1_21,
				val1_22,
				val1_23,
				val1_24,
				val1_25,
				val1_26,
				val1_27,
				val1_28,
				val1_29,
				val1_30,
				val1_31,
				val1_31,
				val2_17,
				val2_18,
				val2_19,
				val2_20,
				val2_21,
				val2_22,
				val2_23,
				val2_24,
				val2_25,
				val2_26,
				val2_27,
				val2_28,
				val2_29,
				val2_30,
				val2_31,
				val2_31);
		}
	}

	TEvoid TILO_VECTORCALL add_4(
		TEint* out,
		TEint val1_1,
		TEint val1_2,
		TEint val1_3,
		TEint val1_4,
		TEint val2_1,
		TEint val2_2,
		TEint val2_3,
		TEint val2_4) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSE2 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_storeu_epi32(out, _mm_add_epi32(_mm_set_epi32(val1_4, val1_3, val1_2, val1_1),
				_mm_set_epi32(val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = val1_1 + val2_1;
			out[1] = val1_2 + val2_2;
			out[2] = val1_3 + val2_3;
			out[3] = val1_4 + val2_4;
		}
	}

	TEvoid TILO_VECTORCALL add_8(
		TEint* out,
		TEint val1_1,
		TEint val1_2,
		TEint val1_3,
		TEint val1_4,
		TEint val1_5,
		TEint val1_6,
		TEint val1_7,
		TEint val1_8,
		TEint val2_1,
		TEint val2_2,
		TEint val2_3,
		TEint val2_4,
		TEint val2_5,
		TEint val2_6,
		TEint val2_7,
		TEint val2_8) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX2 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm256_storeu_epi32(out, _mm256_add_epi32(_mm256_set_epi32(val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm256_set_epi32(val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			add_4(out,
				val1_1,
				val1_2,
				val1_3,
				val1_4,
				val2_1,
				val2_2,
				val2_3,
				val2_4);
			add_4(&out[4],
				val1_5,
				val1_6,
				val1_7,
				val1_8,
				val2_5,
				val2_6,
				val2_7,
				val2_8);
		}
	}

	TEvoid TILO_VECTORCALL add_16(
		TEint* out,
		TEint val1_1,
		TEint val1_2,
		TEint val1_3,
		TEint val1_4,
		TEint val1_5,
		TEint val1_6,
		TEint val1_7,
		TEint val1_8,
		TEint val1_9,
		TEint val1_10,
		TEint val1_11,
		TEint val1_12,
		TEint val1_13,
		TEint val1_14,
		TEint val1_15,
		TEint val1_16,
		TEint val2_1,
		TEint val2_2,
		TEint val2_3,
		TEint val2_4,
		TEint val2_5,
		TEint val2_6,
		TEint val2_7,
		TEint val2_8,
		TEint val2_9,
		TEint val2_10,
		TEint val2_11,
		TEint val2_12,
		TEint val2_13,
		TEint val2_14,
		TEint val2_15,
		TEint val2_16) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm512_storeu_epi32(out, _mm512_add_epi32(_mm512_set_epi32(val1_16, val1_15, val1_14, val1_13, val1_12, val1_11, val1_10, val1_9, val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm512_set_epi32(val2_16, val2_15, val2_14, val2_13, val2_12, val2_11, val2_10, val2_9, val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			add_8(out,
				val1_1,
				val1_2,
				val1_3,
				val1_4,
				val1_5,
				val1_6,
				val1_7,
				val1_8,
				val2_1,
				val2_2,
				val2_3,
				val2_4,
				val2_5,
				val2_6,
				val2_7,
				val2_8);
			add_8(&out[8],
				val1_9,
				val1_10,
				val1_11,
				val1_12,
				val1_13,
				val1_14,
				val1_15,
				val1_16,
				val2_9,
				val2_10,
				val2_11,
				val2_12,
				val2_13,
				val2_14,
				val2_15,
				val2_16);
		}
	}

	TEvoid TILO_VECTORCALL add_2(
		TElong* out,
		TElong val1_1,
		TElong val1_2,
		TElong val2_1,
		TElong val2_2) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSE2 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_storeu_epi64(out, _mm_add_epi64(_mm_set_epi64x(val1_2, val1_1),
				_mm_set_epi64x(val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = val1_1 + val2_1;
			out[1] = val1_2 + val2_2;
		}
	}

	TEvoid TILO_VECTORCALL add_4(
		TElong* out,
		TElong val1_1,
		TElong val1_2,
		TElong val1_3,
		TElong val1_4,
		TElong val2_1,
		TElong val2_2,
		TElong val2_3,
		TElong val2_4) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX && cpuInfo->flags.AVX2 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm256_storeu_epi64(out, _mm256_add_epi64(_mm256_set_epi64x(val1_4, val1_3, val1_2, val1_1),
				_mm256_set_epi64x(val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			add_2(out,
				val1_1,
				val1_2,
				val2_1,
				val2_2);
			add_2(&out[2],
				val1_3,
				val1_4,
				val2_3,
				val2_4);
		}
	}

	TEvoid TILO_VECTORCALL add_8(
		TElong* out,
		TElong val1_1,
		TElong val1_2,
		TElong val1_3,
		TElong val1_4,
		TElong val1_5,
		TElong val1_6,
		TElong val1_7,
		TElong val1_8,
		TElong val2_1,
		TElong val2_2,
		TElong val2_3,
		TElong val2_4,
		TElong val2_5,
		TElong val2_6,
		TElong val2_7,
		TElong val2_8) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX512F && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm512_storeu_epi64(out, _mm512_add_epi64(_mm512_set_epi64(val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm512_set_epi64(val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			add_4(out,
				val1_1,
				val1_2,
				val1_3,
				val1_4,
				val2_1,
				val2_2,
				val2_3,
				val2_4);
			add_4(&out[4],
				val1_5,
				val1_6,
				val1_7,
				val1_8,
				val2_5,
				val2_6,
				val2_7,
				val2_8);
		}
	}

	TEvoid TILO_VECTORCALL sub_16(
		TEbyte* out,
		TEbyte val1_1,
		TEbyte val1_2,
		TEbyte val1_3,
		TEbyte val1_4,
		TEbyte val1_5,
		TEbyte val1_6,
		TEbyte val1_7,
		TEbyte val1_8,
		TEbyte val1_9,
		TEbyte val1_10,
		TEbyte val1_11,
		TEbyte val1_12,
		TEbyte val1_13,
		TEbyte val1_14,
		TEbyte val1_15,
		TEbyte val1_16,
		TEbyte val2_1,
		TEbyte val2_2,
		TEbyte val2_3,
		TEbyte val2_4,
		TEbyte val2_5,
		TEbyte val2_6,
		TEbyte val2_7,
		TEbyte val2_8,
		TEbyte val2_9,
		TEbyte val2_10,
		TEbyte val2_11,
		TEbyte val2_12,
		TEbyte val2_13,
		TEbyte val2_14,
		TEbyte val2_15,
		TEbyte val2_16) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSE2 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_storeu_epi8(out, _mm_sub_epi8(_mm_set_epi8(val1_16, val1_15, val1_14, val1_13, val1_12, val1_11, val1_10, val1_9, val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm_set_epi8(val2_16, val2_15, val2_14, val2_13, val2_12, val2_11, val2_10, val2_9, val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = val1_1 + val2_1;
			out[1] = val1_2 + val2_2;
			out[2] = val1_3 + val2_3;
			out[3] = val1_4 + val2_4;
			out[4] = val1_5 + val2_5;
			out[5] = val1_6 + val2_6;
			out[6] = val1_7 + val2_7;
			out[7] = val1_8 + val2_8;
			out[8] = val1_9 + val2_9;
			out[9] = val1_10 + val2_10;
			out[10] = val1_11 + val2_11;
			out[11] = val1_12 + val2_12;
			out[12] = val1_13 + val2_13;
			out[13] = val1_14 + val2_14;
			out[14] = val1_15 + val2_15;
			out[15] = val1_16 + val2_16;
		}
	}

	TEvoid TILO_VECTORCALL sub_32(
		TEbyte* out,
		TEbyte val1_1,
		TEbyte val1_2,
		TEbyte val1_3,
		TEbyte val1_4,
		TEbyte val1_5,
		TEbyte val1_6,
		TEbyte val1_7,
		TEbyte val1_8,
		TEbyte val1_9,
		TEbyte val1_10,
		TEbyte val1_11,
		TEbyte val1_12,
		TEbyte val1_13,
		TEbyte val1_14,
		TEbyte val1_15,
		TEbyte val1_16,
		TEbyte val1_17,
		TEbyte val1_18,
		TEbyte val1_19,
		TEbyte val1_20,
		TEbyte val1_21,
		TEbyte val1_22,
		TEbyte val1_23,
		TEbyte val1_24,
		TEbyte val1_25,
		TEbyte val1_26,
		TEbyte val1_27,
		TEbyte val1_28,
		TEbyte val1_29,
		TEbyte val1_30,
		TEbyte val1_31,
		TEbyte val1_32,
		TEbyte val2_1,
		TEbyte val2_2,
		TEbyte val2_3,
		TEbyte val2_4,
		TEbyte val2_5,
		TEbyte val2_6,
		TEbyte val2_7,
		TEbyte val2_8,
		TEbyte val2_9,
		TEbyte val2_10,
		TEbyte val2_11,
		TEbyte val2_12,
		TEbyte val2_13,
		TEbyte val2_14,
		TEbyte val2_15,
		TEbyte val2_16,
		TEbyte val2_17,
		TEbyte val2_18,
		TEbyte val2_19,
		TEbyte val2_20,
		TEbyte val2_21,
		TEbyte val2_22,
		TEbyte val2_23,
		TEbyte val2_24,
		TEbyte val2_25,
		TEbyte val2_26,
		TEbyte val2_27,
		TEbyte val2_28,
		TEbyte val2_29,
		TEbyte val2_30,
		TEbyte val2_31,
		TEbyte val2_32) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX2 && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm256_storeu_epi8(out, _mm256_sub_epi8(_mm256_set_epi8(val1_32, val1_31, val1_30, val1_29, val1_28, val1_27, val1_26, val1_25, val1_24, val1_23, val1_22, val1_21, val1_20, val1_19, val1_18, val1_17, val1_16, val1_15, val1_14, val1_13, val1_12, val1_11, val1_10, val1_9, val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm256_set_epi8(val2_32, val2_31, val2_30, val2_29, val2_28, val2_27, val2_26, val2_25, val2_24, val2_23, val2_22, val2_21, val2_20, val2_19, val2_18, val2_17, val2_16, val2_15, val2_14, val2_13, val2_12, val2_11, val2_10, val2_9, val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			sub_16(out,
				val1_1,
				val1_2,
				val1_3,
				val1_4,
				val1_5,
				val1_6,
				val1_7,
				val1_8,
				val1_9,
				val1_10,
				val1_11,
				val1_12,
				val1_13,
				val1_14,
				val1_15,
				val1_16,
				val2_1,
				val2_2,
				val2_3,
				val2_4,
				val2_5,
				val2_6,
				val2_7,
				val2_8,
				val2_9,
				val2_10,
				val2_11,
				val2_12,
				val2_13,
				val2_14,
				val2_15,
				val2_16);
			sub_16(&out[16],
				val1_17,
				val1_18,
				val1_19,
				val1_20,
				val1_21,
				val1_22,
				val1_23,
				val1_24,
				val1_25,
				val1_26,
				val1_27,
				val1_28,
				val1_29,
				val1_30,
				val1_31,
				val1_31,
				val2_17,
				val2_18,
				val2_19,
				val2_20,
				val2_21,
				val2_22,
				val2_23,
				val2_24,
				val2_25,
				val2_26,
				val2_27,
				val2_28,
				val2_29,
				val2_30,
				val2_31,
				val2_31);
		}
	}

	TEvoid TILO_VECTORCALL sub_64(
		TEbyte* out,
		TEbyte val1_1,
		TEbyte val1_2,
		TEbyte val1_3,
		TEbyte val1_4,
		TEbyte val1_5,
		TEbyte val1_6,
		TEbyte val1_7,
		TEbyte val1_8,
		TEbyte val1_9,
		TEbyte val1_10,
		TEbyte val1_11,
		TEbyte val1_12,
		TEbyte val1_13,
		TEbyte val1_14,
		TEbyte val1_15,
		TEbyte val1_16,
		TEbyte val1_17,
		TEbyte val1_18,
		TEbyte val1_19,
		TEbyte val1_20,
		TEbyte val1_21,
		TEbyte val1_22,
		TEbyte val1_23,
		TEbyte val1_24,
		TEbyte val1_25,
		TEbyte val1_26,
		TEbyte val1_27,
		TEbyte val1_28,
		TEbyte val1_29,
		TEbyte val1_30,
		TEbyte val1_31,
		TEbyte val1_32,
		TEbyte val1_33,
		TEbyte val1_34,
		TEbyte val1_35,
		TEbyte val1_36,
		TEbyte val1_37,
		TEbyte val1_38,
		TEbyte val1_39,
		TEbyte val1_40,
		TEbyte val1_41,
		TEbyte val1_42,
		TEbyte val1_43,
		TEbyte val1_44,
		TEbyte val1_45,
		TEbyte val1_46,
		TEbyte val1_47,
		TEbyte val1_48,
		TEbyte val1_49,
		TEbyte val1_50,
		TEbyte val1_51,
		TEbyte val1_52,
		TEbyte val1_53,
		TEbyte val1_54,
		TEbyte val1_55,
		TEbyte val1_56,
		TEbyte val1_57,
		TEbyte val1_58,
		TEbyte val1_59,
		TEbyte val1_60,
		TEbyte val1_61,
		TEbyte val1_62,
		TEbyte val1_63,
		TEbyte val1_64,
		TEbyte val2_1,
		TEbyte val2_2,
		TEbyte val2_3,
		TEbyte val2_4,
		TEbyte val2_5,
		TEbyte val2_6,
		TEbyte val2_7,
		TEbyte val2_8,
		TEbyte val2_9,
		TEbyte val2_10,
		TEbyte val2_11,
		TEbyte val2_12,
		TEbyte val2_13,
		TEbyte val2_14,
		TEbyte val2_15,
		TEbyte val2_16,
		TEbyte val2_17,
		TEbyte val2_18,
		TEbyte val2_19,
		TEbyte val2_20,
		TEbyte val2_21,
		TEbyte val2_22,
		TEbyte val2_23,
		TEbyte val2_24,
		TEbyte val2_25,
		TEbyte val2_26,
		TEbyte val2_27,
		TEbyte val2_28,
		TEbyte val2_29,
		TEbyte val2_30,
		TEbyte val2_31,
		TEbyte val2_32,
		TEbyte val2_33,
		TEbyte val2_34,
		TEbyte val2_35,
		TEbyte val2_36,
		TEbyte val2_37,
		TEbyte val2_38,
		TEbyte val2_39,
		TEbyte val2_40,
		TEbyte val2_41,
		TEbyte val2_42,
		TEbyte val2_43,
		TEbyte val2_44,
		TEbyte val2_45,
		TEbyte val2_46,
		TEbyte val2_47,
		TEbyte val2_48,
		TEbyte val2_49,
		TEbyte val2_50,
		TEbyte val2_51,
		TEbyte val2_52,
		TEbyte val2_53,
		TEbyte val2_54,
		TEbyte val2_55,
		TEbyte val2_56,
		TEbyte val2_57,
		TEbyte val2_58,
		TEbyte val2_59,
		TEbyte val2_60,
		TEbyte val2_61,
		TEbyte val2_62,
		TEbyte val2_63,
		TEbyte val2_64) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm512_storeu_epi8(out, _mm512_sub_epi8(_mm512_set_epi8(val1_64, val1_63, val1_62, val1_61, val1_60, val1_59, val1_58, val1_57, val1_56, val1_55, val1_54, val1_53, val1_52, val1_51, val1_50, val1_49, val1_48, val1_47, val1_46, val1_45, val1_44, val1_43, val1_42, val1_41, val1_40, val1_39, val1_38, val1_37, val1_36, val1_35, val1_34, val1_33, val1_32, val1_31, val1_30, val1_29, val1_28, val1_27, val1_26, val1_25, val1_24, val1_23, val1_22, val1_21, val1_20, val1_19, val1_18, val1_17, val1_16, val1_15, val1_14, val1_13, val1_12, val1_11, val1_10, val1_9, val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm512_set_epi8(val2_64, val2_63, val2_62, val2_61, val2_60, val2_59, val2_58, val2_57, val2_56, val2_55, val2_54, val2_53, val2_52, val2_51, val2_50, val2_49, val2_48, val2_47, val2_46, val2_45, val2_44, val2_43, val2_42, val2_41, val2_40, val2_39, val2_38, val2_37, val2_36, val2_35, val2_34, val2_33, val2_32, val2_31, val2_30, val2_29, val2_28, val2_27, val2_26, val2_25, val2_24, val2_23, val2_22, val2_21, val2_20, val2_19, val2_18, val2_17, val2_16, val2_15, val2_14, val2_13, val2_12, val2_11, val2_10, val2_9, val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			sub_32(out,
				val1_1,
				val1_2,
				val1_3,
				val1_4,
				val1_5,
				val1_6,
				val1_7,
				val1_8,
				val1_9,
				val1_10,
				val1_11,
				val1_12,
				val1_13,
				val1_14,
				val1_15,
				val1_16,
				val1_17,
				val1_18,
				val1_19,
				val1_20,
				val1_21,
				val1_22,
				val1_23,
				val1_24,
				val1_25,
				val1_26,
				val1_27,
				val1_28,
				val1_29,
				val1_30,
				val1_31,
				val1_32,
				val2_1,
				val2_2,
				val2_3,
				val2_4,
				val2_5,
				val2_6,
				val2_7,
				val2_8,
				val2_9,
				val2_10,
				val2_11,
				val2_12,
				val2_13,
				val2_14,
				val2_15,
				val2_16,
				val2_17,
				val2_18,
				val2_19,
				val2_20,
				val2_21,
				val2_22,
				val2_23,
				val2_24,
				val2_25,
				val2_26,
				val2_27,
				val2_28,
				val2_29,
				val2_30,
				val2_31,
				val2_32);
			sub_32(&out[32],
				val1_33,
				val1_34,
				val1_35,
				val1_36,
				val1_37,
				val1_38,
				val1_39,
				val1_40,
				val1_41,
				val1_42,
				val1_43,
				val1_44,
				val1_45,
				val1_46,
				val1_47,
				val1_48,
				val1_49,
				val1_50,
				val1_51,
				val1_52,
				val1_53,
				val1_54,
				val1_55,
				val1_56,
				val1_57,
				val1_58,
				val1_59,
				val1_60,
				val1_61,
				val1_62,
				val1_63,
				val1_64,
				val2_33,
				val2_34,
				val2_35,
				val2_36,
				val2_37,
				val2_38,
				val2_39,
				val2_40,
				val2_41,
				val2_42,
				val2_43,
				val2_44,
				val2_45,
				val2_46,
				val2_47,
				val2_48,
				val2_49,
				val2_50,
				val2_51,
				val2_52,
				val2_53,
				val2_54,
				val2_55,
				val2_56,
				val2_57,
				val2_58,
				val2_59,
				val2_60,
				val2_61,
				val2_62,
				val2_63,
				val2_64
			);
		}
	}

	TEvoid TILO_VECTORCALL sub_8(
		TEshort* out,
		TEshort val1_1,
		TEshort val1_2,
		TEshort val1_3,
		TEshort val1_4,
		TEshort val1_5,
		TEshort val1_6,
		TEshort val1_7,
		TEshort val1_8,
		TEshort val2_1,
		TEshort val2_2,
		TEshort val2_3,
		TEshort val2_4,
		TEshort val2_5,
		TEshort val2_6,
		TEshort val2_7,
		TEshort val2_8) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSE2 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_storeu_epi16(out, _mm_sub_epi16(_mm_set_epi16(val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm_set_epi16(val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = val1_1 + val2_1;
			out[1] = val1_2 + val2_2;
			out[2] = val1_3 + val2_3;
			out[3] = val1_4 + val2_4;
			out[4] = val1_5 + val2_5;
			out[5] = val1_6 + val2_6;
			out[6] = val1_7 + val2_7;
			out[7] = val1_8 + val2_8;
		}
	}

	TEvoid TILO_VECTORCALL sub_16(
		TEshort* out,
		TEshort val1_1,
		TEshort val1_2,
		TEshort val1_3,
		TEshort val1_4,
		TEshort val1_5,
		TEshort val1_6,
		TEshort val1_7,
		TEshort val1_8,
		TEshort val1_9,
		TEshort val1_10,
		TEshort val1_11,
		TEshort val1_12,
		TEshort val1_13,
		TEshort val1_14,
		TEshort val1_15,
		TEshort val1_16,
		TEshort val2_1,
		TEshort val2_2,
		TEshort val2_3,
		TEshort val2_4,
		TEshort val2_5,
		TEshort val2_6,
		TEshort val2_7,
		TEshort val2_8,
		TEshort val2_9,
		TEshort val2_10,
		TEshort val2_11,
		TEshort val2_12,
		TEshort val2_13,
		TEshort val2_14,
		TEshort val2_15,
		TEshort val2_16) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX2 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm256_storeu_epi16(out, _mm256_sub_epi16(_mm256_set_epi16(val1_16, val1_15, val1_14, val1_13, val1_12, val1_11, val1_10, val1_9, val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm256_set_epi16(val2_16, val2_15, val2_14, val2_13, val2_12, val2_11, val2_10, val2_9, val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			sub_8(out,
				val1_1,
				val1_2,
				val1_3,
				val1_4,
				val1_5,
				val1_6,
				val1_7,
				val1_8,
				val2_1,
				val2_2,
				val2_3,
				val2_4,
				val2_5,
				val2_6,
				val2_7,
				val2_8);
			sub_8(&out[8],
				val1_9,
				val1_10,
				val1_11,
				val1_12,
				val1_13,
				val1_14,
				val1_15,
				val1_16,
				val2_9,
				val2_10,
				val2_11,
				val2_12,
				val2_13,
				val2_14,
				val2_15,
				val2_16);
		}
	}

	TEvoid TILO_VECTORCALL sub_32(
		TEshort* out,
		TEshort val1_1,
		TEshort val1_2,
		TEshort val1_3,
		TEshort val1_4,
		TEshort val1_5,
		TEshort val1_6,
		TEshort val1_7,
		TEshort val1_8,
		TEshort val1_9,
		TEshort val1_10,
		TEshort val1_11,
		TEshort val1_12,
		TEshort val1_13,
		TEshort val1_14,
		TEshort val1_15,
		TEshort val1_16,
		TEshort val1_17,
		TEshort val1_18,
		TEshort val1_19,
		TEshort val1_20,
		TEshort val1_21,
		TEshort val1_22,
		TEshort val1_23,
		TEshort val1_24,
		TEshort val1_25,
		TEshort val1_26,
		TEshort val1_27,
		TEshort val1_28,
		TEshort val1_29,
		TEshort val1_30,
		TEshort val1_31,
		TEshort val1_32,
		TEshort val2_1,
		TEshort val2_2,
		TEshort val2_3,
		TEshort val2_4,
		TEshort val2_5,
		TEshort val2_6,
		TEshort val2_7,
		TEshort val2_8,
		TEshort val2_9,
		TEshort val2_10,
		TEshort val2_11,
		TEshort val2_12,
		TEshort val2_13,
		TEshort val2_14,
		TEshort val2_15,
		TEshort val2_16,
		TEshort val2_17,
		TEshort val2_18,
		TEshort val2_19,
		TEshort val2_20,
		TEshort val2_21,
		TEshort val2_22,
		TEshort val2_23,
		TEshort val2_24,
		TEshort val2_25,
		TEshort val2_26,
		TEshort val2_27,
		TEshort val2_28,
		TEshort val2_29,
		TEshort val2_30,
		TEshort val2_31,
		TEshort val2_32) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm512_storeu_epi16(out, _mm512_sub_epi16(_mm512_set_epi16(val1_32, val1_31, val1_30, val1_29, val1_28, val1_27, val1_26, val1_25, val1_24, val1_23, val1_22, val1_21, val1_20, val1_19, val1_18, val1_17, val1_16, val1_15, val1_14, val1_13, val1_12, val1_11, val1_10, val1_9, val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm512_set_epi16(val2_32, val2_31, val2_30, val2_29, val2_28, val2_27, val2_26, val2_25, val2_24, val2_23, val2_22, val2_21, val2_20, val2_19, val2_18, val2_17, val2_16, val2_15, val2_14, val2_13, val2_12, val2_11, val2_10, val2_9, val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			sub_16(out,
				val1_1,
				val1_2,
				val1_3,
				val1_4,
				val1_5,
				val1_6,
				val1_7,
				val1_8,
				val1_9,
				val1_10,
				val1_11,
				val1_12,
				val1_13,
				val1_14,
				val1_15,
				val1_16,
				val2_1,
				val2_2,
				val2_3,
				val2_4,
				val2_5,
				val2_6,
				val2_7,
				val2_8,
				val2_9,
				val2_10,
				val2_11,
				val2_12,
				val2_13,
				val2_14,
				val2_15,
				val2_16);
			sub_16(&out[16],
				val1_17,
				val1_18,
				val1_19,
				val1_20,
				val1_21,
				val1_22,
				val1_23,
				val1_24,
				val1_25,
				val1_26,
				val1_27,
				val1_28,
				val1_29,
				val1_30,
				val1_31,
				val1_31,
				val2_17,
				val2_18,
				val2_19,
				val2_20,
				val2_21,
				val2_22,
				val2_23,
				val2_24,
				val2_25,
				val2_26,
				val2_27,
				val2_28,
				val2_29,
				val2_30,
				val2_31,
				val2_31);
		}
	}

	TEvoid TILO_VECTORCALL sub_4(
		TEint* out,
		TEint val1_1,
		TEint val1_2,
		TEint val1_3,
		TEint val1_4,
		TEint val2_1,
		TEint val2_2,
		TEint val2_3,
		TEint val2_4) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSE2 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_storeu_epi32(out, _mm_sub_epi32(_mm_set_epi32(val1_4, val1_3, val1_2, val1_1),
				_mm_set_epi32(val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = val1_1 + val2_1;
			out[1] = val1_2 + val2_2;
			out[2] = val1_3 + val2_3;
			out[3] = val1_4 + val2_4;
		}
	}

	TEvoid TILO_VECTORCALL sub_8(
		TEint* out,
		TEint val1_1,
		TEint val1_2,
		TEint val1_3,
		TEint val1_4,
		TEint val1_5,
		TEint val1_6,
		TEint val1_7,
		TEint val1_8,
		TEint val2_1,
		TEint val2_2,
		TEint val2_3,
		TEint val2_4,
		TEint val2_5,
		TEint val2_6,
		TEint val2_7,
		TEint val2_8) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX2 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm256_storeu_epi32(out, _mm256_sub_epi32(_mm256_set_epi32(val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm256_set_epi32(val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			sub_4(out,
				val1_1,
				val1_2,
				val1_3,
				val1_4,
				val2_1,
				val2_2,
				val2_3,
				val2_4);
			sub_4(&out[4],
				val1_5,
				val1_6,
				val1_7,
				val1_8,
				val2_5,
				val2_6,
				val2_7,
				val2_8);
		}
	}

	TEvoid TILO_VECTORCALL sub_16(
		TEint* out,
		TEint val1_1,
		TEint val1_2,
		TEint val1_3,
		TEint val1_4,
		TEint val1_5,
		TEint val1_6,
		TEint val1_7,
		TEint val1_8,
		TEint val1_9,
		TEint val1_10,
		TEint val1_11,
		TEint val1_12,
		TEint val1_13,
		TEint val1_14,
		TEint val1_15,
		TEint val1_16,
		TEint val2_1,
		TEint val2_2,
		TEint val2_3,
		TEint val2_4,
		TEint val2_5,
		TEint val2_6,
		TEint val2_7,
		TEint val2_8,
		TEint val2_9,
		TEint val2_10,
		TEint val2_11,
		TEint val2_12,
		TEint val2_13,
		TEint val2_14,
		TEint val2_15,
		TEint val2_16) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm512_storeu_epi32(out, _mm512_sub_epi32(_mm512_set_epi32(val1_16, val1_15, val1_14, val1_13, val1_12, val1_11, val1_10, val1_9, val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm512_set_epi32(val2_16, val2_15, val2_14, val2_13, val2_12, val2_11, val2_10, val2_9, val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			sub_8(out,
				val1_1,
				val1_2,
				val1_3,
				val1_4,
				val1_5,
				val1_6,
				val1_7,
				val1_8,
				val2_1,
				val2_2,
				val2_3,
				val2_4,
				val2_5,
				val2_6,
				val2_7,
				val2_8);
			sub_8(&out[8],
				val1_9,
				val1_10,
				val1_11,
				val1_12,
				val1_13,
				val1_14,
				val1_15,
				val1_16,
				val2_9,
				val2_10,
				val2_11,
				val2_12,
				val2_13,
				val2_14,
				val2_15,
				val2_16);
		}
	}

	TEvoid TILO_VECTORCALL sub_2(
		TElong* out,
		TElong val1_1,
		TElong val1_2,
		TElong val2_1,
		TElong val2_2) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSE2 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_storeu_epi64(out, _mm_sub_epi64(_mm_set_epi64x(val1_2, val1_1),
				_mm_set_epi64x(val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = val1_1 + val2_1;
			out[1] = val1_2 + val2_2;
		}
	}

	TEvoid TILO_VECTORCALL sub_4(
		TElong* out,
		TElong val1_1,
		TElong val1_2,
		TElong val1_3,
		TElong val1_4,
		TElong val2_1,
		TElong val2_2,
		TElong val2_3,
		TElong val2_4) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX && cpuInfo->flags.AVX2 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm256_storeu_epi64(out, _mm256_sub_epi64(_mm256_set_epi64x(val1_4, val1_3, val1_2, val1_1),
				_mm256_set_epi64x(val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			sub_2(out,
				val1_1,
				val1_2,
				val2_1,
				val2_2);
			sub_2(&out[2],
				val1_3,
				val1_4,
				val2_3,
				val2_4);
		}
	}

	TEvoid TILO_VECTORCALL sub_8(
		TElong* out,
		TElong val1_1,
		TElong val1_2,
		TElong val1_3,
		TElong val1_4,
		TElong val1_5,
		TElong val1_6,
		TElong val1_7,
		TElong val1_8,
		TElong val2_1,
		TElong val2_2,
		TElong val2_3,
		TElong val2_4,
		TElong val2_5,
		TElong val2_6,
		TElong val2_7,
		TElong val2_8) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX512F && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm512_storeu_epi64(out, _mm512_sub_epi64(_mm512_set_epi64(val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm512_set_epi64(val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			sub_4(out,
				val1_1,
				val1_2,
				val1_3,
				val1_4,
				val2_1,
				val2_2,
				val2_3,
				val2_4);
			sub_4(&out[4],
				val1_5,
				val1_6,
				val1_7,
				val1_8,
				val2_5,
				val2_6,
				val2_7,
				val2_8);
		}
	}

	TEvoid TILO_VECTORCALL mul_4(
		TEint* out,
		TEint val1_1,
		TEint val1_2,
		TEint val1_3,
		TEint val1_4,
		TEint val2_1,
		TEint val2_2,
		TEint val2_3,
		TEint val2_4) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSE2 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_storeu_epi32(out, _mm_mul_epi32(_mm_set_epi32(val1_4, val1_3, val1_2, val1_1),
				_mm_set_epi32(val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = val1_1 + val2_1;
			out[1] = val1_2 + val2_2;
			out[2] = val1_3 + val2_3;
			out[3] = val1_4 + val2_4;
		}
	}

	TEvoid TILO_VECTORCALL mul_8(
		TEint* out,
		TEint val1_1,
		TEint val1_2,
		TEint val1_3,
		TEint val1_4,
		TEint val1_5,
		TEint val1_6,
		TEint val1_7,
		TEint val1_8,
		TEint val2_1,
		TEint val2_2,
		TEint val2_3,
		TEint val2_4,
		TEint val2_5,
		TEint val2_6,
		TEint val2_7,
		TEint val2_8) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX2 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm256_storeu_epi32(out, _mm256_mul_epi32(_mm256_set_epi32(val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm256_set_epi32(val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			mul_4(out,
				val1_1,
				val1_2,
				val1_3,
				val1_4,
				val2_1,
				val2_2,
				val2_3,
				val2_4);
			mul_4(&out[4],
				val1_5,
				val1_6,
				val1_7,
				val1_8,
				val2_5,
				val2_6,
				val2_7,
				val2_8);
		}
	}

	TEvoid TILO_VECTORCALL mul_16(
		TEint* out,
		TEint val1_1,
		TEint val1_2,
		TEint val1_3,
		TEint val1_4,
		TEint val1_5,
		TEint val1_6,
		TEint val1_7,
		TEint val1_8,
		TEint val1_9,
		TEint val1_10,
		TEint val1_11,
		TEint val1_12,
		TEint val1_13,
		TEint val1_14,
		TEint val1_15,
		TEint val1_16,
		TEint val2_1,
		TEint val2_2,
		TEint val2_3,
		TEint val2_4,
		TEint val2_5,
		TEint val2_6,
		TEint val2_7,
		TEint val2_8,
		TEint val2_9,
		TEint val2_10,
		TEint val2_11,
		TEint val2_12,
		TEint val2_13,
		TEint val2_14,
		TEint val2_15,
		TEint val2_16) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm512_storeu_epi32(out, _mm512_mul_epi32(_mm512_set_epi32(val1_16, val1_15, val1_14, val1_13, val1_12, val1_11, val1_10, val1_9, val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm512_set_epi32(val2_16, val2_15, val2_14, val2_13, val2_12, val2_11, val2_10, val2_9, val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			mul_8(out,
				val1_1,
				val1_2,
				val1_3,
				val1_4,
				val1_5,
				val1_6,
				val1_7,
				val1_8,
				val2_1,
				val2_2,
				val2_3,
				val2_4,
				val2_5,
				val2_6,
				val2_7,
				val2_8);
			mul_8(&out[8],
				val1_9,
				val1_10,
				val1_11,
				val1_12,
				val1_13,
				val1_14,
				val1_15,
				val1_16,
				val2_9,
				val2_10,
				val2_11,
				val2_12,
				val2_13,
				val2_14,
				val2_15,
				val2_16);
		}
	}

	TEvoid TILO_VECTORCALL div_16(
		TEbyte* out,
		TEbyte val1_1,
		TEbyte val1_2,
		TEbyte val1_3,
		TEbyte val1_4,
		TEbyte val1_5,
		TEbyte val1_6,
		TEbyte val1_7,
		TEbyte val1_8,
		TEbyte val1_9,
		TEbyte val1_10,
		TEbyte val1_11,
		TEbyte val1_12,
		TEbyte val1_13,
		TEbyte val1_14,
		TEbyte val1_15,
		TEbyte val1_16,
		TEbyte val2_1,
		TEbyte val2_2,
		TEbyte val2_3,
		TEbyte val2_4,
		TEbyte val2_5,
		TEbyte val2_6,
		TEbyte val2_7,
		TEbyte val2_8,
		TEbyte val2_9,
		TEbyte val2_10,
		TEbyte val2_11,
		TEbyte val2_12,
		TEbyte val2_13,
		TEbyte val2_14,
		TEbyte val2_15,
		TEbyte val2_16) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSE2 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_storeu_epi8(out, _mm_div_epi8(_mm_set_epi8(val1_16, val1_15, val1_14, val1_13, val1_12, val1_11, val1_10, val1_9, val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm_set_epi8(val2_16, val2_15, val2_14, val2_13, val2_12, val2_11, val2_10, val2_9, val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = val1_1 + val2_1;
			out[1] = val1_2 + val2_2;
			out[2] = val1_3 + val2_3;
			out[3] = val1_4 + val2_4;
			out[4] = val1_5 + val2_5;
			out[5] = val1_6 + val2_6;
			out[6] = val1_7 + val2_7;
			out[7] = val1_8 + val2_8;
			out[8] = val1_9 + val2_9;
			out[9] = val1_10 + val2_10;
			out[10] = val1_11 + val2_11;
			out[11] = val1_12 + val2_12;
			out[12] = val1_13 + val2_13;
			out[13] = val1_14 + val2_14;
			out[14] = val1_15 + val2_15;
			out[15] = val1_16 + val2_16;
		}
	}

	TEvoid TILO_VECTORCALL div_32(
		TEbyte* out,
		TEbyte val1_1,
		TEbyte val1_2,
		TEbyte val1_3,
		TEbyte val1_4,
		TEbyte val1_5,
		TEbyte val1_6,
		TEbyte val1_7,
		TEbyte val1_8,
		TEbyte val1_9,
		TEbyte val1_10,
		TEbyte val1_11,
		TEbyte val1_12,
		TEbyte val1_13,
		TEbyte val1_14,
		TEbyte val1_15,
		TEbyte val1_16,
		TEbyte val1_17,
		TEbyte val1_18,
		TEbyte val1_19,
		TEbyte val1_20,
		TEbyte val1_21,
		TEbyte val1_22,
		TEbyte val1_23,
		TEbyte val1_24,
		TEbyte val1_25,
		TEbyte val1_26,
		TEbyte val1_27,
		TEbyte val1_28,
		TEbyte val1_29,
		TEbyte val1_30,
		TEbyte val1_31,
		TEbyte val1_32,
		TEbyte val2_1,
		TEbyte val2_2,
		TEbyte val2_3,
		TEbyte val2_4,
		TEbyte val2_5,
		TEbyte val2_6,
		TEbyte val2_7,
		TEbyte val2_8,
		TEbyte val2_9,
		TEbyte val2_10,
		TEbyte val2_11,
		TEbyte val2_12,
		TEbyte val2_13,
		TEbyte val2_14,
		TEbyte val2_15,
		TEbyte val2_16,
		TEbyte val2_17,
		TEbyte val2_18,
		TEbyte val2_19,
		TEbyte val2_20,
		TEbyte val2_21,
		TEbyte val2_22,
		TEbyte val2_23,
		TEbyte val2_24,
		TEbyte val2_25,
		TEbyte val2_26,
		TEbyte val2_27,
		TEbyte val2_28,
		TEbyte val2_29,
		TEbyte val2_30,
		TEbyte val2_31,
		TEbyte val2_32) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX2 && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm256_storeu_epi8(out, _mm256_div_epi8(_mm256_set_epi8(val1_32, val1_31, val1_30, val1_29, val1_28, val1_27, val1_26, val1_25, val1_24, val1_23, val1_22, val1_21, val1_20, val1_19, val1_18, val1_17, val1_16, val1_15, val1_14, val1_13, val1_12, val1_11, val1_10, val1_9, val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm256_set_epi8(val2_32, val2_31, val2_30, val2_29, val2_28, val2_27, val2_26, val2_25, val2_24, val2_23, val2_22, val2_21, val2_20, val2_19, val2_18, val2_17, val2_16, val2_15, val2_14, val2_13, val2_12, val2_11, val2_10, val2_9, val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			div_16(out,
				val1_1,
				val1_2,
				val1_3,
				val1_4,
				val1_5,
				val1_6,
				val1_7,
				val1_8,
				val1_9,
				val1_10,
				val1_11,
				val1_12,
				val1_13,
				val1_14,
				val1_15,
				val1_16,
				val2_1,
				val2_2,
				val2_3,
				val2_4,
				val2_5,
				val2_6,
				val2_7,
				val2_8,
				val2_9,
				val2_10,
				val2_11,
				val2_12,
				val2_13,
				val2_14,
				val2_15,
				val2_16);
			div_16(&out[16],
				val1_17,
				val1_18,
				val1_19,
				val1_20,
				val1_21,
				val1_22,
				val1_23,
				val1_24,
				val1_25,
				val1_26,
				val1_27,
				val1_28,
				val1_29,
				val1_30,
				val1_31,
				val1_31,
				val2_17,
				val2_18,
				val2_19,
				val2_20,
				val2_21,
				val2_22,
				val2_23,
				val2_24,
				val2_25,
				val2_26,
				val2_27,
				val2_28,
				val2_29,
				val2_30,
				val2_31,
				val2_31);
		}
	}

	TEvoid TILO_VECTORCALL div_64(
		TEbyte* out,
		TEbyte val1_1,
		TEbyte val1_2,
		TEbyte val1_3,
		TEbyte val1_4,
		TEbyte val1_5,
		TEbyte val1_6,
		TEbyte val1_7,
		TEbyte val1_8,
		TEbyte val1_9,
		TEbyte val1_10,
		TEbyte val1_11,
		TEbyte val1_12,
		TEbyte val1_13,
		TEbyte val1_14,
		TEbyte val1_15,
		TEbyte val1_16,
		TEbyte val1_17,
		TEbyte val1_18,
		TEbyte val1_19,
		TEbyte val1_20,
		TEbyte val1_21,
		TEbyte val1_22,
		TEbyte val1_23,
		TEbyte val1_24,
		TEbyte val1_25,
		TEbyte val1_26,
		TEbyte val1_27,
		TEbyte val1_28,
		TEbyte val1_29,
		TEbyte val1_30,
		TEbyte val1_31,
		TEbyte val1_32,
		TEbyte val1_33,
		TEbyte val1_34,
		TEbyte val1_35,
		TEbyte val1_36,
		TEbyte val1_37,
		TEbyte val1_38,
		TEbyte val1_39,
		TEbyte val1_40,
		TEbyte val1_41,
		TEbyte val1_42,
		TEbyte val1_43,
		TEbyte val1_44,
		TEbyte val1_45,
		TEbyte val1_46,
		TEbyte val1_47,
		TEbyte val1_48,
		TEbyte val1_49,
		TEbyte val1_50,
		TEbyte val1_51,
		TEbyte val1_52,
		TEbyte val1_53,
		TEbyte val1_54,
		TEbyte val1_55,
		TEbyte val1_56,
		TEbyte val1_57,
		TEbyte val1_58,
		TEbyte val1_59,
		TEbyte val1_60,
		TEbyte val1_61,
		TEbyte val1_62,
		TEbyte val1_63,
		TEbyte val1_64,
		TEbyte val2_1,
		TEbyte val2_2,
		TEbyte val2_3,
		TEbyte val2_4,
		TEbyte val2_5,
		TEbyte val2_6,
		TEbyte val2_7,
		TEbyte val2_8,
		TEbyte val2_9,
		TEbyte val2_10,
		TEbyte val2_11,
		TEbyte val2_12,
		TEbyte val2_13,
		TEbyte val2_14,
		TEbyte val2_15,
		TEbyte val2_16,
		TEbyte val2_17,
		TEbyte val2_18,
		TEbyte val2_19,
		TEbyte val2_20,
		TEbyte val2_21,
		TEbyte val2_22,
		TEbyte val2_23,
		TEbyte val2_24,
		TEbyte val2_25,
		TEbyte val2_26,
		TEbyte val2_27,
		TEbyte val2_28,
		TEbyte val2_29,
		TEbyte val2_30,
		TEbyte val2_31,
		TEbyte val2_32,
		TEbyte val2_33,
		TEbyte val2_34,
		TEbyte val2_35,
		TEbyte val2_36,
		TEbyte val2_37,
		TEbyte val2_38,
		TEbyte val2_39,
		TEbyte val2_40,
		TEbyte val2_41,
		TEbyte val2_42,
		TEbyte val2_43,
		TEbyte val2_44,
		TEbyte val2_45,
		TEbyte val2_46,
		TEbyte val2_47,
		TEbyte val2_48,
		TEbyte val2_49,
		TEbyte val2_50,
		TEbyte val2_51,
		TEbyte val2_52,
		TEbyte val2_53,
		TEbyte val2_54,
		TEbyte val2_55,
		TEbyte val2_56,
		TEbyte val2_57,
		TEbyte val2_58,
		TEbyte val2_59,
		TEbyte val2_60,
		TEbyte val2_61,
		TEbyte val2_62,
		TEbyte val2_63,
		TEbyte val2_64) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm512_storeu_epi8(out, _mm512_div_epi8(_mm512_set_epi8(val1_64, val1_63, val1_62, val1_61, val1_60, val1_59, val1_58, val1_57, val1_56, val1_55, val1_54, val1_53, val1_52, val1_51, val1_50, val1_49, val1_48, val1_47, val1_46, val1_45, val1_44, val1_43, val1_42, val1_41, val1_40, val1_39, val1_38, val1_37, val1_36, val1_35, val1_34, val1_33, val1_32, val1_31, val1_30, val1_29, val1_28, val1_27, val1_26, val1_25, val1_24, val1_23, val1_22, val1_21, val1_20, val1_19, val1_18, val1_17, val1_16, val1_15, val1_14, val1_13, val1_12, val1_11, val1_10, val1_9, val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm512_set_epi8(val2_64, val2_63, val2_62, val2_61, val2_60, val2_59, val2_58, val2_57, val2_56, val2_55, val2_54, val2_53, val2_52, val2_51, val2_50, val2_49, val2_48, val2_47, val2_46, val2_45, val2_44, val2_43, val2_42, val2_41, val2_40, val2_39, val2_38, val2_37, val2_36, val2_35, val2_34, val2_33, val2_32, val2_31, val2_30, val2_29, val2_28, val2_27, val2_26, val2_25, val2_24, val2_23, val2_22, val2_21, val2_20, val2_19, val2_18, val2_17, val2_16, val2_15, val2_14, val2_13, val2_12, val2_11, val2_10, val2_9, val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			div_32(out,
				val1_1,
				val1_2,
				val1_3,
				val1_4,
				val1_5,
				val1_6,
				val1_7,
				val1_8,
				val1_9,
				val1_10,
				val1_11,
				val1_12,
				val1_13,
				val1_14,
				val1_15,
				val1_16,
				val1_17,
				val1_18,
				val1_19,
				val1_20,
				val1_21,
				val1_22,
				val1_23,
				val1_24,
				val1_25,
				val1_26,
				val1_27,
				val1_28,
				val1_29,
				val1_30,
				val1_31,
				val1_32,
				val2_1,
				val2_2,
				val2_3,
				val2_4,
				val2_5,
				val2_6,
				val2_7,
				val2_8,
				val2_9,
				val2_10,
				val2_11,
				val2_12,
				val2_13,
				val2_14,
				val2_15,
				val2_16,
				val2_17,
				val2_18,
				val2_19,
				val2_20,
				val2_21,
				val2_22,
				val2_23,
				val2_24,
				val2_25,
				val2_26,
				val2_27,
				val2_28,
				val2_29,
				val2_30,
				val2_31,
				val2_32);
			div_32(&out[32],
				val1_33,
				val1_34,
				val1_35,
				val1_36,
				val1_37,
				val1_38,
				val1_39,
				val1_40,
				val1_41,
				val1_42,
				val1_43,
				val1_44,
				val1_45,
				val1_46,
				val1_47,
				val1_48,
				val1_49,
				val1_50,
				val1_51,
				val1_52,
				val1_53,
				val1_54,
				val1_55,
				val1_56,
				val1_57,
				val1_58,
				val1_59,
				val1_60,
				val1_61,
				val1_62,
				val1_63,
				val1_64,
				val2_33,
				val2_34,
				val2_35,
				val2_36,
				val2_37,
				val2_38,
				val2_39,
				val2_40,
				val2_41,
				val2_42,
				val2_43,
				val2_44,
				val2_45,
				val2_46,
				val2_47,
				val2_48,
				val2_49,
				val2_50,
				val2_51,
				val2_52,
				val2_53,
				val2_54,
				val2_55,
				val2_56,
				val2_57,
				val2_58,
				val2_59,
				val2_60,
				val2_61,
				val2_62,
				val2_63,
				val2_64
			);
		}
	}

	TEvoid TILO_VECTORCALL div_8(
		TEshort* out,
		TEshort val1_1,
		TEshort val1_2,
		TEshort val1_3,
		TEshort val1_4,
		TEshort val1_5,
		TEshort val1_6,
		TEshort val1_7,
		TEshort val1_8,
		TEshort val2_1,
		TEshort val2_2,
		TEshort val2_3,
		TEshort val2_4,
		TEshort val2_5,
		TEshort val2_6,
		TEshort val2_7,
		TEshort val2_8) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSE2 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_storeu_epi16(out, _mm_div_epi16(_mm_set_epi16(val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm_set_epi16(val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = val1_1 + val2_1;
			out[1] = val1_2 + val2_2;
			out[2] = val1_3 + val2_3;
			out[3] = val1_4 + val2_4;
			out[4] = val1_5 + val2_5;
			out[5] = val1_6 + val2_6;
			out[6] = val1_7 + val2_7;
			out[7] = val1_8 + val2_8;
		}
	}

	TEvoid TILO_VECTORCALL div_16(
		TEshort* out,
		TEshort val1_1,
		TEshort val1_2,
		TEshort val1_3,
		TEshort val1_4,
		TEshort val1_5,
		TEshort val1_6,
		TEshort val1_7,
		TEshort val1_8,
		TEshort val1_9,
		TEshort val1_10,
		TEshort val1_11,
		TEshort val1_12,
		TEshort val1_13,
		TEshort val1_14,
		TEshort val1_15,
		TEshort val1_16,
		TEshort val2_1,
		TEshort val2_2,
		TEshort val2_3,
		TEshort val2_4,
		TEshort val2_5,
		TEshort val2_6,
		TEshort val2_7,
		TEshort val2_8,
		TEshort val2_9,
		TEshort val2_10,
		TEshort val2_11,
		TEshort val2_12,
		TEshort val2_13,
		TEshort val2_14,
		TEshort val2_15,
		TEshort val2_16) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX2 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm256_storeu_epi16(out, _mm256_div_epi16(_mm256_set_epi16(val1_16, val1_15, val1_14, val1_13, val1_12, val1_11, val1_10, val1_9, val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm256_set_epi16(val2_16, val2_15, val2_14, val2_13, val2_12, val2_11, val2_10, val2_9, val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			div_8(out,
				val1_1,
				val1_2,
				val1_3,
				val1_4,
				val1_5,
				val1_6,
				val1_7,
				val1_8,
				val2_1,
				val2_2,
				val2_3,
				val2_4,
				val2_5,
				val2_6,
				val2_7,
				val2_8);
			div_8(&out[8],
				val1_9,
				val1_10,
				val1_11,
				val1_12,
				val1_13,
				val1_14,
				val1_15,
				val1_16,
				val2_9,
				val2_10,
				val2_11,
				val2_12,
				val2_13,
				val2_14,
				val2_15,
				val2_16);
		}
	}

	TEvoid TILO_VECTORCALL div_32(
		TEshort* out,
		TEshort val1_1,
		TEshort val1_2,
		TEshort val1_3,
		TEshort val1_4,
		TEshort val1_5,
		TEshort val1_6,
		TEshort val1_7,
		TEshort val1_8,
		TEshort val1_9,
		TEshort val1_10,
		TEshort val1_11,
		TEshort val1_12,
		TEshort val1_13,
		TEshort val1_14,
		TEshort val1_15,
		TEshort val1_16,
		TEshort val1_17,
		TEshort val1_18,
		TEshort val1_19,
		TEshort val1_20,
		TEshort val1_21,
		TEshort val1_22,
		TEshort val1_23,
		TEshort val1_24,
		TEshort val1_25,
		TEshort val1_26,
		TEshort val1_27,
		TEshort val1_28,
		TEshort val1_29,
		TEshort val1_30,
		TEshort val1_31,
		TEshort val1_32,
		TEshort val2_1,
		TEshort val2_2,
		TEshort val2_3,
		TEshort val2_4,
		TEshort val2_5,
		TEshort val2_6,
		TEshort val2_7,
		TEshort val2_8,
		TEshort val2_9,
		TEshort val2_10,
		TEshort val2_11,
		TEshort val2_12,
		TEshort val2_13,
		TEshort val2_14,
		TEshort val2_15,
		TEshort val2_16,
		TEshort val2_17,
		TEshort val2_18,
		TEshort val2_19,
		TEshort val2_20,
		TEshort val2_21,
		TEshort val2_22,
		TEshort val2_23,
		TEshort val2_24,
		TEshort val2_25,
		TEshort val2_26,
		TEshort val2_27,
		TEshort val2_28,
		TEshort val2_29,
		TEshort val2_30,
		TEshort val2_31,
		TEshort val2_32) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm512_storeu_epi16(out, _mm512_div_epi16(_mm512_set_epi16(val1_32, val1_31, val1_30, val1_29, val1_28, val1_27, val1_26, val1_25, val1_24, val1_23, val1_22, val1_21, val1_20, val1_19, val1_18, val1_17, val1_16, val1_15, val1_14, val1_13, val1_12, val1_11, val1_10, val1_9, val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm512_set_epi16(val2_32, val2_31, val2_30, val2_29, val2_28, val2_27, val2_26, val2_25, val2_24, val2_23, val2_22, val2_21, val2_20, val2_19, val2_18, val2_17, val2_16, val2_15, val2_14, val2_13, val2_12, val2_11, val2_10, val2_9, val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			div_16(out,
				val1_1,
				val1_2,
				val1_3,
				val1_4,
				val1_5,
				val1_6,
				val1_7,
				val1_8,
				val1_9,
				val1_10,
				val1_11,
				val1_12,
				val1_13,
				val1_14,
				val1_15,
				val1_16,
				val2_1,
				val2_2,
				val2_3,
				val2_4,
				val2_5,
				val2_6,
				val2_7,
				val2_8,
				val2_9,
				val2_10,
				val2_11,
				val2_12,
				val2_13,
				val2_14,
				val2_15,
				val2_16);
			div_16(&out[16],
				val1_17,
				val1_18,
				val1_19,
				val1_20,
				val1_21,
				val1_22,
				val1_23,
				val1_24,
				val1_25,
				val1_26,
				val1_27,
				val1_28,
				val1_29,
				val1_30,
				val1_31,
				val1_31,
				val2_17,
				val2_18,
				val2_19,
				val2_20,
				val2_21,
				val2_22,
				val2_23,
				val2_24,
				val2_25,
				val2_26,
				val2_27,
				val2_28,
				val2_29,
				val2_30,
				val2_31,
				val2_31);
		}
	}

	TEvoid TILO_VECTORCALL div_4(
		TEint* out,
		TEint val1_1,
		TEint val1_2,
		TEint val1_3,
		TEint val1_4,
		TEint val2_1,
		TEint val2_2,
		TEint val2_3,
		TEint val2_4) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSE2 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_storeu_epi32(out, _mm_div_epi32(_mm_set_epi32(val1_4, val1_3, val1_2, val1_1),
				_mm_set_epi32(val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = val1_1 + val2_1;
			out[1] = val1_2 + val2_2;
			out[2] = val1_3 + val2_3;
			out[3] = val1_4 + val2_4;
		}
	}

	TEvoid TILO_VECTORCALL div_8(
		TEint* out,
		TEint val1_1,
		TEint val1_2,
		TEint val1_3,
		TEint val1_4,
		TEint val1_5,
		TEint val1_6,
		TEint val1_7,
		TEint val1_8,
		TEint val2_1,
		TEint val2_2,
		TEint val2_3,
		TEint val2_4,
		TEint val2_5,
		TEint val2_6,
		TEint val2_7,
		TEint val2_8) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX2 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm256_storeu_epi32(out, _mm256_div_epi32(_mm256_set_epi32(val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm256_set_epi32(val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			div_4(out,
				val1_1,
				val1_2,
				val1_3,
				val1_4,
				val2_1,
				val2_2,
				val2_3,
				val2_4);
			div_4(&out[4],
				val1_5,
				val1_6,
				val1_7,
				val1_8,
				val2_5,
				val2_6,
				val2_7,
				val2_8);
		}
	}

	TEvoid TILO_VECTORCALL div_16(
		TEint* out,
		TEint val1_1,
		TEint val1_2,
		TEint val1_3,
		TEint val1_4,
		TEint val1_5,
		TEint val1_6,
		TEint val1_7,
		TEint val1_8,
		TEint val1_9,
		TEint val1_10,
		TEint val1_11,
		TEint val1_12,
		TEint val1_13,
		TEint val1_14,
		TEint val1_15,
		TEint val1_16,
		TEint val2_1,
		TEint val2_2,
		TEint val2_3,
		TEint val2_4,
		TEint val2_5,
		TEint val2_6,
		TEint val2_7,
		TEint val2_8,
		TEint val2_9,
		TEint val2_10,
		TEint val2_11,
		TEint val2_12,
		TEint val2_13,
		TEint val2_14,
		TEint val2_15,
		TEint val2_16) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm512_storeu_epi32(out, _mm512_div_epi32(_mm512_set_epi32(val1_16, val1_15, val1_14, val1_13, val1_12, val1_11, val1_10, val1_9, val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm512_set_epi32(val2_16, val2_15, val2_14, val2_13, val2_12, val2_11, val2_10, val2_9, val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			div_8(out,
				val1_1,
				val1_2,
				val1_3,
				val1_4,
				val1_5,
				val1_6,
				val1_7,
				val1_8,
				val2_1,
				val2_2,
				val2_3,
				val2_4,
				val2_5,
				val2_6,
				val2_7,
				val2_8);
			div_8(&out[8],
				val1_9,
				val1_10,
				val1_11,
				val1_12,
				val1_13,
				val1_14,
				val1_15,
				val1_16,
				val2_9,
				val2_10,
				val2_11,
				val2_12,
				val2_13,
				val2_14,
				val2_15,
				val2_16);
		}
	}

	TEvoid TILO_VECTORCALL div_2(
		TElong* out,
		TElong val1_1,
		TElong val1_2,
		TElong val2_1,
		TElong val2_2) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSE2 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_storeu_epi64(out, _mm_div_epi64(_mm_set_epi64x(val1_2, val1_1),
				_mm_set_epi64x(val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = val1_1 + val2_1;
			out[1] = val1_2 + val2_2;
		}
	}

	TEvoid TILO_VECTORCALL div_4(
		TElong* out,
		TElong val1_1,
		TElong val1_2,
		TElong val1_3,
		TElong val1_4,
		TElong val2_1,
		TElong val2_2,
		TElong val2_3,
		TElong val2_4) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX && cpuInfo->flags.AVX2 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm256_storeu_epi64(out, _mm256_div_epi64(_mm256_set_epi64x(val1_4, val1_3, val1_2, val1_1),
				_mm256_set_epi64x(val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			div_2(out,
				val1_1,
				val1_2,
				val2_1,
				val2_2);
			div_2(&out[2],
				val1_3,
				val1_4,
				val2_3,
				val2_4);
		}
	}

	TEvoid TILO_VECTORCALL div_8(
		TElong* out,
		TElong val1_1,
		TElong val1_2,
		TElong val1_3,
		TElong val1_4,
		TElong val1_5,
		TElong val1_6,
		TElong val1_7,
		TElong val1_8,
		TElong val2_1,
		TElong val2_2,
		TElong val2_3,
		TElong val2_4,
		TElong val2_5,
		TElong val2_6,
		TElong val2_7,
		TElong val2_8) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX512F && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm512_storeu_epi64(out, _mm512_div_epi64(_mm512_set_epi64(val1_8, val1_7, val1_6, val1_5, val1_4, val1_3, val1_2, val1_1),
				_mm512_set_epi64(val2_8, val2_7, val2_6, val2_5, val2_4, val2_3, val2_2, val2_1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			div_4(out,
				val1_1,
				val1_2,
				val1_3,
				val1_4,
				val2_1,
				val2_2,
				val2_3,
				val2_4);
			div_4(&out[4],
				val1_5,
				val1_6,
				val1_7,
				val1_8,
				val2_5,
				val2_6,
				val2_7,
				val2_8);
		}
	}

	[[nodiscard]] TILO_INLINE TEfloat TILO_FASTCALL sqrt(
		TEfloat val) {
		return std::sqrt(val);
	}

	TILO_INLINE TEvoid sqrt(
		TEfloat& out,
		TEfloat val) {
		out = sqrt(val);
	}

	TEvoid TILO_VECTORCALL sqrt_2(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_store_ps(out, _mm_sqrt_ps(_mm_set_ps(0, 0, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = sqrt(val1);
			out[1] = sqrt(val2);
		}
	}

	TEvoid TILO_VECTORCALL sqrt_4(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_store_ps(out, _mm_sqrt_ps(_mm_set_ps(val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = sqrt(val1);
			out[1] = sqrt(val2);
			out[2] = sqrt(val3);
			out[3] = sqrt(val4);
		}
	}

	TEvoid TILO_VECTORCALL sqrt_8(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm256_store_ps(out, _mm256_sqrt_ps(_mm256_set_ps(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			sqrt_4(out,
				val1,
				val2,
				val3,
				val4);
			sqrt_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	TEvoid TILO_VECTORCALL sqrt_16(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8,
		TEfloat val9,
		TEfloat val10,
		TEfloat val11,
		TEfloat val12,
		TEfloat val13,
		TEfloat val14,
		TEfloat val15,
		TEfloat val16) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm512_store_ps(out, _mm512_sqrt_ps(_mm512_set_ps(val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			sqrt_8(out,
				val1,
				val2,
				val3,
				val4,
				val5,
				val6,
				val7,
				val8);
			sqrt_8(&out[8],
				val9,
				val10,
				val11,
				val12,
				val13,
				val14,
				val15,
				val16);
		}
	}

	[[nodiscard]] TILO_INLINE TEdouble TILO_FASTCALL sqrt(
		TEdouble val) {
		return std::sqrt(val);
	}

	TILO_INLINE TEvoid sqrt(
		TEdouble& out,
		TEdouble val) {
		out = sqrt(val);
	}

	TEvoid TILO_VECTORCALL sqrt_2(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSE2, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_store_pd(out, _mm_sqrt_pd(_mm_set_pd(val2, val1)));
		TILO_ASSUME(simdEnabledSvmlSupported)
		} else if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabledSvmlSupported, TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SVML_SSE_PROBABILITY)) [[TILO_SVML_ATTR]] {
			_mm_store_pd(out, _mm_svml_sqrt_pd(_mm_set_pd(val2, val1)));
		} else [[TILO_NO_SVML_ATTR]] {
			out[0] = sqrt(val1);
			out[1] = sqrt(val2);
		}
	}

	TEvoid TILO_VECTORCALL sqrt_4(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm256_store_pd(out, _mm256_sqrt_pd(_mm256_set_pd(val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			sqrt_2(out,
				val1,
				val2);
			sqrt_2(&out[2],
				val3,
				val4);
		}
	}

	TEvoid TILO_VECTORCALL sqrt_8(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4,
		TEdouble val5,
		TEdouble val6,
		TEdouble val7,
		TEdouble val8) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm512_store_pd(out, _mm512_sqrt_pd(_mm512_set_pd(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			sqrt_4(out,
				val1,
				val2,
				val3,
				val4);
			sqrt_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	template <TEbool fast = true>
	[[nodiscard]] constexpr TILO_INLINE TEfloat TILO_FASTCALL invsqrt(
		TEfloat val) = delete;

	template <>
	[[nodiscard]] TILO_INLINE TEfloat TILO_FASTCALL invsqrt<false>(
		TEfloat val) {
		return 1 / sqrt(val);
	}

	template <>
	[[nodiscard]] constexpr  TILO_INLINE TEfloat TILO_FASTCALL invsqrt<true>(
		TEfloat val) {
		register const TEfloat y = bit_cast<TEfloat, TEuint>(0x5f3759df - (bit_cast<TEuint, TEfloat>(val) >> 1));
		return y * (1.5f - (val * 0.5f * y * y));
	}

	template <TEbool fast = true>
	constexpr TILO_INLINE TEvoid invsqrt(
		TEfloat& out,
		TEfloat val) {
		out = invsqrt<fast>(val, fast);
	}

	template <TEbool fast = true>
	constexpr TEvoid invsqrt_2(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_store_ps(out, _mm_sin_ps(_mm_set_ps(0, 0, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = invsqrt<fast>(val1);
			out[1] = invsqrt<fast>(val2);
		}
	}

	template <TEbool fast = true>
	constexpr TEvoid invsqrt_4(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_store_ps(out, _mm_invsqrt_ps(_mm_set_ps(val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = invsqrt<fast>(val1);
			out[1] = invsqrt<fast>(val2);
			out[2] = invsqrt<fast>(val3);
			out[3] = invsqrt<fast>(val4);
		}
	}

	template <TEbool fast = true>
	constexpr TEvoid invsqrt_8(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm256_store_ps(out, _mm256_invsqrt_ps(_mm256_set_ps(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			invsqrt_4<fast>(out,
				val1,
				val2,
				val3,
				val4);
			invsqrt_4<fast>(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	template <TEbool fast = true>
	constexpr TEvoid invsqrt_16(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8,
		TEfloat val9,
		TEfloat val10,
		TEfloat val11,
		TEfloat val12,
		TEfloat val13,
		TEfloat val14,
		TEfloat val15,
		TEfloat val16) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm512_store_ps(out, _mm512_invsqrt_ps(_mm512_set_ps(val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			invsqrt_8<fast>(out,
				val1,
				val2,
				val3,
				val4,
				val5,
				val6,
				val7,
				val8);
			invsqrt_8<fast>(&out[8],
				val9,
				val10,
				val11,
				val12,
				val13,
				val14,
				val15,
				val16);
		}
	}

	template <TEbool fast = true>
	[[nodiscard]] constexpr TILO_INLINE TEdouble TILO_FASTCALL invsqrt(
		TEdouble val);

	template <>
	[[nodiscard]] TILO_INLINE TEdouble TILO_FASTCALL invsqrt<false>(
		TEdouble val) {
		return 1 / sqrt(val);
	}

	template <>
	[[nodiscard]] constexpr TILO_INLINE TEdouble TILO_FASTCALL invsqrt<true>(
		TEdouble val) {
		register const TEdouble y = bit_cast<TEdouble>(0x5fe6eb50c7b537a9 - (bit_cast<TEulong>(val) >> 1));
		return y * (1.5f - (val * 0.5f * y * y));
	}

	template <TEbool fast = true>
	TILO_INLINE constexpr TEvoid invsqrt(
		TEdouble& out,
		TEdouble val) {
		out = invsqrt<fast>(val);
	}

	template <TEbool fast = true>
	constexpr TEvoid invsqrt_2(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSE2, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_store_pd(out, _mm_invsqrt_pd(_mm_set_pd(val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = invsqrt<fast>(val1);
			out[1] = invsqrt<fast>(val2);
		}
	}

	template <TEbool fast = true>
	constexpr TEvoid invsqrt_4(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm256_store_pd(out, _mm256_invsqrt_pd(_mm256_set_pd(val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			invsqrt_2<fast>(out,
				val1,
				val2);
			invsqrt_2<fast>(&out[2],
				val3,
				val4);
		}
	}

	template <TEbool fast = true>
	constexpr TEvoid invsqrt_8(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4,
		TEdouble val5,
		TEdouble val6,
		TEdouble val7,
		TEdouble val8) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm512_store_pd(out, _mm512_invsqrt_pd(_mm512_set_pd(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			invsqrt_4<fast>(out,
				val1,
				val2,
				val3,
				val4);
			invsqrt_4<fast>(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	[[nodiscard]] TILO_INLINE TEfloat TILO_FASTCALL cbrt(
		TEfloat val) {
		return std::cbrt(val);
	}

	TILO_INLINE TEvoid cbrt(
		TEfloat& out,
		TEfloat val) {
		out = cbrt(val);
	}

	TEvoid TILO_VECTORCALL cbrt_2(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_store_ps(out, _mm_sin_ps(_mm_set_ps(0, 0, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = cbrt(val1);
			out[1] = cbrt(val2);
		}
	}

	TEvoid TILO_VECTORCALL cbrt_4(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_store_ps(out, _mm_cbrt_ps(_mm_set_ps(val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = cbrt(val1);
			out[1] = cbrt(val2);
			out[2] = cbrt(val3);
			out[3] = cbrt(val4);
		}
	}

	TEvoid TILO_VECTORCALL cbrt_8(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm256_store_ps(out, _mm256_cbrt_ps(_mm256_set_ps(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			cbrt_4(out,
				val1,
				val2,
				val3,
				val4);
			cbrt_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	TEvoid TILO_VECTORCALL cbrt_16(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8,
		TEfloat val9,
		TEfloat val10,
		TEfloat val11,
		TEfloat val12,
		TEfloat val13,
		TEfloat val14,
		TEfloat val15,
		TEfloat val16) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm512_store_ps(out, _mm512_cbrt_ps(_mm512_set_ps(val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			cbrt_8(out,
				val1,
				val2,
				val3,
				val4,
				val5,
				val6,
				val7,
				val8);
			cbrt_8(&out[8],
				val9,
				val10,
				val11,
				val12,
				val13,
				val14,
				val15,
				val16);
		}
	}

	[[nodiscard]] TILO_INLINE TEdouble TILO_FASTCALL cbrt(
		TEdouble val) {
		return std::cbrt(val);
	}

	TILO_INLINE TEvoid cbrt(
		TEdouble& out,
		TEdouble val) {
		out = cbrt(val);
	}

	TEvoid TILO_VECTORCALL cbrt_2(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_store_pd(out, _mm_cbrt_pd(_mm_set_pd(val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = cbrt(val1);
			out[1] = cbrt(val2);
		}
	}

	TEvoid TILO_VECTORCALL cbrt_4(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm256_store_pd(out, _mm256_cbrt_pd(_mm256_set_pd(val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			cbrt_2(out,
				val1,
				val2);
			cbrt_2(&out[2],
				val3,
				val4);
		}
	}

	TEvoid TILO_VECTORCALL cbrt_8(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4,
		TEdouble val5,
		TEdouble val6,
		TEdouble val7,
		TEdouble val8) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm512_store_pd(out, _mm512_cbrt_pd(_mm512_set_pd(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			cbrt_4(out,
				val1,
				val2,
				val3,
				val4);
			cbrt_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	[[nodiscard]] TILO_INLINE TEfloat TILO_FASTCALL invcbrt(
		TEfloat val,
		TEbool fast = true) {
		if (!fast)
			return 1 / cbrt(val);
		const TEfloat y = bit_cast<TEfloat, TEuint>(0x5f3759df - (bit_cast<TEuint, TEfloat>(val) >> 1));
		return y * (1.5f - (val * 0.5f * y * y));
	}

	TILO_INLINE TEvoid invcbrt(
		TEfloat& out,
		TEfloat val,
		TEbool fast = true) {
		out = invcbrt(val, fast);
	}

	TEvoid TILO_VECTORCALL invcbrt_2(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEbool fast = true) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_store_ps(out, _mm_sin_ps(_mm_set_ps(0, 0, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = invcbrt(val1, fast);
			out[1] = invcbrt(val2, fast);
		}
	}

	TEvoid TILO_VECTORCALL invcbrt_4(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEbool fast = true) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSE, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_store_ps(out, _mm_invcbrt_ps(_mm_set_ps(val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = invcbrt(val1, fast);
			out[1] = invcbrt(val2, fast);
			out[2] = invcbrt(val3, fast);
			out[3] = invcbrt(val4, fast);
		}
	}

	TEvoid TILO_VECTORCALL invcbrt_8(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8,
		TEbool fast = true) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm256_store_ps(out, _mm256_invcbrt_ps(_mm256_set_ps(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			invcbrt_4(out,
				val1,
				val2,
				val3,
				val4,
				fast);
			invcbrt_4(&out[4],
				val5,
				val6,
				val7,
				val8,
				fast);
		}
	}

	TEvoid TILO_VECTORCALL invcbrt_16(
		TEfloat* out,
		TEfloat val1,
		TEfloat val2,
		TEfloat val3,
		TEfloat val4,
		TEfloat val5,
		TEfloat val6,
		TEfloat val7,
		TEfloat val8,
		TEfloat val9,
		TEfloat val10,
		TEfloat val11,
		TEfloat val12,
		TEfloat val13,
		TEfloat val14,
		TEfloat val15,
		TEfloat val16,
		TEbool fast = true) {
		invcbrt_8(out,
			val1,
			val2,
			val3,
			val4,
			val5,
			val6,
			val7,
			val8,
			fast);
		invcbrt_8(&out[8],
			val9,
			val10,
			val11,
			val12,
			val13,
			val14,
			val15,
			val16,
			fast);
	}

	[[nodiscard]] constexpr TILO_INLINE TEdouble TILO_FASTCALL invcbrt(
		TEdouble val,
		TEbool fast = true) {
		if (!fast)
			return 1 / cbrt(val);
		const TEdouble y = bit_cast<TEdouble>(0x5fe6eb50c7b537a9 - (bit_cast<TEulong>(val) >> 1));
		return y * (1.5f - (val * 0.5f * y * y));
	}

	TILO_INLINE TEvoid invcbrt(
		TEdouble& out,
		TEdouble val,
		TEbool fast = true) {
		out = invcbrt(val, fast);
	}

	TEvoid TILO_VECTORCALL invcbrt_2(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEbool fast = true) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSE2, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_store_pd(out, _mm_invcbrt_pd(_mm_set_pd(val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = invcbrt(val1, fast);
			out[1] = invcbrt(val2, fast);
		}
	}

	TEvoid TILO_VECTORCALL invcbrt_4(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4,
		TEbool fast = true) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm256_store_pd(out, _mm256_invcbrt_pd(_mm256_set_pd(val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			invcbrt_2(out,
				val1,
				val2,
				fast);
			invcbrt_2(&out[2],
				val3,
				val4,
				fast);
		}
	}

	TEvoid TILO_VECTORCALL invcbrt_8(
		TEdouble* out,
		TEdouble val1,
		TEdouble val2,
		TEdouble val3,
		TEdouble val4,
		TEdouble val5,
		TEdouble val6,
		TEdouble val7,
		TEdouble val8,
		TEbool fast = true) {
		invcbrt_4(out,
			val1,
			val2,
			val3,
			val4,
			fast);
		invcbrt_4(&out[4],
			val5,
			val6,
			val7,
			val8,
			fast);
	}

	TEvoid TILO_VECTORCALL abs_16(
		TEbyte* out,
		TEbyte val1,
		TEbyte val2,
		TEbyte val3,
		TEbyte val4,
		TEbyte val5,
		TEbyte val6,
		TEbyte val7,
		TEbyte val8,
		TEbyte val9,
		TEbyte val10,
		TEbyte val11,
		TEbyte val12,
		TEbyte val13,
		TEbyte val14,
		TEbyte val15,
		TEbyte val16) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSSE3 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_storeu_epi8(out, _mm_abs_epi8(_mm_set_epi8(val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = abs(val1);
			out[1] = abs(val2);
			out[2] = abs(val3);
			out[3] = abs(val4);
			out[4] = abs(val5);
			out[5] = abs(val6);
			out[6] = abs(val7);
			out[7] = abs(val8);
			out[8] = abs(val9);
			out[9] = abs(val10);
			out[10] = abs(val11);
			out[11] = abs(val12);
			out[12] = abs(val13);
			out[13] = abs(val14);
			out[14] = abs(val15);
			out[15] = abs(val16);
		}
	}

	TEvoid TILO_VECTORCALL abs_32(
		TEbyte* out,
		TEbyte val1,
		TEbyte val2,
		TEbyte val3,
		TEbyte val4,
		TEbyte val5,
		TEbyte val6,
		TEbyte val7,
		TEbyte val8,
		TEbyte val9,
		TEbyte val10,
		TEbyte val11,
		TEbyte val12,
		TEbyte val13,
		TEbyte val14,
		TEbyte val15,
		TEbyte val16,
		TEbyte val17,
		TEbyte val18,
		TEbyte val19,
		TEbyte val20,
		TEbyte val21,
		TEbyte val22,
		TEbyte val23,
		TEbyte val24,
		TEbyte val25,
		TEbyte val26,
		TEbyte val27,
		TEbyte val28,
		TEbyte val29,
		TEbyte val30,
		TEbyte val31,
		TEbyte val32) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX2 && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm256_storeu_epi8(out, _mm256_abs_epi8(_mm256_set_epi8(val32, val31, val30, val29, val28, val27, val26, val25, val24, val23, val22, val21, val20, val19, val18, val17, val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			abs_16(out,
				val1,
				val2,
				val3,
				val4,
				val5,
				val6,
				val7,
				val8,
				val9,
				val10,
				val11,
				val12,
				val13,
				val14,
				val15,
				val16);
			abs_16(&out[16],
				val17,
				val18,
				val19,
				val20,
				val21,
				val22,
				val23,
				val24,
				val25,
				val26,
				val27,
				val28,
				val29,
				val30,
				val31,
				val31);
		}
	}

	TEvoid TILO_VECTORCALL abs_64(
		TEbyte* out,
		TEbyte val1,
		TEbyte val2,
		TEbyte val3,
		TEbyte val4,
		TEbyte val5,
		TEbyte val6,
		TEbyte val7,
		TEbyte val8,
		TEbyte val9,
		TEbyte val10,
		TEbyte val11,
		TEbyte val12,
		TEbyte val13,
		TEbyte val14,
		TEbyte val15,
		TEbyte val16,
		TEbyte val17,
		TEbyte val18,
		TEbyte val19,
		TEbyte val20,
		TEbyte val21,
		TEbyte val22,
		TEbyte val23,
		TEbyte val24,
		TEbyte val25,
		TEbyte val26,
		TEbyte val27,
		TEbyte val28,
		TEbyte val29,
		TEbyte val30,
		TEbyte val31,
		TEbyte val32,
		TEbyte val33,
		TEbyte val34,
		TEbyte val35,
		TEbyte val36,
		TEbyte val37,
		TEbyte val38,
		TEbyte val39,
		TEbyte val40,
		TEbyte val41,
		TEbyte val42,
		TEbyte val43,
		TEbyte val44,
		TEbyte val45,
		TEbyte val46,
		TEbyte val47,
		TEbyte val48,
		TEbyte val49,
		TEbyte val50,
		TEbyte val51,
		TEbyte val52,
		TEbyte val53,
		TEbyte val54,
		TEbyte val55,
		TEbyte val56,
		TEbyte val57,
		TEbyte val58,
		TEbyte val59,
		TEbyte val60,
		TEbyte val61,
		TEbyte val62,
		TEbyte val63,
		TEbyte val64) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm512_storeu_epi8(out, _mm512_abs_epi8(_mm512_set_epi8(val64, val63, val62, val61, val60, val59, val58, val57, val56, val55, val54, val53, val52, val51, val50, val49, val48, val47, val46, val45, val44, val43, val42, val41, val40, val39, val38, val37, val36, val35, val34, val33, val32, val31, val30, val29, val28, val27, val26, val25, val24, val23, val22, val21, val20, val19, val18, val17, val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			abs_32(out,
				val1,
				val2,
				val3,
				val4,
				val5,
				val6,
				val7,
				val8,
				val9,
				val10,
				val11,
				val12,
				val13,
				val14,
				val15,
				val16,
				val17,
				val18,
				val19,
				val20,
				val21,
				val22,
				val23,
				val24,
				val25,
				val26,
				val27,
				val28,
				val29,
				val30,
				val31,
				val32);
			abs_32(&out[32],
				val33,
				val34,
				val35,
				val36,
				val37,
				val38,
				val39,
				val40,
				val41,
				val42,
				val43,
				val44,
				val45,
				val46,
				val47,
				val48,
				val49,
				val50,
				val51,
				val52,
				val53,
				val54,
				val55,
				val56,
				val57,
				val58,
				val59,
				val60,
				val61,
				val62,
				val63,
				val64);
		}
	}

	TEvoid TILO_VECTORCALL abs_8(
		TEshort* out,
		TEshort val1,
		TEshort val2,
		TEshort val3,
		TEshort val4,
		TEshort val5,
		TEshort val6,
		TEshort val7,
		TEshort val8) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSSE3 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_storeu_epi16(out, _mm_abs_epi16(_mm_set_epi16(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = abs(val1);
			out[1] = abs(val2);
			out[2] = abs(val3);
			out[3] = abs(val4);
			out[4] = abs(val5);
			out[5] = abs(val6);
			out[6] = abs(val7);
			out[7] = abs(val8);
		}
	}

	TEvoid TILO_VECTORCALL abs_16(
		TEshort* out,
		TEshort val1,
		TEshort val2,
		TEshort val3,
		TEshort val4,
		TEshort val5,
		TEshort val6,
		TEshort val7,
		TEshort val8,
		TEshort val9,
		TEshort val10,
		TEshort val11,
		TEshort val12,
		TEshort val13,
		TEshort val14,
		TEshort val15,
		TEshort val16) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX2 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm256_storeu_epi16(out, _mm256_abs_epi16(_mm256_set_epi16(val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			abs_8(out,
				val1,
				val2,
				val3,
				val4,
				val5,
				val6,
				val7,
				val8);
			abs_8(&out[8],
				val9,
				val10,
				val11,
				val12,
				val13,
				val14,
				val15,
				val16);
		}
	}

	TEvoid TILO_VECTORCALL abs_32(
		TEshort* out,
		TEshort val1,
		TEshort val2,
		TEshort val3,
		TEshort val4,
		TEshort val5,
		TEshort val6,
		TEshort val7,
		TEshort val8,
		TEshort val9,
		TEshort val10,
		TEshort val11,
		TEshort val12,
		TEshort val13,
		TEshort val14,
		TEshort val15,
		TEshort val16,
		TEshort val17,
		TEshort val18,
		TEshort val19,
		TEshort val20,
		TEshort val21,
		TEshort val22,
		TEshort val23,
		TEshort val24,
		TEshort val25,
		TEshort val26,
		TEshort val27,
		TEshort val28,
		TEshort val29,
		TEshort val30,
		TEshort val31,
		TEshort val32) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm512_storeu_epi16(out, _mm512_abs_epi16(_mm512_set_epi16(val32, val31, val30, val29, val28, val27, val26, val25, val24, val23, val22, val21, val20, val19, val18, val17, val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			abs_16(out,
				val1,
				val2,
				val3,
				val4,
				val5,
				val6,
				val7,
				val8,
				val9,
				val10,
				val11,
				val12,
				val13,
				val14,
				val15,
				val16);
			abs_16(&out[16],
				val17,
				val18,
				val19,
				val20,
				val21,
				val22,
				val23,
				val24,
				val25,
				val26,
				val27,
				val28,
				val29,
				val30,
				val31,
				val31);
		}
	}

	TEvoid TILO_VECTORCALL abs_4(
		TEint* out,
		TEint val1,
		TEint val2,
		TEint val3,
		TEint val4) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.SSSE3 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_SSE_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_storeu_epi32(out, _mm_abs_epi32(_mm_set_epi32(val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = abs(val1);
			out[1] = abs(val2);
			out[2] = abs(val3);
			out[3] = abs(val4);
		}
	}

	TEvoid TILO_VECTORCALL abs_8(
		TEint* out,
		TEint val1,
		TEint val2,
		TEint val3,
		TEint val4,
		TEint val5,
		TEint val6,
		TEint val7,
		TEint val8) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX2 && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm256_storeu_epi32(out, _mm256_abs_epi32(_mm256_set_epi32(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			abs_4(out,
				val1,
				val2,
				val3,
				val4);
			abs_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	TEvoid TILO_VECTORCALL abs_16(
		TEint* out,
		TEint val1,
		TEint val2,
		TEint val3,
		TEint val4,
		TEint val5,
		TEint val6,
		TEint val7,
		TEint val8,
		TEint val9,
		TEint val10,
		TEint val11,
		TEint val12,
		TEint val13,
		TEint val14,
		TEint val15,
		TEint val16) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX512F && cpuInfo->flags.AVX512BW && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm512_storeu_epi32(out, _mm512_abs_epi32(_mm512_set_epi32(val16, val15, val14, val13, val12, val11, val10, val9, val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			abs_8(out,
				val1,
				val2,
				val3,
				val4,
				val5,
				val6,
				val7,
				val8);
			abs_8(&out[8],
				val9,
				val10,
				val11,
				val12,
				val13,
				val14,
				val15,
				val16);
		}
	}

	TEvoid TILO_VECTORCALL abs_2(
		TElong* out,
		TElong val1,
		TElong val2) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX512F && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm_storeu_epi64(out, _mm_abs_epi64(_mm_set_epi64x(val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			out[0] = abs(val1);
			out[1] = abs(val2);
		}
	}

	TEvoid TILO_VECTORCALL abs_4(
		TElong* out,
		TElong val1,
		TElong val2,
		TElong val3,
		TElong val4) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX && cpuInfo->flags.AVX512F && cpuInfo->flags.AVX512VL, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm256_storeu_epi64(out, _mm256_abs_epi64(_mm256_set_epi64x(val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			abs_2(out,
				val1,
				val2);
			abs_2(&out[2],
				val3,
				val4);
		}
	}

	TEvoid TILO_VECTORCALL abs_8(
		TElong* out,
		TElong val1,
		TElong val2,
		TElong val3,
		TElong val4,
		TElong val5,
		TElong val6,
		TElong val7,
		TElong val8) {
		TILO_ASSUME(simdEnabled)
		if (TILO_EXPECT_WITH_PROBABILITY(TILO_EXPECT(simdEnabled, TILO_SIMD_ENABLED_EXPECTATION) && cpuInfo->flags.AVX512F, 1, TILO_AVX_PROBABILITY)) [[TILO_SIMD_ATTR]] {
			_mm512_storeu_epi64(out, _mm512_abs_epi64(_mm512_set_epi64(val8, val7, val6, val5, val4, val3, val2, val1)));
		} else [[TILO_NO_SIMD_ATTR]] {
			abs_4(out,
				val1,
				val2,
				val3,
				val4);
			abs_4(&out[4],
				val5,
				val6,
				val7,
				val8);
		}
	}

	template <typename T1, typename T2>
	constexpr TILO_INLINE std::common_type_t<T1, T2> lcm(const T1 val1, const T2 val2) noexcept {
		return std::lcm(val1, val2);
	}

	//TODO add more functions
}

#undef TILO_SIMD_ATTR
#undef TILO_NO_SIMD_ATTR
#undef TILO_SVML_ATTR
#undef TILO_NO_SVML_ATTR
#undef TILO_ASSUME_SIMD
#undef TILO_SIMD_ENABLED_EXPECTATION
#undef TILO_ASSUME_SVML
#undef TILO_SIMD_ENABLED_SVML_SUPPORTED_EXPECTATION

#endif
