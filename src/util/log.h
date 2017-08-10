#ifndef UTIL_LOG_H
#define UTIL_LOG_H

#include <stdio.h>

#define OUT stdout

enum log_level {
    CRITICAL = 0,
    ERROR = 1,
    WARNING = 2,
    INFO = 3,
    DEBUG = 4,
    TRACE = 5,
};

#define LOG_LEVEL 5

void LOG(enum log_level, const char* format, ...);

#endif // UTIL_LOG_H
