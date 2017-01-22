#ifndef __BASE_LOG_H__
#define __BASE_LOG_H__

#include <string>
#include <stdarg.h>
#include "string_utils.h"
#include "log_base.h"

namespace Common
{

class Log
{
    public:
        Log();
        ~Log();

    public:
        void InitLog(const uint32_t dwLogLevel = 15);

        void InitLog(const std::string &strLogName,
            const uint32_t dwLogLevel = 15);

        void MarkDebugLog(const std::string &strLogContent);

        void MarkErrorLog(const std::string &strLogContent);

        void MarkKeyLog(const std::string &strLogContent);

    private:
        void InitLogBase();

        void InitDebugLog();

        void InitErrorLog();

        void InitKeyLog();

    private:
        uint32_t m_dwLogLevel;

        std::string m_strLogName;

        LogBase m_oLogDebug;
        LogBase m_oLogError;
        LogBase m_oLogKey;
};
}

#endif
