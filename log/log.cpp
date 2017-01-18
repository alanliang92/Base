#include <unistd.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "log.h"
#include "log_base.h"

using namespace Common;

#define MAX_BUFFER 100 

//TODO 继续抽象函数

namespace Common
{

LogBase m_objLogBase;

//获取可执行程序的名
std::string GetExecuteName(const pid_t pid)
{
    char pidPath[128];
    char executeName[1024];
    snprintf(pidPath, 128, "/proc/%d/cmdline", pid);

    int executeCmdLineFd = open(pidPath, O_RDONLY);

    if(executeCmdLineFd == -1)
    {
        return "Open ProcFile Error";
    }

    ssize_t iRet = read(executeCmdLineFd, executeName, 1024);
    if(iRet == -1)
    {
        return "Read ProcFile Error";
    }

    std::string strExecuteName = std::string(executeName);
    std::vector<std::string> vecResult;
    StringUtils::SplitBySeparator(strExecuteName, '/', vecResult);

    close(executeCmdLineFd);

    return vecResult[vecResult.size()-1];
}

std::string MakeExtendContent()
{
    std::stringstream oss;

    pid_t pid = getpid();    

    time_t dwTimeStamp = time(NULL); 
    struct tm* tmNowTime = localtime(&dwTimeStamp);
    char formatTimeBuffer[128];
    strftime(formatTimeBuffer, 128, "%F %T", tmNowTime);

    oss << "[" << formatTimeBuffer << "]";
    oss << "|" << GetExecuteName(pid);
    oss << "|" << pid; 
    oss << "|";

    return oss.str();
}

std::string MakeExtendContent(const std::string &strFullFileName,
        const std::string &strFunction,
        const uint32_t dwLineNo)
{
    std::stringstream oss;

    pid_t pid = getpid();    

    time_t dwTimeStamp = time(NULL); 
    struct tm* tmNowTime = localtime(&dwTimeStamp);
    char formatTimeBuffer[128];
    strftime(formatTimeBuffer, 128, "%F %T", tmNowTime);

    std::vector<std::string> vecFileName;
    StringUtils::SplitBySeparator(strFullFileName, '/', vecFileName);
    std::string strFileName = vecFileName[vecFileName.size()-1];

    oss << "[" << formatTimeBuffer << "]";
    oss << "|" << GetExecuteName(pid);
    oss << "|" << pid; 
    oss << "|" << strFileName << ":" << dwLineNo;
    oss << "|" << strFunction;
    oss << "|";

    return oss.str();
}

int InitLog(const uint32_t dwLogLevel)
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
    m_objLogBase.SetLogLevel(dwLogLevel);
    iRet = m_objLogBase.OpenLogFile();
    return iRet;
}

int InitLog(const std::string &strLogName, const uint32_t dwLogLevel)
{
    int iRet = 0;
    m_objLogBase.SetLogName(strLogName);
    m_objLogBase.SetLogLevel(dwLogLevel);
    iRet = m_objLogBase.OpenLogFile();
    return iRet;
}

void ExtLogInfo(const std::string &strFullFileName, 
        const std::string &strFunction,
        const uint32_t dwLineNo,
        const char * strFormat, 
        ...)
{
    if((m_objLogBase.GetLogLevel() & LOG_INFO) != LOG_INFO)
    {
        return ;
    }
    else
    {
        std::string strExtendContent = MakeExtendContent(strFullFileName, strFunction, dwLineNo);

        char logBuffer[MAX_BUFFER];
        va_list args;
        va_start(args, strFormat);
        vsnprintf(logBuffer, MAX_BUFFER, strFormat, args);
        logBuffer[strlen(logBuffer)] = '\n';
        std::string strLog = strExtendContent + std::string(logBuffer);
        m_objLogBase.WriteLog(strLog.c_str());
        va_end(args);
    }
}

void LogInfo(const char * strFormat, ...)
{
    if((m_objLogBase.GetLogLevel() & LOG_INFO) != LOG_INFO)
    {
        return ;
    }
    else
    {
        std::string strExtendContent = MakeExtendContent();

        char logBuffer[MAX_BUFFER];
        va_list args;
        va_start(args, strFormat);
        vsnprintf(logBuffer, MAX_BUFFER, strFormat, args);
        logBuffer[strlen(logBuffer)] = '\n';
        std::string strLog = strExtendContent + std::string(logBuffer);
        m_objLogBase.WriteLog(strLog.c_str());
        va_end(args);
    }
}
}
