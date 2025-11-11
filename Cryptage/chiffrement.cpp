#include "chiffrement.h"
#include <iostream>


std::string Chiffrement::caesar(const std::string& text, bool encrypt) {
    std::string result = text;
    int shift = encrypt ? CESAR_SHIFT : -CESAR_SHIFT;
    for (char& c : result) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            c = static_cast<char>( ( (c - base + shift + 26) % 26 ) + base );
        }
    }
    return result;
}

std::string Chiffrement::xorCipher(const std::string& text) {
    std::string result = text;
    for (char& c : result) {
        c ^= XOR_KEY;
    }
    return result;
}

std::string Chiffrement::process(const std::string& text, int mode, bool encrypt) const {
    std::string result = text;

    switch (mode) {
    case 1: // César
        result = caesar(result, encrypt);
        break;
    case 2: // XOR
        result = xorCipher(result);
        break;
    case 3: // Both: César then XOR if encrypt, XOR then César if decrypt
        if (encrypt) {
            result = caesar(result, true);
            result = xorCipher(result);
        } else {
            result = xorCipher(result);
            result = caesar(result, false);
        }
        break;
    default:
        break; // if invalid mode, return unchanged
    }

    return result;
}
