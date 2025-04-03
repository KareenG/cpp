#include "palantir/encryption/xor.hpp"

namespace palantir {

XorEncryptor::XorEncryptor(std::string key)
: key_{key}
{
}

char XorEncryptor::encode(char c) 
{
    return c ^ key_[key_index_ % key_.size()];
}

char XorEncryptor::decode(char c) 
{
    return c ^ key_[key_index_ % key_.size()];
}

}  // namespace palantir
