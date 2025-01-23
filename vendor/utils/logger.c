#include "logger.h"

void LOG(log_levels level, const char* message, ...) {
    if(level == LOG_LEVEL_WARN && LOG_WARN_ENABLED != 1) return;
    if(level == LOG_LEVEL_INFO && LOG_INFO_ENABLED != 1) return;
    if(level == LOG_LEVEL_DEBUG && LOG_DEBUG_ENABLED != 1) return;
    if(level == LOG_LEVEL_TRACE && LOG_TRACE_ENABLED != 1) return;

    const char* level_strings[6];
    char out_message[32000];
    char out_message2[32001];

    level_strings[0] = "[FATAL]: "; level_strings[1] = "[ERROR]: "; level_strings[2] = "[WARN]:  ";
    level_strings[3] = "[INFO]:  "; level_strings[4] = "[DEBUG]: "; level_strings[5] = "[TRACE]: ";
    memset(out_message, 0, sizeof(out_message));

    __builtin_va_list arg_ptr;

    va_start(arg_ptr, message);
    vsnprintf(out_message, 32000, message, arg_ptr);
    va_end(arg_ptr);

    sprintf(out_message2, "%s%s\n", level_strings[level], out_message);
    printf("%s", out_message2);
}