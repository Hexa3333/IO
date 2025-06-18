#include "File.hpp"
#include <filesystem>

File::File()
    : access(FileAccess::none)
{
}

File::File(const std::string& filePath, FileAccess accessMode)
    : access(accessMode)
{
    info.path = filePath;
    QueryInfo();
    Open(info.path);
}

File::operator bool() const
{
    return stream.is_open();
}

FileError File::Open(const std::string& filePath)
{
    info.path = filePath;
    stream.open(info.path, GetFstreamMode());
    if (!stream.is_open())
    {
        throw std::runtime_error("File: \"" + std::string(info.path) + "\" could not be opened");
    }

    return FileError::none;
}

FileError File::Read(std::string& outContent)
{
    // TODO: Access checks handle it
    if ((access & FileAccess::read) == FileAccess::none)
    {
        return FileError::no_read_perm;
    }

    // TODO: Error handling
    stream.seekg(0, std::ios::end);
    size_t size = stream.tellg();
    stream.seekg(0);

    outContent.resize(size+1);
    stream.read(&outContent[0], size);
    outContent[size] = 0;

    return FileError::none;
}

FileError File::Write(const std::string& writeContent)
{
    // TODO: Access checks handle it
    if ((access & FileAccess::write) == FileAccess::none)
    {
        return FileError::no_write_perm;
    }

    // TODO: Error handling
    stream.write(writeContent.data(), writeContent.size());

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

FileError File::QueryInfo()
{
    if (!std::filesystem::exists(info.path))
        return FileError::not_found;

    auto status = std::filesystem::status(info.path);
    info.type = status.type();
    info.permissions = status.permissions();
    info.lastWriteTime = std::filesystem::last_write_time(info.path);

    return FileError::none;
}

// TODO
FileError File::AccessCheck()
{
    return FileError::none;
}

File::~File()
{
    stream.close();
}
