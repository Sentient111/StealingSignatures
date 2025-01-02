#include "certificate_handler/certificate_handler.h"
#include "file_utils/file_utils.h"
#include "header_parser/header_parser.h"
#include "../ext/logger/logger.h"
#include <vector>
#include <fstream>
#include <windows.h>

bool steal_certificate_from_file(std::string& signed_path, std::string& unsigned_path)
{
    // Get location and size of certificate from target program
    DWORD certificate_size;
    DWORD certificate_location = get_position(&certificate_size, signed_path);

    // Error check
    if (certificate_size == 0x0 || certificate_location == 0x0)
    {
        logger::log(logger::error, "Target file is not signed.");
        return false;
    }

    logger::log(logger::info, "Found certificate at position: 0x%p", certificate_location);
    logger::log(logger::info, "Certificate size : %d bytes", certificate_size);

    // Copy certificate into buffer
    std::vector<char> cert(certificate_size);
    std::ifstream target_file_input(signed_path, std::ios::binary);
    target_file_input.seekg(certificate_location);
    target_file_input.read(cert.data(), certificate_size);
    target_file_input.close();

    logger::log(logger::info, "Copied certificate");

    // Create copy of program to add certificate to
    std::string new_file_path = create_copy(unsigned_path);
    logger::log(logger::info, "Created copy of file to add certificate");

    // Get positions to write cert position and size to
    int index_size;
    int index_position = get_position_of_position(&index_size, unsigned_path);

    // Load whole file into buffer and edit there
    std::ifstream new_file_in(new_file_path, std::ios::binary);
    new_file_in.seekg(0, std::ios::end);
    int file_size = new_file_in.tellg();
    new_file_in.seekg(0, std::ios::beg);
    std::vector<char> file_content(file_size);
    new_file_in.read(file_content.data(), file_size);
    new_file_in.close();

    // Overwrite position and size
    std::ofstream new_file_off(new_file_path, std::ios::binary);
    DWORD created_cert_location = file_size;
    DWORD created_cert_size = certificate_size;

    logger::log(logger::info, "Overwriting values in add file");
    *(DWORD*)&file_content[index_position] = created_cert_location;
    *(DWORD*)&file_content[index_size] = created_cert_size;

    // Write buffer back to file
    new_file_off.write(file_content.data(), file_size);
    new_file_off.close();

    // Append the certificate to the new file
    logger::log(logger::info, "Done overwriting location and size");
    std::ofstream coutfile(new_file_path, std::ios::binary | std::ios::app);
    coutfile.write(cert.data(), certificate_size);
    coutfile.close();

    logger::log(logger::info, "Added certificate in new file at : 0x%p with size : %d", created_cert_location, certificate_size);
    logger::log(logger::success, "SUCCESS");

    Sleep(5000);
    return true;
}
