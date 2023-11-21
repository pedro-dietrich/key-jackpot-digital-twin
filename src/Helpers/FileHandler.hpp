#pragma once

#include <string>

class FileHandler
{
    public:
        // Sets the application's root path from the executable path
        static void setRootPath(const char* executablePath);

        // Returns a string with the full file path
        static std::string getPath(const char* location, const char* fileName);
        // Returns a string containing the file contents
        static std::string getFileContents(const char* location, const char* fileName);

        // Path for the executable
        static std::string rootPath;
};
