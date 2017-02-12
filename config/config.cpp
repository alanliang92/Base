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

bool Config::GetItemContent(const std::string &strParentItem,
        const std::string &strChildItem, 
        std::string &strValue)
{
    strValue = m_mapConfig[strParentItem][strChildItem];

    if(!strValue.empty())
    {
        return true;
    }
    
    return false;
}

bool Config::GetItemContent(const std::string &strParentItem,
        const std::string &strChildItem,
        std::string &strValue,
        const std::string &strDefaultValue)
{
    std::string tmpValue = "";
    bool bGetItem = false;

    bGetItem = GetItemContent(strParentItem, strChildItem, tmpValue);
    if(!bGetItem)
    {
        strValue = strDefaultValue;
    }
    else
    {
        strValue = tmpValue;
    }

    return true;
}

bool Config::GetItemContent(const std::string &strParentItem,
        const std::string &strChildItem,
        uint32_t &dwValue)
{
    std::string tmpValue = "";
    bool bGetItem = false;

    bGetItem = GetItemContent(strParentItem, strChildItem, tmpValue);
    if(!bGetItem)
    {
        return false;
    }

    dwValue = atoi(tmpValue.c_str());
    return true;
}

bool Config::GetItemContent(const std::string &strParentItem,
        const std::string &strChildItem,
        uint32_t &dwValue,
        const std::string &strDefaultValue)
{
    std::string tmpValue = "";
    bool bGetItem = false;

    bGetItem = GetItemContent(strParentItem, strChildItem, tmpValue);
    if(!bGetItem)
    {
        dwValue = atoi(strDefaultValue.c_str());
    }
    else{
        dwValue = atoi(tmpValue.c_str());
    }

    return true;
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
