#include "string_utils.h"

using namespace Common;

StringUtils::StringUtils()
{

}

StringUtils::~StringUtils()
{

}

void StringUtils::SplitBySeparator(const std::string &strContext,
        const char cSeparator,
        std::vector<std::string> &vecSplitResult)
{
    std::string strTmp = strContext;
    std::size_t dwSeparatorIndex = 0;

    for(; dwSeparatorIndex != std::string::npos; )
    {
        dwSeparatorIndex = strTmp.find(cSeparator);

        if(dwSeparatorIndex != std::string::npos)
        {
            std::string strItem = strTmp.substr(0, dwSeparatorIndex);
            if(!strItem.empty())
            {
                vecSplitResult.push_back(Strip(strItem));
            }
            if(dwSeparatorIndex + 1 < strTmp.size())
            {
                strTmp = strTmp.substr(dwSeparatorIndex+1);
            }
            else
            {
                break;
            }
        }
        else
        {
            vecSplitResult.push_back(Strip(strTmp));
        }
    }

}

void StringUtils::SplitBySeparator(const char* strContext,
        const char cSeparator,
        std::vector<std::string> &vecSplitResult)
{
    std::string strTmp = std::string(strContext);
    SplitBySeparator(strTmp, cSeparator, vecSplitResult);
}

void StringUtils::SplitBySubStr(const std::string &strContext,
        const std::string &strSubStr,
        std::vector<std::string> &vecSplitResult)
{
    std::string strTmp = strContext;
    std::size_t dwSeparatorIndex = 0;
    std::size_t dwSubStrSize = strSubStr.size();

    for(; dwSeparatorIndex != std::string::npos; )
    {
        dwSeparatorIndex = strTmp.find(strSubStr);

        if(dwSeparatorIndex != std::string::npos)
        {
            std::string strItem = strTmp.substr(0, dwSeparatorIndex);

            if(!strItem.empty())
            {
                vecSplitResult.push_back(Strip(strItem));
            }

            if(dwSeparatorIndex + dwSubStrSize < strTmp.size())
            {
                strTmp = strTmp.substr(dwSeparatorIndex + dwSubStrSize);
            }
            else
            {
                break;
            }
        }
        else
        {
            vecSplitResult.push_back(Strip(strTmp));
        }
    }
}

const std::string StringUtils::Strip(const std::string &strContext,
        const char cStripChar)
{
    std::string strResult = strContext;
    
    size_t dwHeadBeg = strResult.find_first_of(cStripChar);
    size_t dwHeadEnd = strResult.find_first_not_of(cStripChar);

    if(dwHeadBeg == 0)
    {
        strResult = strResult.erase(dwHeadBeg, dwHeadEnd);
    }
    else
    {
        strResult = strContext;
    }

    if(!strResult.empty())
    {
        size_t dwTailBeg = strResult.find_last_not_of(cStripChar);
        size_t dwTailEnd = strResult.find_last_of(cStripChar);

        if(dwTailEnd == strResult.size()-1)
        {
            strResult = strResult.erase(dwTailBeg+1, strResult.size());
        }
    }

    return strResult;
}
