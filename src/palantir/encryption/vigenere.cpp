#include <locale>
#include <cassert>
#include <cctype>
#include <algorithm> // For std::transform

#include "palantir/encryption/vigenere.hpp"

namespace palantir {

Vigenere::Vigenere(std::string key)
: key_(std::move(key)) 
{
    std::transform(key_.begin(), key_.end(), key_.begin(), [](unsigned char c) { 
        return std::tolower(c); 
    });
}

std::string Vigenere::encode(std::string const& buffer) const 
{
    return encode_text(buffer);
}

std::string Vigenere::decode(std::string const& buffer) const 
{
    return decode_text(buffer);
}

std::string Vigenere::encode_text(const std::string& text) const {
    std::string result = text;
    size_t text_length = text.size();
    size_t key_length = key_.size();
    size_t key_index = 0;

    for (size_t i = 0; i < text_length; ++i) {
        char c = text[i];
        if (std::isalpha(c)) {
            int key_shift = key_[key_index % key_length] - 'a';
            char base = std::isupper(c) ? 'A' : 'a';

            result[i] = base + (c - base + key_shift + 26) % 26;

            key_index++;
        }
    }
    return result;
}

std::string Vigenere::decode_text(const std::string& text) const {
    std::string result = text;
    size_t text_length = text.size();
    size_t key_length = key_.size();
    size_t key_index = 0;

    for (size_t i = 0; i < text_length; ++i) {
        char c = text[i];
        if (std::isalpha(c)) {
            int key_shift = -(key_[key_index % key_length] - 'a');
            char base = std::isupper(c) ? 'A' : 'a';

            result[i] = base + (26 + c - base + key_shift) % 26;

            key_index++;
        }
    }
    return result;
}

}       // namespace palantir