#pragma once
/*
*/

#include <fstream>
#include "FileMode.hpp"
#include "FileError.hpp"

/*
   Work In Progress.
   [+] Add custom overloads for reading and writing
   [-] Safety. Real safety.

*/
class File
{
public:
    File();
    File(const std::string& fileName, FileMode mode = FileMode::read | FileMode::write);
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

private:
    std::string path;
    std::fstream stream;
    FileMode mode;
};
