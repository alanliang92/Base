#include <unistd.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "log.h"
#include "log_base.h"

using namespace Common;

Log::Log()
{
    m_dwLogLevel = 0;
    m_strLogName = "";
}

Log::~Log()
{

}

void Log::InitLog(const uint32_t dwLogLevel)
{
    time_t dwTimeStamp = time(NULL);
    struct tm tmNowTime = *(localtime(&dwTimeStamp));

    std::stringstream ossLogName;

    uint32_t dwFromatTime = 0;
    dwFromatTime = (tmNowTime.tm_year + 1900) * 1000000;
    dwFromatTime = dwFromatTime + (tmNowTime.tm_mon + 1) * 10000;
    dwFromatTime = dwFromatTime + tmNowTime.tm_mday * 100;
    dwFromatTime = dwFromatTime + tmNowTime.tm_hour;

    ossLogName << dwFromatTime; 
    
    m_strLogName = ossLogName.str();
    m_dwLogLevel = dwLogLevel;

    InitLogBase();
}

void Log::InitLog(const std::string &strLogName,
         const uint32_t dwLogLevel)
{
    size_t dwIndex = m_strLogName.find_last_of(".log");
    if(dwIndex != std::string::npos)
    {
        m_strLogName = m_strLogName.substr(0, dwIndex);
    }
    else
    {
        m_strLogName = strLogName;
    }

    m_dwLogLevel = dwLogLevel;

    InitLogBase();
}

void Log::InitLogBase()
{
    InitDebugLog();

    InitErrorLog();

    InitKeyLog();
}

void Log::InitDebugLog()
{
    std::string strDebugLogName = m_strLogName + "_debug.log";
    m_oLogDebug.SetLogName(strDebugLogName);
    uint32_t iRet = m_oLogDebug.OpenLogFile();

    if(iRet != 0)
    {
        printf("DebugLog[%s] open fail", strDebugLogName.c_str());
    }
}

void Log::InitErrorLog()
{
    std::string strErrorLogName = m_strLogName + "_error.log";
    m_oLogError.SetLogName(strErrorLogName);
    uint32_t iRet = m_oLogError.OpenLogFile();

    if(iRet != 0)
    {
        printf("ErrorLog[%s] open fail", strErrorLogName.c_str());
    }
}

void Log::InitKeyLog()
{
    std::string strKeyLogName = m_strLogName + "_key.log";
    m_oLogKey.SetLogName(strKeyLogName);
    uint32_t iRet = m_oLogKey.OpenLogFile();

    if(iRet != 0)
    {
        printf("KeyLog[%s] open fail", strKeyLogName.c_str());
    }
}

void Log::MarkDebugLog(const std::string &strLogContent)
{
    if((m_dwLogLevel & LOG_DEBUG) == LOG_DEBUG)
    {
        m_oLogDebug.WriteLog(strLogContent);
    }
}

void Log::MarkErrorLog(const std::string &strLogContent)
{
    if((m_dwLogLevel & LOG_ERROR) == LOG_ERROR)
    {
        m_oLogError.WriteLog(strLogContent);
    }
}

void Log::MarkKeyLog(const std::string &strLogContent)
{
    if((m_dwLogLevel & LOG_KEY) == LOG_KEY)
    {
        m_oLogKey.WriteLog(strLogContent);
    }
}

