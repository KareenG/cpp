#include <string>
#include <cctype>  // For isalpha(), isupper()

#include "palantir/encryption/char_encryption.hpp"

namespace palantir {
   
std::string CharEncryptor::encode(std::string const& buffer) const 
{
    std::string encoded_str;
    for (char c : buffer) {
        encoded_str.push_back(encode_char(c));
    }
    return encoded_str;
}

std::string CharEncryptor::decode(std::string const& buffer) const 
{
    std::string encoded_str;
    for (char c : buffer) {
        encoded_str.push_back(decode_char(c));
    }
    return encoded_str;
}

}
