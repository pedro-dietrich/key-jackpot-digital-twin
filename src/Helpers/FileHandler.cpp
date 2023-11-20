#include "FileHandler.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>

// Initializes static variable
std::string FileHandler::rootPath;

// Sets the application's root path from the executable path
void FileHandler::setRootPath(const char* executablePath)
{
    std::filesystem::path path = std::filesystem::path(executablePath).parent_path();
    rootPath = path.string().append("/");
}

// Returns a string with the full file path
std::string FileHandler::getPath(const char* location, const char* fileName)
{
    return rootPath + location + fileName;
}

// Returns a string containing the file contents
std::string FileHandler::getFileContents(const char* location, const char* fileName)
{
    // Sets the path for the file
    std::string filePath = rootPath + location + fileName;

    // Tries to open the file
    std::ifstream inputFile(filePath, std::ios::binary);

    // Checks for errors when opening the file
    if(!inputFile)
    {
        std::cerr << "File " << fileName << " was not found at " << filePath << "." << std::endl;
        throw(errno);
        return NULL;
    }

    // Moves the read position to the end of the file, and resizes the string accordingly
    std::string contents;
    inputFile.seekg(0, std::ios::end);
    contents.resize(inputFile.tellg());
    // Moves the read position back to the beggining of the file
    inputFile.seekg(0, std::ios::beg);

    // Copies the file contents to the string and closes the file
    inputFile.read(&contents[0], contents.size());
    inputFile.close();

    return contents;
}
