#pragma once

#include <string>
#include <unordered_map>

#include "palantir/encryption/encryption_abstract.hpp"

namespace palantir {

class Rot13 : public EncryptionAbstract {
private:
    std::unordered_map<u_int8_t, u_int8_t> const lookup_table;

private:
    std::unordered_map<u_int8_t, u_int8_t> initialize_LUT();

public:
    Rot13();
    
    virtual ~Rot13() override = default;

    virtual std::string encode(std::string const& buffer) const override;
    virtual std::string decode(std::string const& buffer) const override;
};

}       //  namespace palantir

