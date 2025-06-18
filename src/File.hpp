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
   [-] Safety. Real safety.

*/

class File
{
public:
    File();
    File(const std::string& fileName, FileAccess mode = FileAccess::read | FileAccess::write);
    operator bool() const;

    FileError Open(const std::string& filePath);

    FileError Read(std::string& outContent);
    FileError Write(const std::string& writeContent);

    template <typename T>
    friend FileError operator>>(File& f, T& outContent);

    template <typename T>
    friend FileError operator<<(File f, const T& writeContent);

    ~File();
private:
    std::ios::openmode GetFstreamMode();
    void QueryInfo();

private:
    FileInfo info;
    std::string path;
    std::fstream stream;
    FileAccess access;
};
