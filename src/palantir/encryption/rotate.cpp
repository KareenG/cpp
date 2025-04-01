#include "palantir/encryption/rotate.hpp"

namespace palantir {

RotateEncryptor::RotateEncryptor(int shift)
: shift_(shift % 26) 
{ 
}

char RotateEncryptor::encode_char(char c) const 
{
    if (isalpha(c)) {
        char base = isupper(c) ? 'A' : 'a';
        return base + (c - base + shift_) % 26;
    }
    return c;
}

char RotateEncryptor::decode_char(char c) const 
{
    if (isalpha(c)) {
        char base = isupper(c) ? 'A' : 'a';
        return base + (c - base - shift_ + 26) % 26;
    }
    return c;
}

}  // namespace palantir
