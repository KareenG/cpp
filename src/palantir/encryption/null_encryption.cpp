#include "palantir/encryption/null_encryption.hpp"

namespace palantir {
    
char NullEncryption::encode(char c) 
{
    return c;
}

char NullEncryption::decode(char c) 
{
    return c;
}

}       // namespace palantir