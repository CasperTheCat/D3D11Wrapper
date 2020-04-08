#pragma once

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

