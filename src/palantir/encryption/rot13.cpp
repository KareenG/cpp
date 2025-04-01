#include "palantir/encryption/rot13.hpp"

namespace palantir {

Rot13::Rot13()
: lookup_table{initialize_LUT()}
{
}

char Rot13::encode_char(char c) const 
{
    return lookup_table.at(c);
}

char Rot13::decode_char(char c) const 
{
    return encode_char(c);
}

std::unordered_map<char, char> Rot13::initialize_LUT() 
{
    std::unordered_map<char, char> t;
    for (int i = 0; i < 256; ++i) {
        if (isalpha(i)) {
            if (isupper(i)) {
                t[i] = 'A' + (i - 'A' + 13) % 26;
            } else if (islower(i)) {
                t[i] = 'a' + (i - 'a' + 13) % 26;
            }
        } else {
            t[i] = i;
        }
    }
    return t;
}

}       // namespace palantir