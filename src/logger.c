#include "logger.h"
#include <stdarg.h>
#include <stdio.h>

void cntlm_log(int priority, const char *message, ... ) {
  va_list args;
  va_start (args, message);

  switch(priority) {
    case LOG_VERBOSE: {
      ZF_LOGV(message, args);
    } break;
    
    case LOG_DEBUG: {
      ZF_LOGD(message, args);
    } break;
    
    case LOG_INFO: {
       ZF_LOGI(message, args);
    } break;
    
    case LOG_WARN: {
      ZF_LOGW(message, args);
    } break;
    
    case LOG_ERROR: {
      ZF_LOGE(message, args);
    } break;
    
    case LOG_FATAL: {
      ZF_LOGF(message, args);
    } break;
    
    case LOG_NONE: break;
    
    default: {
      ZF_LOGI(message, args);
    }
  }
}