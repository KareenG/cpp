#include "palantir/encryption/xor.hpp"

namespace palantir {

XorEncryptor::XorEncryptor(std::string key)
: key_{key}
{
}

std::string XorEncryptor::encode(const std::string& text) const 
{
    if (key_.empty()) {
        return text;
    }
    std::string result = text;
    size_t text_length = text.size();
    size_t key_length = key_.size();
    size_t key_index = 0;

    for (size_t i = 0; i < text_length; ++i) {
        result[i] = text[i] ^ key_[key_index % key_length];
        key_index++;
    }

    return result;
}

std::string XorEncryptor::decode(const std::string& text) const 
{
    return encode(text);
}

}  // namespace palantir
