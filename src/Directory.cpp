#include "Directory.hpp"
#include <filesystem>

Directory::Directory(const std::string& fPath)
{
    for (auto const& entry : std::filesystem::directory_iterator(fPath))
    {
        FileInfo info;
        info.path = entry.path();
        auto status = entry.status();
        info.type = status.type();
        info.permissions = status.permissions();
        info.lastWriteTime = entry.last_write_time();

        fileInfos.push_back(info);
    }
}
