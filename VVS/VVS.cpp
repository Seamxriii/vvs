
#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

int main() {
    std::string path_to_directory;

    std::cout << "Enter the path to the directory: ";
    std::getline(std::cin, path_to_directory);  // 

    fs::path dir_path(path_to_directory);
    if (!fs::exists(dir_path)) {
        std::cerr << "Error: Directory does not exist." << std::endl;
        return 1;
    }

    if (!fs::is_directory(dir_path)) {
        std::cerr << "Error: The path provided is not a directory." << std::endl;
        return 1;
    }


    int file_count = 0;
    try {
        for (const auto& entry : fs::recursive_directory_iterator(dir_path)) {
            if (fs::is_regular_file(entry)) {
                file_count++;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Total number of files in the directory: " << file_count << std::endl;

    return 0;
}