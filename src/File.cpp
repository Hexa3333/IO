#include "File.hpp"

File::File()
    : access(FileAccess::none)
{
}

File::File(const std::string& filePath, FileAccess accessMode)
    : path(filePath), access(accessMode)
{
    Open(path);
}

File::operator bool() const
{
    return stream.is_open();
}

FileError File::Open(const std::string& filePath)
{
    path = filePath;
    stream.open(path, GetFstreamMode());
    if (!stream.is_open())
    {
        throw std::runtime_error("File: \"" + path + "\" could not be opened");
    }

    return FileError::none;
}

FileError File::Read(std::string& outContent)
{
    if ((access & FileAccess::read) == FileAccess::none)
    {
        return FileError::no_read_perm;
    }

    stream.seekg(0, std::ios::end);
    size_t size = stream.tellg();
    stream.seekg(0);

    outContent.resize(size+1);
    stream.read(&outContent[0], size);
    outContent[size] = 0;

    return FileError::none;
}

std::ios::openmode File::GetFstreamMode()
{
    std::ios::openmode fstreamMode{};

    if ((access & FileAccess::read) != FileAccess::none)
        fstreamMode |= std::ios::in;
    if ((access & FileAccess::write) != FileAccess::none)
        fstreamMode |= std::ios::out;
    if ((access & FileAccess::binary) != FileAccess::none)
        fstreamMode |= std::ios::binary;

    return fstreamMode;
}

void File::QueryInfo()
{
}

File::~File()
{
    stream.close();
}
