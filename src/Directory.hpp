// TODO



#pragma once

#include "FileInfo.hpp"
#include <vector>

class Directory
{
public:
    Directory(const std::string& fPath);

private:
    std::vector<FileInfo> fileInfos;
};
