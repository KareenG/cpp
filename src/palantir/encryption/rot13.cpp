

#include "palantir/encryption/rot13.hpp"

namespace palantir {
Rot13::Rot13()
: lookup_table{initialize_LUT()}
{
}

std::string Rot13::encode(std::string const& buffer) const
{
    std::string encoded_str;
    for(char c : buffer) {
        encoded_str.push_back(lookup_table.at(c));
    }
    return encoded_str;
}

std::string Rot13::decode(std::string const& buffer) const
{
    return encode(buffer);
}

std::unordered_map<u_int8_t, u_int8_t> Rot13::initialize_LUT() 
{
    std::unordered_map<u_int8_t, u_int8_t> t;
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