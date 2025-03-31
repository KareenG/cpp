#include <codecvt>
#include <locale>

#include "palantir/encryption/atbash.hpp"

namespace palantir {

std::string Atbash::encode(std::string const& buffer) const
{
    std::string encoded_str;
    for(char c : buffer) {
        if(isalpha(c)) {
            if(isupper(c)) {
                encoded_str.push_back('Z' - (c - 'A'));
            } else {
                encoded_str.push_back('z' - (c - 'a'));
            }
        } else {
            encoded_str.push_back(c);
        }
    }
    return encoded_str;
}

std::string Atbash::decode(std::string const& buffer) const
{
    return encode(buffer);
}

}       // namespace palantir