#ifndef CB_UTIL_HPP__
#define CB_UTIL_HPP__

#include <csignal>

// a macro to ensure you meant to leave out that variable
#define CB_UNUSED(x) (void) (x)

// slightly less verbose function binds
#define CB_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#ifdef __linux__
#define CB_ASSERT_CORE(x, ...) \
{ if(!(x)) \
    { \
        Log::core_error("Assertion Failed: {0}", __VA_ARGS__); \
        std::raise(SIGTRAP); \
} }

#define CB_ASSERT(x, ...) \
{ if(!(x)) \
    { \
        Log::error("Assertion Failed: {0}", __VA_ARGS__); \
        std::raise(SIGTRAP); \
} }

#elif __APPLE__ && defined(__MACH__)

#elif _WIN32 || defined(_WIN64)
#define CB_ASSERT_CORE(x, ...) \
{ if(!(x)) \
    { \
        Log::core_error("Assertion Failed: {0}", __VA_ARGS__); \
        __debugbreak(); \
} }

#define CB_ASSERT(x, ...) \
{ if(!(x)) \
    { \
        Log::error("Assertion Failed: {0}", __VA_ARGS__); \
        __debugbreak(); \
} }

#endif


#endif // CB_UTIL_HPP__