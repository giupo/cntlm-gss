#ifndef LOGGER_H
#define LOGGER_H

#include "zf_log.h"

#define LOG_VERBOSE 1
#define LOG_DEBUG   2
#define LOG_INFO    3
#define LOG_WARN    4
#define LOG_WARNING 4
#define LOG_ERROR   5
#define LOG_ERR     5
#define LOG_FATAL   6
#define LOG_NONE    0xFF

extern void cntlm_log(int priority, const char *message, ... );

#endif 