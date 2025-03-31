#pragma once

#include <string>

#include "palantir/encryption/encryption_abstract.hpp"

namespace palantir {

class Caesar : public EncryptionAbstract {
private:
    int shift_;

private:
    std::string shift_text(const std::string& text, int shift) const;

public:
    explicit Caesar(int shift = 3);
    
    virtual ~Caesar() override = default;

    virtual std::string encode(std::string const& buffer) const override;
    virtual std::string decode(std::string const& buffer) const override;
};

}       //  namespace palantir

