#pragma once

#if !defined(K5_ASSERT_ENABLE)
#if !defined(NDEBUG)
#define K5_ASSERT_ENABLE 1
#endif
#endif

#if K5_ASSERT_ENABLE
#include <cstdio>

// Assert filename
#define _K5_ASSERT_FILE __FILE__

// Assert line number
#define _K5_ASSERT_LINE __LINE__

// Assert function name
#if defined(__GNUC__) || defined(__clang__)
#define _K5_ASSERT_FUNCTION __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
#define _K5_ASSERT_FUNCTION __FUNCSIG__
#else
#define _K5_ASSERT_FUNCTION __FUNCTION__
#endif

// Debug trap function
#if defined(__linux__)
#include <csignal>
        #define _K5_ASSERT_TRAP raise(SIGTRAP)
#elif defined(_MSC_VER)
extern void __cdecl __debugbreak(void)
        #define _K5_ASSERT_TRAP __debugbreak()
#else
#define _K5_ASSERT_TRAP ((void)0)
#endif

// Stop warning about passing zero args after the message
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#endif

#define _K5_GET_ASSERT(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, NAME, ...) NAME
#define K5_ASSERT(...) _K5_GET_ASSERT(__VA_ARGS__,\
        _K5_ASSERT_MSG, _K5_ASSERT_MSG, _K5_ASSERT_MSG, _K5_ASSERT_MSG,\
        _K5_ASSERT_MSG, _K5_ASSERT_MSG, _K5_ASSERT_MSG, _K5_ASSERT_MSG,\
        _K5_ASSERT_MSG, _K5_ASSERT_MSG, _K5_ASSERT_MSG, _K5_ASSERT_MSG, _K5_ASSERT_MSG, _K5_ASSERT_NNOSG) (__VA_ARGS__)

#define _K5_ASSERT_MSG(expr, message, ...)\
        if (!(expr)) {\
            fprintf(stderr, "Assertion '%s' failed!\n", #expr);\
            fprintf(stderr, "  | file      '%s:%d'\n", _K5_ASSERT_FILE, _K5_ASSERT_LINE);\
            fprintf(stderr, "  | function  '%s'\n", _K5_ASSERT_FUNCTION);\
            fprintf(stderr, "  | message   '");\
            fprintf(stderr, (message), ##__VA_ARGS__);\
            fprintf(stderr, "'\n");\
            _K5_ASSERT_TRAP;\
        }

#define _K5_ASSERT_NOMSG(expr)\
        if (!(expr)) {\
            fprintf(stderr, "Assertion '%s' failed!\n", #expr);\
            fprintf(stderr, "  | file      '%s:%d'\n", _K5_ASSERT_FILE);\
            fprintf(stderr, "  | function  '%s'\n", _K5_ASSERT_FUNCTION);\
            _K5_ASSERT_TRAP;\
        }
#else
#define K5_ASSERT(...) ((void)0)
#endif