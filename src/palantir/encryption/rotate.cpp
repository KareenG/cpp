#include <string>
#include <cctype>  // For isalpha(), isupper()

#include "palantir/encryption/rotate.hpp"

namespace palantir {
   
std::string RotateCharEncryptor::encode(std::string const& buffer) {
    std::string decoded;
    for (char c : buffer) {
        decoded.push_back(shift_element(c, shift_));
    }
    return decoded;
}

std::string RotateCharEncryptor::decode(std::string const& buffer) {
    std::string decoded;
    for (char c : buffer) {
        decoded.push_back(shift_element(c, -shift_));
    }
    return decoded;
}

void RotateCharEncryptor::set_shift(int shift)
{
    shift_ = shift;
}

char RotateCharEncryptor::shift_element(const char c, int shift) 
{
    if (std::isalpha(c)) {
        char base = std::isupper(c) ? 'A' : 'a';
        return (base + (c - base + shift + 26) % 26);
    } 
    return c;
}

}
