#include "header_parser/header_parser.h"
#include <fstream>
#include <Windows.h>

int get_position_of_position(int* size, std::string& path)
{
    // Create buffer for header
    uint8_t headers[0xFFF]; // Size for headers

    // Read header data into buffer
    std::ifstream stream(path, std::ios::binary);
    stream.read(reinterpret_cast<char*>(&headers), sizeof(headers));
    stream.close();

    // Get DOS and NT header
    PIMAGE_DOS_HEADER dos_headers = reinterpret_cast<PIMAGE_DOS_HEADER>(&headers);
    PIMAGE_NT_HEADERS64 nt_header = reinterpret_cast<PIMAGE_NT_HEADERS64>(reinterpret_cast<uintptr_t>(&headers) + dos_headers->e_lfanew);

    // Get end of optional header
    int location = (reinterpret_cast<uintptr_t>(&nt_header->OptionalHeader.DataDirectory) + sizeof(IMAGE_DATA_DIRECTORY)) - reinterpret_cast<uintptr_t>(&headers);

    // Add offset depending on platform
    if (nt_header->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC)
        location += 24;
    else
        location += 8;

    // Both values are DWORDs, so add 4 bytes to skip location and get size
    *size = location + 4;
    return location;
}

DWORD get_position(DWORD* size, std::string& path)
{
    // Create buffer for header
    uint8_t headers[0xFFF];

    // Read header data into buffer
    std::ifstream stream(path, std::ios::binary);
    stream.read(reinterpret_cast<char*>(&headers), sizeof(headers));
    stream.close();

    // Get positions in buffer
    int location_size;
    int location = get_position_of_position(&location_size, path);

    // Interpret the location as DWORD pointer and get the value
    DWORD location_in_file = *(DWORD*)(&headers[location]);
    DWORD size_value = *(DWORD*)(&headers[location_size]);

    *size = size_value;
    return location_in_file;
}
