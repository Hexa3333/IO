#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>

#include "File.hpp"

// Custom stuff
struct vec2
{
    int x, y;
};

// Friend operator overload examples:

// Format: v.x,v.y
FileError operator>>(File& f, vec2& v)
{
    std::string content;
    FileError retCond = f.Read(content);
    if (retCond != FileError::none)
    {
        throw std::runtime_error("oopsie");
    }

    size_t commaIndex = content.find(",");

    v.x = std::stoi(content.substr(0, commaIndex));
    v.y = std::stoi(content.substr(commaIndex+1, content.size()+1));

    return retCond;
}

#if 0
FileError operator<<(File f, const vec2& v)
{
    return f.Write("{ " + std::to_string(v.x) + ", " + std::to_string(v.y) + " }");
}
#endif


int main(void)
{
    File fileIn("./file", FileAccess::read);
    std::string contents;
    if (fileIn.Read(contents) != FileError::none)
    {
        throw std::runtime_error("uh oh");
    }

    std::cout << "Read:\n" << contents << "\n";

    File vectorized("./vectorized");
    vec2 v;
    vectorized >> v;
    std::cout << v.x << ", " << v.y << "\n";

    File out("./out", FileAccess::write);
    std::string outMessage = "Save the world.\nTruthnuke.\nOver...";
    out.Write(outMessage);
}
