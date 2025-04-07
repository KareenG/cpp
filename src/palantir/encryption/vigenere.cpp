#include <locale>
#include <cassert>
#include <cctype>
#include <algorithm> // For std::transform

#include "palantir/encryption/vigenere.hpp"

namespace palantir {

Vigenere::Vigenere(std::string key)
//: key_{key}
: KeyBaseEncryptor([key]() {
    std::string lower = key;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
}())
{
}

char Vigenere::encode(char c) 
{
    if (std::isalpha(c)) {
        int key_shift = get_key_char_and_inc_index() - 'a';
        char base = std::isupper(c) ? 'A' : 'a';
        //++key_index_;
        return base + (c - base + key_shift + 26) % 26;
    }
    return c;
}

char Vigenere::decode(char c) 
{
    if (std::isalpha(c)) {
        int key_shift = -(get_key_char_and_inc_index() - 'a'); //key_[key_index_ % key_.size()]
        char base = std::isupper(c) ? 'A' : 'a';
        //++key_index_;
        return base + (26 + c - base + key_shift) % 26;
    }
    return c;
}

}       // namespace palantir
