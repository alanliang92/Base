#include "file.h"
#include "string.h"

using namespace Common;

File::File()
{
    
}

File::File(const std::string &strFileName)
{
    m_strFileName = strFileName;    

    int iFileFlag = O_RDONLY;
    m_iFileFd = open(m_strFileName.c_str(), iFileFlag);

    if(m_iFileFd == -1)
    {
        printf("File[%s] open fail!\n", m_strFileName.c_str());
        m_bFileCanRead = false;
    }
    else
    {
        m_bFileCanRead = true;
    }
}

File::~File()
{
    close(m_iFileFd);
}

const std::string File::GetLine()
{
    if(m_bFileCanRead == false)
    {
        if(m_strCurrContent.empty())
        {
            return "";
        }

        return DealLine(); 
    }

    while(m_strCurrContent.empty()
       || m_strCurrContent.find("\n") == std::string::npos)
    {
        char *content = (char *)malloc(MAX_READ_NUM+1);
        ssize_t dwReadSize = read(m_iFileFd, content, MAX_READ_NUM); 

        if(dwReadSize == -1)
        {
            free(content);
            m_bFileCanRead = false;
            printf("Read Error!\n");
            return "";
        }

        if(dwReadSize != MAX_READ_NUM)
        {
            m_bFileCanRead = false;
        }

        content[dwReadSize] = '\0';

        std::string strAppendContent = content;

        //printf("Read result:%s\n", strAppendContent.c_str());

        if(!strAppendContent.empty())
        {
            m_strCurrContent += strAppendContent;
        }

        free(content);

        //printf("After read current content:%s\n", m_strCurrContent.c_str());
    }

    return DealLine();
}

const std::string File::DealLine()
{
    std::string strLineContent = "";
    size_t dwIndex = m_strCurrContent.find("\n");
    
    if(dwIndex != std::string::npos)
    {
        //printf("index: %lu\n", dwIndex);
        strLineContent = m_strCurrContent.substr(0, dwIndex);
        m_strCurrContent = m_strCurrContent.substr(dwIndex+1);
    }

    //printf("CurrContent:%s\n", m_strCurrContent.c_str());
    return strLineContent;
}
