#include "palantir/encryption/null_encryption.hpp"

namespace palantir {
    
char NullEncryption::encode_char(char c) const 
{
    return c;
}

char NullEncryption::decode_char(char c) const 
{
    return c;
}

}       // namespace palantir