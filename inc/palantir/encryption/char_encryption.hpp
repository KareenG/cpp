#pragma once

#include <string>

#include "palantir/encryption/encryption_abstract.hpp"

namespace palantir {

/**
 * @class CharEncryptor
 * 
 * @brief Abstract base class for character-based encryption algorithms.
 *
 * This class extends the EncryptionAbstract to provide a framework for
 * encoding and decoding strings on a character-by-character basis. It 
 * defines additional pure virtual functions for encoding and decoding 
 * individual characters, which must be implemented by derived classes.
 */
class CharEncryptor : public EncryptionAbstract {
public:
    virtual ~CharEncryptor() = default;

    /**
     * @brief Encode a string using the implemented character-based encryption algorithm.
     * 
     * This function iterates over each character in the provided string,
     * applies the encode_char method, and returns the fully encoded string.
     * 
     * @param buffer The string to encode.
     * @return The encoded string.
     */
    virtual std::string encode(std::string const& buffer) const override;

    /**
     * @brief Decode a string using the implemented character-based encryption algorithm.
     * 
     * This function iterates over each character in the provided string,
     * applies the decode_char method, and returns the fully decoded string.
     * 
     * @param buffer The string to decode.
     * @return The decoded string.
     */
    virtual std::string decode(std::string const& buffer) const override;
    
protected:
    /**
     * @brief Encode a single character.
     * 
     * Must be implemented by derived classes to define how individual characters
     * are encoded.
     * 
     * @param c The character to encode.
     * @return The encoded character.
     */
    virtual char encode_char(char c) const = 0;
    
    /**
     * @brief Decode a single character.
     * 
     * Must be implemented by derived classes to define how individual characters
     * are decoded.
     * 
     * @param c The character to decode.
     * @return The decoded character.
     */
    virtual char decode_char(char c) const = 0;
};

}
