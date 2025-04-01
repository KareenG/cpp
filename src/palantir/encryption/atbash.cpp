#include "palantir/encryption/atbash.hpp"

namespace palantir {

Atbash::Atbash()
: lookup_table{initialize_LUT()}
{
}

char Atbash::encode_char(char c) const 
{
    return lookup_table.at(c);
}

char Atbash::decode_char(char c) const 
{
    return encode_char(c);
}

std::unordered_map<char, char> Atbash::initialize_LUT() 
{
    std::unordered_map<char, char> t;
    for (int i = 0; i < 256; ++i) {
        if (isalpha(i)) {
            if (isupper(i)) {
                t[i] = 'Z' - (i - 'A');
            } else if (islower(i)) {
                t[i] = 'z' - (i - 'a');
            }
        } else {
            t[i] = i;
        }
    }
    return t;
}

}       // namespace palantir