#include "config.h"

using namespace Common;

Config::Config()
{

}

Config::Config(const std::string &strConfigFile)
    : m_strConfigFileName(strConfigFile)
{
    InitConfigContent();
}

Config::~Config()
{

}

const std::string Config::GetItemContent(const std::string &strParentItem,
        const std::string &strChildItem)
{
    return m_mapConfig[strParentItem][strChildItem];
}

void Config::InitConfigContent()
{
    File oFile(m_strConfigFileName);

    std::string strLineContent = "";
    std::string strTmp = "";
    std::string strParentItem = "";

    while((strTmp = oFile.GetLine()) != "")
    {
        strLineContent = StringUtils::Strip(strTmp);

        if(strLineContent.find("[") != std::string::npos 
           && strLineContent.find("]") != std::string::npos)
        {
            size_t dwBeginIndex = strLineContent.find("[");
            size_t dwEndIndex = strLineContent.find("]");
            strParentItem = strLineContent.substr(dwBeginIndex+1, dwEndIndex-1);

            continue;
        }
        
        if(strParentItem.empty() 
           || strLineContent.find("=") == std::string::npos)
        {
            continue;
        }

        std::vector<std::string> vecChiledItem;
        StringUtils::SplitBySubStr(strLineContent, "=", vecChiledItem);
        
        if(vecChiledItem.size() != 2)
        {
            continue;
        }

        m_mapConfig[strParentItem][vecChiledItem[0]] = vecChiledItem[1];
    }
}
