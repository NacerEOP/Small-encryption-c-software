#pragma once
#include <string>

class data_write {
private:
    std::string filePath;  // store the path from GUI

public:
    data_write(const std::string& path);
    ~data_write() = default;

    // Write the given text to the stored file (overwrite)
    bool write(const std::string& text);

    // Read the contents of the stored file and return it
    std::string read() const;
};
