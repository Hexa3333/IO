#pragma once
#include <cstdint>

enum struct FileMode : uint8_t
{
    none    =        0,
    read    =  (1 << 0),
    write   =  (1 << 1),
    binary  =  (1 << 2),

};

inline FileMode operator|(FileMode a, FileMode b)
{
    return static_cast<FileMode>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inline FileMode operator&(FileMode a, FileMode b)
{
    return static_cast<FileMode>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}
