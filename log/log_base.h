#ifndef __BASE_LOG_BASE_H__
#define __BASE_LOG_BASE_H__

#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<ctype.h>
#include<string>

namespace Common
{

//日志基本组件
class LogBase
{
    public:
        LogBase();

        void SetLogName(const char *strLogName);

        void SetLogName(const std::string &strLogName);

        int OpenLogFile();

        int WriteLog(const char *strLog);

        int WriteLog(const std::string &strLog);

        ~LogBase();

    private:

    private:
        std::string m_strLogName;
        uint32_t m_dwLogLevel;
        int m_iLogFd;
};

}

#endif
