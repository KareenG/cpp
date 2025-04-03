#include <string>
#include <cctype>  // For isalpha(), isupper()

#include "palantir/encryption/char_encryption.hpp"

namespace palantir {
   
std::string CharEncryptor::encode(std::string const& buffer) {
    reset_index();
    //key_index_ = 0;
    std::string encoded;
    for (char c : buffer) {
        encoded.push_back(encode(c));  // Call the character-specific encode method
    }
    return encoded;
}

std::string CharEncryptor::decode(std::string const& buffer) {
    reset_index();
    //key_index_ = 0;
    std::string decoded;
    for (char c : buffer) {
        decoded.push_back(decode(c));  // Call the character-specific decode method
    }
    return decoded;
}

// void CharEncryptor::set_key_index()
// {

// }


void CharEncryptor::reset_index()
{
    key_index_ = 0;
}

// size_t CharEncryptor::index()
// {
//     return index_;
// }

}
