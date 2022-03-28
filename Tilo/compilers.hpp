// Compiler-specific macros
#ifndef TILO_COMPILERS_HPP
#define TILO_COMPILERS_HPP

#ifdef __GNUC__
#	define TILO_COMPILER_GNU
#endif

#ifdef __clang__
#	define TILO_COMPILER_CLANG
#endif

#ifdef _MSC_VER
#	define TILO_COMPILER_MS
#endif

#endif