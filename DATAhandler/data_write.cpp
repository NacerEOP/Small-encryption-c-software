#include "data_write.h"
#include <fstream>
#include <sstream>
#include <iostream>

data_write::data_write(const std::string& path) : filePath(path) { }

bool data_write::write(const std::string& text) {
    std::ofstream outFile(filePath, std::ios::trunc); // overwrite
    if (!outFile) {
        std::cerr << "Failed to open file for writing: " << filePath << std::endl;
        return false;
    }
    outFile << text;
    outFile.close();
    return true;
}

std::string data_write::read() const {
    std::ifstream inFile(filePath);
    if (!inFile) {
        std::cerr << "Failed to open file for reading: " << filePath << std::endl;
        return "";
    }
    std::ostringstream ss;
    ss << inFile.rdbuf();
    inFile.close();
    return ss.str();
}
