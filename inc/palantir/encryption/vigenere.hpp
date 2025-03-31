#pragma once

#include <string>
#include <array>

#include "palantir/encryption/encryption_abstract.hpp"

namespace palantir {

class Vigenere : public EncryptionAbstract {
private:
    std::string key_;

private:
    std::string encode_text(const std::string& text) const;
    std::string decode_text(const std::string& text) const;

public:
    explicit Vigenere(std::string key);
    
    virtual ~Vigenere() override = default;

    virtual std::string encode(std::string const& buffer) const override;
    virtual std::string decode(std::string const& buffer) const override;
};

}       //  namespace palantir

