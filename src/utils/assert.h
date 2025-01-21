#ifndef UTIL_ASSERT_H

#define UTIL_ASSERT_H

#include "logger.h"

#define ASSERT(expr)                                                 \
    {                                                                \
        if (expr)                                                    \
            ;                                                        \
        else {                                                       \
            report_assertion_failure(#expr, "", __FILE__, __LINE__); \
            __builtin_trap();                                        \
        }                                                            \
    }

#define ASSERT_MSG(expr, message)                                         \
    {                                                                     \
        if (expr)                                                         \
            ;                                                             \
        else {                                                            \
            report_assertion_failure(#expr, message, __FILE__, __LINE__); \
            __builtin_trap();                                             \
        }                                                                 \
    }

void report_assertion_failure(const char* expression, const char* message, const char* file, int line);

#endif // !UTIL_ASSERT_H