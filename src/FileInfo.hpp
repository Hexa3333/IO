#pragma once
#include <filesystem>

// TODO: learn std::filesystem::path

struct FileInfo
{
    std::filesystem::path path;
    std::filesystem::file_type type;
    std::filesystem::perms permissions;
    std::filesystem::file_time_type time;
};
