#ifndef __CONFIG_H
#define __CONFIG_H

#include <stdio.h>
#include <stdint.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <string>
#include <stdlib.h>
#include <map>
#include "string_utils.h"
#include "file.h"

namespace Common
{

class Config
{
    public:
        Config(const std::string &strConfigFile);

        ~Config();

        const std::string GetItemContent(const std::string &strParentItem,
                const std::string &strChildItem);

    private:
        Config();

        void InitConfigContent();
    
    private:
        std::string m_strConfigFileName;
        std::map<std::string, std::map<std::string, std::string> > m_mapConfig;
};

}

#endif
