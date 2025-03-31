

#include "palantir/encryption/null_encryption.hpp"

namespace palantir {

// Rot13::~Rot13()
// {

// }

std::string NullEncryption::encode(std::string const& buffer) const
{
    return buffer;
}

std::string NullEncryption::decode(std::string const& buffer) const
{
    return buffer;
}


}       // namespace palantir