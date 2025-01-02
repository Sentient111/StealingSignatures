// Forced includes
#include <iostream>
#include <string>

// Custom includes
#include "certificate_handler/certificate_handler.h"
#include "file_utils/file_utils.h"
#include "header_parser/header_parser.h"
#include "../ext/logger/logger.h"

int main()
{
    // Get file paths
    std::string signed_path;
    std::string unsigned_path;

    // Prompt the user for the signed file path
    logger::log(logger::info, "Please enter the path to the signed file.");
    std::cout << ": ";
    std::getline(std::cin, signed_path);  // Use getline to handle spaces in paths

    // Prompt the user for the unsigned file path
    logger::log(logger::info, "Please enter the path to the unsigned file.");
    std::cout << "[+]: ";
    std::getline(std::cin, unsigned_path);  // Use getline to handle spaces in paths

    // Call the function to steal the certificate
    bool success = steal_certificate_from_file(signed_path, unsigned_path);
    if (success)
    {
        logger::log(logger::success, "Certificate stolen and added successfully!");
    }
    else
    {
        logger::log(logger::error, "Failed to steal or add the certificate.");
    }

    return 0;
}
