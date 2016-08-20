#include<time.h>
#include "log_base.h"
#include "string.h"
#include <sstream>
#include <iostream>

using namespace Common;

LogBase::LogBase()
{
    time_t dwTimeStamp = time(NULL);
    struct tm tmNowTime = *(localtime(&dwTimeStamp));

    std::stringstream ossLogName;

    uint32_t dwFromatTime = 0;
    dwFromatTime = (tmNowTime.tm_year + 1900) * 1000000;
    dwFromatTime = dwFromatTime + (tmNowTime.tm_mon + 1) * 10000;
    dwFromatTime = dwFromatTime + tmNowTime.tm_mday * 100;
    dwFromatTime = dwFromatTime + tmNowTime.tm_hour;

    ossLogName << dwFromatTime << ".log"; 

    m_strLogName = ossLogName.str();
    
}

LogBase::LogBase(const char *strLogName,
         const uint32_t dwLogLevel)
{
    m_strLogName = (std::string)(strLogName);
}

LogBase::LogBase(const std::string &strLogName,
         const uint32_t dwLogLevel)
{
    m_strLogName = strLogName;
}

LogBase::~LogBase()
{
    close(m_iLogFd);
}

int LogBase::OpenLogFile()
{
    int iFileFlag = O_WRONLY|O_CREAT|O_APPEND;
    int iFileMode = S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH;
    m_iLogFd = open(m_strLogName.c_str(), iFileFlag, iFileMode);
    if(m_iLogFd == -1)
    {
        return -1;
    }

    return 0;
}

int LogBase::WriteLog(const std::string &strLog)
{
    return WriteLog(strLog.c_str());
}

int LogBase::WriteLog(const char *strLog)
{
    size_t iRet = write(m_iLogFd, strLog, strlen(strLog));
    
    if(iRet == -1)
    {
        return -1;
    }
    
    return 0;
}
