#include "palantir/encryption/caesar.hpp"

namespace palantir {

Caesar::Caesar(int shift)
: RotateCharEncryptor(shift)
{  
}

}  





























//: shift_(shift)


//  namespace palantir

// char Caesar::shift_char(const char c, int shift) 
// {
//     if (std::isalpha(c)) {
//         char base = std::isupper(c) ? 'A' : 'a';
//         return (base + (c - base + shift + 26) % 26);
//     } else {
//         return c;
//     }
// }

// char Caesar::encode(char c) 
// {
//     return shift_char(c, shift_);
// }

// char Caesar::decode(char c) 
// {
//     return shift_char(c, -shift_);
// }