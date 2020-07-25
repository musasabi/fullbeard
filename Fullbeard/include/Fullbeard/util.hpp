#ifndef FULLBEARD_UTIL_HPP__
#define FULLBEARD_UTIL_HPP__

#include <csignal>

// a macro to ensure you meant to leave out that variable
#define UNUSED__(x) (void) (x)

// slightly less verbose function binds
#define BIND_EVENT_FN__(fn) std::bind(&fn, this, std::placeholders::_1)

#define ASSERT_CORE__(x, ...) \
{ if(!(x)) \
    { \
        Log::core_error("Assertion Failed: {0}", __VA_ARGS__); \
        std::raise(SIGTRAP); \
} }

#define ASSERT__(x, ...) \
{ if(!(x)) \
    { \
        Log::error("Assertion Failed: {0}", __VA_ARGS__); \
        std::raise(SIGTRAP); \
} }

#endif // FULLBEARD_UTIL_HPP__