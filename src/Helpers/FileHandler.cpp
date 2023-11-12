#include "FileHandler.hpp"

#include <fstream>

// Returns a string containing the file contents
std::string get_file_contents(const char* file_name)
{
    // Tries to open the file
    std::ifstream input_file(file_name, std::ios::binary);

    // Checks for errors when opening the file
    if(!input_file)
    {
        throw(errno);
        return NULL;
    }

    // Moves the read position to the end of the file, and resizes the string accordingly
    std::string contents;
    input_file.seekg(0, std::ios::end);
    contents.resize(input_file.tellg());
    // Moves the read position back to the beggining of the file
    input_file.seekg(0, std::ios::beg);

    // Copies the file contents to the string and closes the file
    input_file.read(&contents[0], contents.size());
    input_file.close();

    return contents;
}
