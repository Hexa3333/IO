#pragma once
#include <cstdint>

enum struct FileAccess : uint8_t
{
    none       =        0,
    read       =  (1 << 0),
    write      =  (1 << 1),
    binary     =  (1 << 2),
    append     =  (1 << 3),
    truncate   =  (1 << 4),
};

inline FileAccess operator|(FileAccess a, FileAccess b)
{
    return static_cast<FileAccess>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inline FileAccess operator&(FileAccess a, FileAccess b)
{
    return static_cast<FileAccess>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}
