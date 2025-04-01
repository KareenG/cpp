#include "palantir/encryption/caesar.hpp"

namespace palantir {

Caesar::Caesar(int shift)
: shift_(shift)
{  
}

char Caesar::shift_char(const char c, int shift) const 
{
    if (std::isalpha(c)) {
        char base = std::isupper(c) ? 'A' : 'a';
        return (base + (c - base + shift + 26) % 26);
    } else {
        return c;
    }
}

char Caesar::encode_char(char c) const 
{
    return shift_char(c, shift_);
}

char Caesar::decode_char(char c) const 
{
    return shift_char(c, -shift_);
}

}       //  namespace palantir
