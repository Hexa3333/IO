#pragma once

#include "FileAccess.hpp"
#include <cstdint>

enum struct FileError : uint8_t
{
    none,
    not_found,
    no_read_perm,
    no_write_perm,
};

inline FileError operator|(FileError a, FileError b)
{
    return static_cast<FileError>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inline FileError operator|=(FileError& a, FileError b)
{
    a = operator|(a, b);
    return a;
}

inline FileError operator&(FileError a, FileError b)
{
    return static_cast<FileError>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}
