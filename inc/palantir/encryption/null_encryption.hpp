#pragma once

#include <string>

#include "palantir/encryption/char_encryption.hpp"

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
class NullEncryption : public CharEncryptor {
public:
    NullEncryption() = default;
    
    virtual ~NullEncryption() override = default;

    /**
     * @brief Encodes a character by returning it unchanged.
     *
     * @param c The character to encode.
     * @return The unchanged character.
     */
    virtual char encode_char(char c) const override;

    /**
     * @brief Decodes a character by returning it unchanged.
     *
     * @param c The character to decode.
     * @return The unchanged character.
     */
    virtual char decode_char(char c) const override;
};

}       //  namespace palantir

