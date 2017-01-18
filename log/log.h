#ifndef __BASE_LOG_H__
#define __BASE_LOG_H__

#include <string>
#include <stdarg.h>
#include "string_utils.h"
#include "log_base.h"

#define LOG_INFO(format, args...) \
{\ 
    std::string strFullFileName = __FILE__; \
    std::string strFunction = __FUNCTION__; \
    uint32_t dwLineNo = __LINE__; \
    ExtLogInfo(strFullFileName, strFunction, dwLineNo, format, args); \
}

namespace Common
{

int InitLog(const uint32_t dwLogLevel = 15);

int InitLog(const std::string &strLogName, const uint32_t dwLogLevel = 15);

void ExtLogInfo(const std::string &strFileName,
        const std::string &strFunction,
        const uint32_t dwLineNo,
        const char * strFormat,
        ...);

void LogInfo(const char * strFormat, ...);

extern LogBase m_objLogBase;
}

#endif
