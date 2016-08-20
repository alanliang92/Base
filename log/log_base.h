#ifndef __BASE_LOG_H__
#define __BASE_LOG_H__

#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<ctype.h>
#include<string>

namespace Common
{

//日志组件
class LogBase
{
    public:
        LogBase();

        LogBase(const char *strLogName,
            const uint32_t dwLogLevel);

        LogBase(const std::string &strLogName,
            const uint32_t dwLogLevel);

        int OpenLogFile();

        int WriteLog(const std::string &strLog);

        int WriteLog(const char *strLog);

        ~LogBase();

    private:

    private:
        std::string m_strLogName;
        uint32_t m_dwLogLevel;
        int m_iLogFd;
};

}

#endif
