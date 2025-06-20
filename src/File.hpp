#pragma once
/*
   
*/


#include <fstream>
#include "FileAccess.hpp"
#include "FileError.hpp"
#include "FileInfo.hpp"

/*
   Work In Progress.
   [+] Add custom overloads for reading and writing
   [+] Access safety
   [+] Reset Access

   [-] Operations (move, copy)
   [-] Operations on the file system
*/

class File
{
public:
    File();
    File(const std::string& fileName, FileAccess mode = FileAccess::read | FileAccess::write);
    operator bool() const;

    FileError ResetAccess(FileAccess flags);
    FileError Open(const std::string& filePath);

    FileError Read(std::string& outContent);
    FileError Write(const std::string& writeContent);

    void Flush();

    bool CheckExists() const;
    bool CanRead() const;
    bool CanWrite() const;

    static void HandleError(FileError e);

    template <typename T>
    friend FileError operator>>(File& f, T& outContent);
    FileError operator>>(std::string& outString);

    template <typename T>
    friend FileError operator<<(File& f, const T& writeContent);
    FileError operator<<(const std::string& writeContent);

    ~File();
private:
    std::ios::openmode GetFstreamMode();
    [[nodiscard("Should not be ignored")]]
    FileError QueryInfo();
    FileError AccessCheck() const;
    void CreateWritableRegularFile();

private:
    std::fstream stream;

    FileInfo info;
    FileAccess access;
};
