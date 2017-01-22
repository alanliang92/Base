#include <time.h>
#include "log_base.h"
#include "string.h"
#include <sstream>
#include <iostream>

using namespace Common;

#define LOG_PATH "/home/lancelot/log/"

LogBase::LogBase()
{
    m_strLogName = "";
    m_iLogFd = -1;
}

LogBase::~LogBase()
{
    close(m_iLogFd);
}

void LogBase::SetLogName(const char *strLogName)
{
    m_strLogName = (std::string)(strLogName);
}

void LogBase::SetLogName(const std::string &strLogName)
{
    m_strLogName = strLogName;
}

int LogBase::OpenLogFile()
{
    int iFileFlag = O_WRONLY | O_CREAT | O_APPEND;
    int iFileMode = S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH;
    std::string strLogFilePath = LOG_PATH + m_strLogName;
    m_iLogFd = open(strLogFilePath.c_str(), iFileFlag, iFileMode);
    if(m_iLogFd == -1)
    {
        return -1;
    }

    return 0;
}

int LogBase::WriteLog(const char *strLog)
{
    ssize_t iRet = write(m_iLogFd, strLog, strlen(strLog));
    
    if(iRet == -1)
    {
        return -1;
    }

    return 0;
}

int LogBase::WriteLog(const std::string &strLog)
{
    return WriteLog(strLog.c_str());
}
