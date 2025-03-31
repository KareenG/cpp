#pragma once

#include <string>

#include "palantir/encryption/encryption_abstract.hpp"

namespace palantir {

class NullEncryption : public EncryptionAbstract {
public:
    NullEncryption() = default;
    
    virtual ~NullEncryption() override = default;

    virtual std::string encode(std::string const& buffer) const override;
    virtual std::string decode(std::string const& buffer) const override;
};

}       //  namespace palantir

