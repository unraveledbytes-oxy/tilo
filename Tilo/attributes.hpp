#ifndef TILO_ATTRIBUTES_HPP
#define TILO_ATTRIBUTES_HPP

#include "compilers.hpp"

#if defined(TILO_COMPILER_GNU) || defined(TILO_COMPILER_CLANG)
#	ifdef _M_IX86
#		define TILO_CDECL __attribute__ ((cdecl))
#		define TILO_FASTCALL __attribute__ ((fastcall))
#		define TILO_THISCALL __attribute__ ((thiscall))
#	else
#		define TILO_FASTCALL
#		define TILO_THISCALL
#	endif
#	define TILO_VECTORCALL
#	define TILO_INLINE __attribute__ ((always_inline)) inline
#	define TILO_ALLOCATOR
#	define TILO_NOALIAS
#	define TILO_RESTRICT_FUNC
#	define TILO_RESTRICT __restrict__
#	define TILO_NAKED __attribute__ ((naked))
#	define TILO_EXPECT(_expr, _expectation) __builtin_expect(_expr, _expectation)
#	define TILO_EXPECT_WITH_PROBABILITY(_expr, _expectation, _probability) __builtin_expect_with_probability(_expr, _expectation, _probability)
#	define TILO_ASSUME(_expr)
#	define TILO_ALIGN(_alignment) __attribute__ ((aligned(_alignment)))
#	define TILO_UNREACHABLE __builtin_unreachable();
#elif defined(TILO_COMPILER_MS)
#	define TILO_CDECL __cdecl
#	define TILO_FASTCALL __fastcall
#	define TILO_THISCALL __thiscall
#	define TILO_VECTORCALL __vectorcall
#	define TILO_INLINE __forceinline
#	define TILO_ALLOCATOR __declspec(allocator)
#	define TILO_NOALIAS __declspec(noalias)
#	define TILO_RESTRICT_FUNC __declspec(restrict)
#	define TILO_RESTRICT __restrict
#	define TILO_NAKED __declspec(naked)
#	define TILO_EXPECT(_expr, _expectation) _expr
#	define TILO_EXPECT_WITH_PROBABILITY(_expr, _expectation, _probability) _expr
#	define TILO_ASSUME(_expr) __assume(_expr);
#	define TILO_ALIGN(_alignment) __declspec(align(_alignment))
#	define TILO_UNREACHABLE __assume(0);
#else
#	define TILO_CDECL
#	define TILO_FASTCALL
#	define TILO_THISCALL
#	define TILO_VECTORCALL
#	define TILO_INLINE inline
#	define TILO_ALLOCATOR
#	define TILO_NOALIAS
#	define TILO_RESTRICT_FUNC
#	define TILO_RESTRICT
#	define TILO_NAKED
#	define TILO_EXPECT(_expr, _expectation) _expr
#	define TILO_EXPECT_WITH_PROBABILITY(_expr, _expectation, _probability) _expr
#	define TILO_ASSUME(_expr)
#	define TILO_ALIGN(_alignment)
#	define TILO_UNREACHABLE
#endif

#endif
