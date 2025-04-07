#include <string>
#include <cctype>  // For isalpha(), isupper()

#include "palantir/encryption/key_base_encryptor.hpp"

namespace palantir {

KeyBaseEncryptor::KeyBaseEncryptor(std::string key)
: key_{key}
, key_index_{}
{
}

std::string KeyBaseEncryptor::encode(std::string const& buffer) {
    //reset_index();
    key_index_ = 0;
    std::string encoded;
    for (char c : buffer) {
        encoded.push_back(encode(c));  // Call the character-specific encode method
    }
    return encoded;
}

std::string KeyBaseEncryptor::decode(std::string const& buffer) {
    //reset_index();
    key_index_ = 0;
    std::string decoded;
    for (char c : buffer) {
        decoded.push_back(decode(c));  // Call the character-specific decode method
    }
    return decoded;
}

char KeyBaseEncryptor::get_key_char_and_inc_index()
{
    if (!key_.empty())
    {
        char c = key_[key_index_];
        key_index_ = (key_index_ + 1) % key_.size();
        return c;
    }
    return '\0';
}


// void KeyBaseEncryptor::set_key_index()
// {

// }


// void KeyBaseEncryptor::reset_index()
// {
//     key_index_ = 0;
// }

// size_t KeyBaseEncryptor::index()
// {
//     return index_;
// }

}
