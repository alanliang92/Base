#ifndef _FILE_UTILS_H
#define _FILE_UTILS_H

#include <stdio.h>
#include <stdint.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <string>
#include <stdlib.h>

#define MAX_READ_NUM 10

namespace Common
{

class File
{
    public:
        File(const std::string &strFileName);

        ~File();

        const std::string GetLine();

    private:
        File();

        const std::string DealLine();

    private:
        std::string m_strFileName;
        std::string m_strCurrContent;
        int m_iFileFd;  
        bool m_bFileCanRead;
};

}

#endif
