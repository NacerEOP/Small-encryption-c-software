#pragma once
#include <string>

class Chiffrement {
private:
    static const int CESAR_SHIFT = 3; // shift for Caesar cipher
    static const char XOR_KEY = 'K';  // key for XOR cipher

    static std::string caesar(const std::string& text, bool encrypt);
    static std::string xorCipher(const std::string& text);

public:
    Chiffrement() = default;
    ~Chiffrement() = default;

    // Main function: text -> encrypted or decrypted according to mode
    std::string process(const std::string& text, int mode, bool encrypt) const;
};
