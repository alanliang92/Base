#ifndef _STRING_UTILS_H
#define _STRING_UTILS_H

#include <vector>
#include <string>

namespace Common
{

//字符串操作类
class StringUtils
{
    public:
        StringUtils();

        ~StringUtils();

    public:
        //通过分隔符划分字符串
        static void SplitBySeparator(const std::string &strContext,
                const char cSeparator,
                std::vector<std::string> &vecSplitResult);

        static void SplitBySeparator(const char* strContext,
                const char cSeparator,
                std::vector<std::string> &vecSplitResult);

        //通过子串划分字符串
        static void SplitBySubStr(const std::string &strContext,
                const std::string &strSubStr,
                std::vector<std::string> &vecSplitResult);

        //删除字符串前后指定字符，默认空格
        static const std::string Strip(const std::string &strContext,
                const char cStripChar = ' ');

    private:
        
};

}

#endif
