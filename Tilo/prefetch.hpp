// Platform independent prefetch hint
#ifndef TILO_PREFETCH_HPP
#define TILO_PREFETCH_HPP

#include "compilers.hpp"

#if defined(TILO_COMPILER_GNU) || defined(TILO_COMPILER_CLANG)
#	define TILO_PREFETCH_READ_T0(_addr) __builtin_prefetch(_addr, 0, 0);
#	define TILO_PREFETCH_READ_T1(_addr) __builtin_prefetch(_addr, 0, 1);
#	define TILO_PREFETCH_READ_T2(_addr) __builtin_prefetch(_addr, 0, 2);
#	define TILO_PREFETCH_READ_T3(_addr) __builtin_prefetch(_addr, 0, 3);
#	define TILO_PREFETCH_WRITE_T0(_addr) __builtin_prefetch(_addr, 1, 0);
#	define TILO_PREFETCH_WRITE_T1(_addr) __builtin_prefetch(_addr, 1, 1);
#	define TILO_PREFETCH_WRITE_T2(_addr) __builtin_prefetch(_addr, 1, 2);
#	define TILO_PREFETCH_WRITE_T3(_addr) __builtin_prefetch(_addr, 1, 3);
#elif defined(TILO_COMPILER_MS)
#	include <winnt.h>
#	define TILO_PREFETCH_READ_T0(_addr) PreFetchCacheLine(PF_NON_TEMPORAL_LEVEL_ALL, _addr);
#	define TILO_PREFETCH_READ_T1(_addr) PreFetchCacheLine(PF_TEMPORAL_LEVEL_1, _addr);
#	define TILO_PREFETCH_READ_T2(_addr) PreFetchCacheLine(PF_TEMPORAL_LEVEL_1, _addr);
#	define TILO_PREFETCH_READ_T3(_addr) PreFetchCacheLine(PF_TEMPORAL_LEVEL_1, _addr);
#	define TILO_PREFETCH_WRITE_T0(_addr) PreFetchCacheLine(PF_NON_TEMPORAL_LEVEL_ALL, _addr);
#	define TILO_PREFETCH_WRITE_T1(_addr) PreFetchCacheLine(PF_TEMPORAL_LEVEL_1, _addr);
#	define TILO_PREFETCH_WRITE_T2(_addr) PreFetchCacheLine(PF_TEMPORAL_LEVEL_1, _addr);
#	define TILO_PREFETCH_WRITE_T3(_addr) PreFetchCacheLine(PF_TEMPORAL_LEVEL_1, _addr);
#else
#	define TILO_PREFETCH_READ_T0
#	define TILO_PREFETCH_READ_T1
#	define TILO_PREFETCH_READ_T2
#	define TILO_PREFETCH_READ_T3
#	define TILO_PREFETCH_WRITE_T0
#	define TILO_PREFETCH_WRITE_T1
#	define TILO_PREFETCH_WRITE_T2
#	define TILO_PREFETCH_WRITE_T3
#endif

#endif
