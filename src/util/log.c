#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "log.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void LOG(enum log_level level, const char* format, ...)
{
    if (level <= LOG_LEVEL) {
        va_list args;
        char prefix[512];
        switch (level) {
        case CRITICAL:
            strcpy(prefix, ANSI_COLOR_RED);
            strcat(prefix, "CRITICAL: ");
            break;
        case ERROR:
            strcpy(prefix, ANSI_COLOR_MAGENTA);
            strcat(prefix, "ERROR: ");
            break;
        case WARNING:
            strcpy(prefix, ANSI_COLOR_YELLOW);
            strcat(prefix, "WARNING: ");
            break;
        case INFO:
            strcpy(prefix, ANSI_COLOR_GREEN);
            strcat(prefix, "INFO: ");
            break;
        case DEBUG:
            strcpy(prefix, ANSI_COLOR_CYAN);
            strcat(prefix, "DEBUG: ");
            break;
        case TRACE:
            strcpy(prefix, ANSI_COLOR_BLUE);
            strcat(prefix, "TRACE: ");
            break;
        default:
            printf("BAD THING\n");
            exit(1);
            break;
        }
        strcat(prefix, ANSI_COLOR_RESET);

        char* out = prefix;
        strcat(out, format);
        strcat(out, "\n");
        fprintf(OUT, out, args);
    }
}
