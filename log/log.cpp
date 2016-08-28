#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "log.h"
#include "log_base.h"

using namespace Common;

namespace Common
{

LogBase m_objLogBase;

int InitLog()
{
    int iRet = 0; 
    time_t dwTimeStamp = time(NULL);
    struct tm tmNowTime = *(localtime(&dwTimeStamp));

    std::stringstream ossLogName;

    uint32_t dwFromatTime = 0;
    dwFromatTime = (tmNowTime.tm_year + 1900) * 1000000;
    dwFromatTime = dwFromatTime + (tmNowTime.tm_mon + 1) * 10000;
    dwFromatTime = dwFromatTime + tmNowTime.tm_mday * 100;
    dwFromatTime = dwFromatTime + tmNowTime.tm_hour;

    ossLogName << dwFromatTime << ".log"; 
    
    std::string strLogName = ossLogName.str();

    m_objLogBase.SetLogName(strLogName);
    iRet = m_objLogBase.OpenLogFile();
    return iRet;
}

int InitLog(const std::string &strLogName)
{
    int iRet = 0;
    m_objLogBase.SetLogName(strLogName);
    iRet = m_objLogBase.OpenLogFile();
    return iRet;
}

void LogInfo(const char * strFormat, ...)
{
    char logBuffer[512];
    va_list args;
    va_start(args, strFormat);
    vsnprintf(logBuffer, 512-1, strFormat, args);
    m_objLogBase.WriteLog(logBuffer);
    va_end(args);
}
}
