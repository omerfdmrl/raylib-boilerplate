#include "assert.h"

void report_assertion_failure(const char* expression, const char* message, const char* file, int line) {
    if(strlen(message) > 0)
        LOG(LOG_LEVEL_FATAL, "Assertion Failure: %s, message: '%s', in file:%s:%d\n", expression, message, file, line);
    else
        LOG(LOG_LEVEL_FATAL, "Assertion Failure: %s, in file:%s:%d\n", expression, file, line);
}