#include <cctype>

#include "palantir/encryption/caesar.hpp"

namespace palantir {

Caesar::Caesar(int shift)
: shift_(shift)
{  
}

std::string Caesar::encode(std::string const& buffer) const
{
    return shift_text(buffer, shift_);
}

std::string Caesar::decode(std::string const& buffer) const
{
    return shift_text(buffer, -shift_);
}

std::string Caesar::shift_text(const std::string& text, int shift) const 
{
    std::string result;
    for (char c : text) {
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            result += (base + (c - base + shift + 26) % 26);
        } else {
            result += c;
        }
    }
    return result;
}

}       //  namespace palantir
    