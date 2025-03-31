#pragma once

#include <string>

#include "palantir/encryption/encryption_abstract.hpp"

namespace palantir {

class Atbash : public EncryptionAbstract {
public:
    Atbash() = default;
    
    virtual ~Atbash() override = default;

    virtual std::string encode(std::string const& buffer) const override;
    virtual std::string decode(std::string const& buffer) const override;
};

}       //  namespace palantir

