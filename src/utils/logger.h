#ifndef UTIL_LOGGER_H

#define UTIL_LOGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

enum e_log_levels {
    LOG_LEVEL_FATAL = 0,
    LOG_LEVEL_ERROR = 1,
    LOG_LEVEL_WARN = 2,
    LOG_LEVEL_INFO = 3,
    LOG_LEVEL_DEBUG = 4,
    LOG_LEVEL_TRACE = 5
};

typedef enum e_log_levels log_levels;

#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

#if LOG_RELASE == 1
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif

void LOG(log_levels level, const char* message, ...);

#endif // !UTIL_LOGGER_H