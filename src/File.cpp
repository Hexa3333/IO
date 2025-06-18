#include "File.hpp"
#include "FileInfo.hpp"
#include <filesystem>
#include <stdexcept>

// TODO: Functions other than the constructor need not necessarily
// handle errors. Maybe this should be a flag also ?

// TODO
File::File()
    : access(FileAccess::none)
{
}

File::File(const std::string& filePath, FileAccess accessMode)
    : access(accessMode)
{
    info.path = filePath;

    // Query the FileInfo (includes permissions)
    FileError queryError = QueryInfo();

    // File does not exist on disk
    if (queryError == FileError::not_found)
    {
        if ((access & FileAccess::read) != FileAccess::none)
            // You cannot read a non-existent file!
            throw std::runtime_error("Attempted to read a non-existent file");

        if ((access & FileAccess::write) != FileAccess::none)
            CreateWritableRegularFile();
    }
    // exists on disk
    else
        HandleError(AccessCheck());
    HandleError(Open(info.path));
}

File::operator bool() const
{
    return stream.is_open();
}

FileError File::ResetAccess(FileAccess flags)
{
    stream.close();

    access = flags;
    FileError errors = AccessCheck();
    HandleError(errors);
    stream.open(info.path, GetFstreamMode());

    return errors;
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

void File::Flush()
{
    stream.flush();
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
    if ((access & FileAccess::append) != FileAccess::none)
        fstreamMode |= std::ios::app;
    if ((access & FileAccess::truncate) != FileAccess::none)
        fstreamMode |= std::ios::trunc;

    return fstreamMode;
}

FileError File::QueryInfo()
{
    if (!CheckExists())
        return FileError::not_found;

    auto status = std::filesystem::status(info.path);
    info.type = status.type();
    info.permissions = status.permissions();
    info.lastWriteTime = std::filesystem::last_write_time(info.path);

    return FileError::none;
}

bool File::CheckExists()
{
    return std::filesystem::exists(info.path);
}

FileError File::AccessCheck() const
{
    using perms = std::filesystem::perms;
    static auto infoPermCheck = [&](perms i, perms f)
    {
        return (i & f) != perms::none;
    };

    FileError errors{};

    if ((access & FileAccess::read) != FileAccess::none &&
        !infoPermCheck(info.permissions, perms::owner_read))
    {
        errors |= FileError::no_read_perm;
    }

    if ((access & FileAccess::write) != FileAccess::none &&
        !infoPermCheck(info.permissions, perms::owner_write))
    {
        errors |= FileError::no_write_perm;
    }

    return errors;
}

void File::CreateWritableRegularFile()
{
    info.type = std::filesystem::file_type::regular;
    info.permissions = std::filesystem::perms::owner_write;
    info.lastWriteTime = std::filesystem::file_time_type::clock::now();

    // Preserve information that this file was CREATED(truncated) during the lifetime of the program
    access = FileAccess::write | FileAccess::truncate;
}

#include <iostream>
// TODO
void File::HandleError(FileError e)
{
    switch (e)
    {
        case FileError::no_read_perm:
        {
            // Handle
            std::cout << "NO READ PERM\n";
            break;
        }

        case FileError::no_write_perm:
        {
            // Handle
            std::cout << "NO WRITE PERM\n";
            break;
        }

        case FileError::not_found:
        {
            std::cout << "NOT FOUND\n";
            break;
        }

        case FileError::none:
        default:
        break;
    }
}

FileError File::operator>>(std::string& outString)
{
    return Read(outString);
}

FileError File::operator<<(const std::string& writeContent)
{
    return Write(writeContent);
}

File::~File()
{
    stream.close();
}
