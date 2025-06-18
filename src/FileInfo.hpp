#pragma once
#include <filesystem>

struct FileInfo
{
    std::filesystem::path path;
    std::filesystem::file_type type;
    std::filesystem::perms permissions;
    std::filesystem::file_time_type time;
};
