#ifndef __BASE_LOG_BASE_H__
#define __BASE_LOG_BASE_H__

#include <stdint.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <string>

enum LOG_LEVEL
{
    LOG_INFO = 1,
    LOG_DEBUG = 1 << 1,
    LOG_ERROR = 1 << 2,
    LOG_KEY = 1 << 3
};

namespace Common
{

//日志基本组件
class LogBase
{
    public:
        LogBase();

        ~LogBase();

        void SetLogName(const char *strLogName);

        void SetLogName(const std::string &strLogName);

        int OpenLogFile();

        int WriteLog(const char *strLog);

        int WriteLog(const std::string &strLog);

    private:

    private:
        std::string m_strLogName;
        uint32_t m_dwLogLevel;
        int m_iLogFd;
};

}

#endif
