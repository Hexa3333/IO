#pragma once

#include <cstdint>

enum struct FileError : uint8_t
{
    none              =       0,
    not_found         = (1 << 0),
    no_read_perm      = (1 << 1),
    no_write_perm     = (1 << 2),
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

inline FileError operator&=(FileError& a, FileError b)
{
    a = operator&(a, b);
    return a;
}
