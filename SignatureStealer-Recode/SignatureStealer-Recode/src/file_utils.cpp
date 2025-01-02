#include "file_utils/file_utils.h"
#include "../ext/logger/logger.h"
#include <fstream>
#include <vector>

std::string create_copy(std::string& path)
{
    // New file name
    std::string new_path = path + ".signed";

    // Open input and output streams
    std::ofstream new_file(new_path, std::ios::binary);
    std::ifstream base_file(path, std::ios::binary);

    // Error checks
    if (!new_file.is_open())
    {
        logger::log(logger::error, "Could not open new_file stream");
        return "";
    }

    if (!base_file.is_open())
    {
        logger::log(logger::error, "Could not open base_file stream");
        return "";
    }

    // Get file size
    base_file.seekg(0, std::ios::end);
    int file_size = base_file.tellg();
    base_file.seekg(0, std::ios::beg);

    // Create buffer for file size and copy into it
    std::vector<char> content(file_size);
    base_file.read(content.data(), file_size);

    // Copy buffer to new file
    new_file.write(content.data(), file_size);

    return new_path;
}
