#include <unistd.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "log_interface.h"
#include "log.h"

using namespace Common;

#define MAX_BUFFER 100 

namespace Common
{

Log m_oLog;

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

void InitLog(const uint32_t dwLogLevel)
{
    m_oLog.InitLog(dwLogLevel);
}

void InitLog(const std::string &strLogName, const uint32_t dwLogLevel)
{
    m_oLog.InitLog(strLogName, dwLogLevel);
}

void ExtLogDebug(const std::string &strFullFileName, 
        const std::string &strFunction,
        const uint32_t dwLineNo,
        const char * strFormat, 
        ...)
{
    std::string strExtendContent = MakeExtendContent(strFullFileName, strFunction, dwLineNo);

    char logBuffer[MAX_BUFFER];
    va_list args;
    va_start(args, strFormat);
    vsnprintf(logBuffer, MAX_BUFFER, strFormat, args);
    va_end(args);

    std::string strLog = strExtendContent + std::string(logBuffer) + "\n";
    m_oLog.MarkDebugLog(strLog);
}

void LogDebug(const char * strFormat, ...)
{
    std::string strExtendContent = MakeExtendContent();

    char logBuffer[MAX_BUFFER];
    va_list args;
    va_start(args, strFormat);
    vsnprintf(logBuffer, MAX_BUFFER, strFormat, args);
    va_end(args);

    std::string strLog = strExtendContent + std::string(logBuffer) + "\n";
    m_oLog.MarkDebugLog(strLog);
}

void ExtLogError(const std::string &strFullFileName, 
        const std::string &strFunction,
        const uint32_t dwLineNo,
        const char * strFormat, 
        ...)
{
    std::string strExtendContent = MakeExtendContent(strFullFileName, strFunction, dwLineNo);

    char logBuffer[MAX_BUFFER];
    va_list args;
    va_start(args, strFormat);
    vsnprintf(logBuffer, MAX_BUFFER, strFormat, args);
    va_end(args);

    std::string strLog = strExtendContent + std::string(logBuffer) + "\n";
    m_oLog.MarkErrorLog(strLog);
}

void LogError(const char * strFormat, ...)
{
    std::string strExtendContent = MakeExtendContent();

    char logBuffer[MAX_BUFFER];
    va_list args;
    va_start(args, strFormat);
    vsnprintf(logBuffer, MAX_BUFFER, strFormat, args);
    va_end(args);

    std::string strLog = strExtendContent + std::string(logBuffer) + "\n";
    m_oLog.MarkErrorLog(strLog);
}

void ExtLogKey(const std::string &strFullFileName, 
        const std::string &strFunction,
        const uint32_t dwLineNo,
        const char * strFormat, 
        ...)
{
    std::string strExtendContent = MakeExtendContent(strFullFileName, strFunction, dwLineNo);

    char logBuffer[MAX_BUFFER];
    va_list args;
    va_start(args, strFormat);
    vsnprintf(logBuffer, MAX_BUFFER, strFormat, args);
    va_end(args);

    std::string strLog = strExtendContent + std::string(logBuffer) + "\n";
    m_oLog.MarkKeyLog(strLog);
}

void LogKey(const char * strFormat, ...)
{
    std::string strExtendContent = MakeExtendContent();

    char logBuffer[MAX_BUFFER];
    va_list args;
    va_start(args, strFormat);
    vsnprintf(logBuffer, MAX_BUFFER, strFormat, args);
    va_end(args);

    std::string strLog = strExtendContent + std::string(logBuffer) + "\n";
    m_oLog.MarkKeyLog(strLog);
}
}
