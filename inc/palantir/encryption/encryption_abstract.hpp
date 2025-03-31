#pragma once

#include <string>
#include <vector>

namespace palantir {

class EncryptionAbstract {
public:
    EncryptionAbstract() = default;
    
    virtual ~EncryptionAbstract() = default;

    virtual std::string encode(std::string const& buffer) const = 0;
    virtual std::string decode(std::string const& buffer) const = 0;

protected:
    EncryptionAbstract(EncryptionAbstract const& other) = default;

    EncryptionAbstract& operator=(EncryptionAbstract const& other) = default;
};

}       //  namespace palantir

