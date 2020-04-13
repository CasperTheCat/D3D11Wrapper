#pragma once

#include "utils.h"

#ifndef SCOPED_LOCK
/**
 * Scoped Lock in C++17
 *
 * Fall back to LockGuard in C++14
 */
#if __cplusplus >= 201703L
#define SCOPED_LOCK(x) std::scoped_lock lock_ ## x (x)
#define SCOPED_LOCK_XY(x,y) std::scoped_lock lock_ ## x ## y (x,y)
#else
#define SCOPED_LOCK(x) std::lock_guard<std::mutex> lock_ ## x (x)
#define SCOPED_LOCK_XY(x,y) std::lock(x, y); \
            std::lock_guard<std::mutex> lock_ ## x (x, std::adopt_lock); \
            std::lock_guard<std::mutex> lock_ ## y (y, std::adopt_lock)
#endif
#endif


#ifndef NDEBUG
#define DEBUG_ONLY_PRINT(x) std::cout << x << std::endl
#define DEBUG_LOGLINE(x, msg) x << msg << std::endl

#define DEBUG_LINE(x, msg) \
	std::cout << "[" << std::to_string(uint64_t(this)) << "] " << msg << std::endl; \
	DEBUG_LOGLINE(x, msg)

#else
#define DEBUG_ONLY_PRINT(x)
#define DEBUG_LOGLINE(x, msg)
#define DEBUG_LINE(x, msg)
#endif

