#ifndef __BASE_LOG_H__
#define __BASE_LOG_H__

#include <string>
#include <stdarg.h>
#include "log_base.h"

namespace Common
{

int InitLog();

int InitLog(const std::string &strLogName);

void LogInfo(const char * strFormat, ...);

extern LogBase m_objLogBase;

}

#endif
