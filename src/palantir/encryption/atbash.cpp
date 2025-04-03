#include "palantir/encryption/atbash.hpp"

namespace palantir {

char Atbash::encode(char c) 
{
    if (isalpha(c)) {
        if (isupper(c)) {
            return 'Z' - (c - 'A');
        } 
        return 'z' - (c - 'a');
    }
    return c;
}

char Atbash::decode(char c) 
{
    return encode(c);
}

}       // namespace palantir

















// Atbash::Atbash()
// : lookup_table{initialize_LUT()}
// {
// }

// std::unordered_map<char, char> Atbash::initialize_LUT() 
// {
//     std::unordered_map<char, char> t;
//     for (int i = 0; i < 256; ++i) {
//         if (isalpha(i)) {
//             if (isupper(i)) {
//                 t[i] = 'Z' - (i - 'A');
//             } else if (islower(i)) {
//                 t[i] = 'z' - (i - 'a');
//             }
//         } else {
//             t[i] = i;
//         }
//     }
//     return t;
// }