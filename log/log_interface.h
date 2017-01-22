#ifndef __BASE_LOG_INTERFACE_H__
#define __BASE_LOG_INTERFACE_H__

#include <string>
#include <stdarg.h>
#include "string_utils.h"
#include "log.h"

#define LOG_DEBUG(format, args...) \
{\ 
    std::string strFullFileName = __FILE__; \
    std::string strFunction = __FUNCTION__; \
    uint32_t dwLineNo = __LINE__; \
    ExtLogDebug(strFullFileName, strFunction, dwLineNo, format, args); \
}

#define LOG_ERROR(format, args...) \
{\ 
    std::string strFullFileName = __FILE__; \
    std::string strFunction = __FUNCTION__; \
    uint32_t dwLineNo = __LINE__; \
    ExtLogError(strFullFileName, strFunction, dwLineNo, format, args); \
}

#define LOG_KEY(format, args...) \
{\ 
    std::string strFullFileName = __FILE__; \
    std::string strFunction = __FUNCTION__; \
    uint32_t dwLineNo = __LINE__; \
    ExtLogKey(strFullFileName, strFunction, dwLineNo, format, args); \
}

using namespace Common;

namespace Common
{
void InitLog(const uint32_t dwLogLevel = 15);

void InitLog(const std::string &strLogName, const uint32_t dwLogLevel = 15);

void ExtLogDebug(const std::string &strFileName,
        const std::string &strFunction,
        const uint32_t dwLineNo,
        const char * strFormat,
        ...);

void LogDebug(const char * strFormat, ...);

void ExtLogError(const std::string &strFileName,
        const std::string &strFunction,
        const uint32_t dwLineNo,
        const char * strFormat,
        ...);

void LogError(const char * strFormat, ...);

void ExtLogKey(const std::string &strFileName,
        const std::string &strFunction,
        const uint32_t dwLineNo,
        const char * strFormat,
        ...);

void LogKey(const char * strFormat, ...);

extern Log m_oLog;
}

#endif
