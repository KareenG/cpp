#pragma once

#include <string>

#include "palantir/encryption/key_base_encryptor.hpp"

namespace palantir {

/**
 * @class NullEncryption
 * 
 * @brief A no-operation encryption class that implements the CharEncryptor interface.
 *
 * This class provides a null implementation of the CharEncryptor, meaning that
 * it performs no actual encryption or decryption. The encode and decode functions
 * simply return the input character unchanged. This can be useful in contexts where 
 * optional encryption is needed, and sometimes no encryption should be applied.
 */
class NullEncryption : public KeyBaseEncryptor {
public:
    NullEncryption() = default;
    
    virtual ~NullEncryption() override = default;

private:
    /**
     * @brief Encodes a character by returning it unchanged.
     *
     * @param c The character to encode.
     * @return The unchanged character.
     */
    char encode(char c) override;

    /**
     * @brief Decodes a character by returning it unchanged.
     *
     * @param c The character to decode.
     * @return The unchanged character.
     */
    char decode(char c) override;

};

}       //  namespace palantir

