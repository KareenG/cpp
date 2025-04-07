#include "palantir/encryption/xor.hpp"

namespace palantir {

XorEncryptor::XorEncryptor(std::string key)
//: key_{key}
: KeyBaseEncryptor(key)
{
}

char XorEncryptor::encode(char c) 
{
    return c ^ get_key_char_and_inc_index();
}

char XorEncryptor::decode(char c) 
{
    return c ^ get_key_char_and_inc_index();
}

}  // namespace palantir
