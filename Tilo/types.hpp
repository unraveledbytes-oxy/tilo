// Wrap C++ integral types to ensure they're alle the same size across all compilers and platforms
#ifndef TILO_TYPES_HPP
#define TILO_TYPES_HPP

#include <cstdint>
#include "compilers.hpp"

namespace te {
	// Just for completeness
	typedef void TEvoid;
	typedef bool TEbool;
	typedef size_t TEsize;

	// Integer types
	typedef int8_t TEbyte;
	typedef uint8_t TEubyte;
	typedef int16_t TEshort;
	typedef uint16_t TEushort;
	typedef int32_t TEint;
	typedef uint32_t TEuint;
	typedef int64_t TElong;
	typedef uint64_t TEulong;

	// Fast integer types
	typedef int_fast8_t TEfastbyte;
	typedef uint_fast8_t TEfastubyte;
	typedef int_fast16_t TEfastshort;
	typedef uint_fast16_t TEfastushort;
	typedef int_fast32_t TEfastint;
	typedef uint_fast32_t TEfastuint;
	typedef int_fast64_t TEfastlong;
	typedef uint_fast64_t TEfastulong;

	// Pointer integer
	typedef intptr_t TEpointer;

	// Fixed-size floating point numbers
#if defined(TILO_COMPILER_GNU) || defined(TILO_COMPILER_CLANG)
	// typedef float TEfloat TYPE_MODE(__SF__);
	typedef float TEfloat __attribute__ ((mode(SF)));
	typedef TEfloat* TEafloat __attribute__ ((aligned(16)));
#elif FLT_MANT_DIG==24
	typedef float TEfloat;
#	ifdef TILO_COMPILER_GNU
	typedef TEfloat* TEafloat __attribute__ ((aligned(16)));
#	elif defined(TILO_COMPILER_MS)
	typedef __declspec(align(16)) TEfloat* TEafloat;
#	endif
#elif DBL_MANT_DIG==24
	typedef double TEfloat;
#	ifdef TILO_COMPILER_GNU
	typedef TEfloat* TEafloat __attribute__ ((aligned(16)));
#	elif defined(TILO_COMPILER_MS)
	typedef __declspec(align(16)) TEfloat* TEafloat;
#	endif
#else
	typedef float TEfloat;
#	ifdef TILO_COMPILER_GNU
	typedef TEfloat* TEafloat __attribute__ ((aligned(16)));
#	elif defined(TILO_COMPILER_MS)
	typedef __declspec(align(16)) TEfloat* TEafloat;
#	endif
#endif

#if defined(TILO_COMPILER_GNU) || defined(TILO_COMPILER_CLANG)
	typedef float TEdouble __attribute__((mode(DF)));
	typedef TEdouble* TEadouble __attribute__ ((aligned(16)));
#elif FLT_MANT_DIG==53
	typedef float TEdouble;
#	ifdef TILO_COMPILER_GNU
	typedef TEdouble* TEadouble __attribute__ ((aligned(16)));
#	elif defined(TILO_COMPILER_MS)
	typedef __declspec(align(16)) TEdouble* TEadouble;
#	endif
#elif DBL_MANT_DIG==53
	typedef double TEdouble;
#	ifdef TILO_COMPILER_GNU
	typedef TEdouble* TEadouble __attribute__ ((aligned(16)));
#	elif defined(TILO_COMPILER_MS)
	typedef __declspec(align(16)) TEdouble* TEadouble;
#	endif
#elif LDBL_MANT_DIG==53
	typedef long double TEdouble;
#	ifdef TILO_COMPILER_GNU
	typedef TEdouble* TEadouble __attribute__ ((aligned(16)));
#	elif defined(TILO_COMPILER_MS)
	typedef __declspec(align(16)) TEdouble* TEadouble;
#	endif
#else
	typedef double TEdouble;
#	ifdef TILO_COMPILER_GNU
	typedef TEdouble* TEadouble __attribute__ ((aligned(16)));
#	elif defined(TILO_COMPILER_MS)
	typedef __declspec(align(16)) TEdouble* TEadouble;
#	endif
#endif
}

#endif
