#pragma once

#include <string>
#include <unordered_map>

#include "palantir/encryption/key_base_encryptor.hpp"

namespace palantir {

/**
 * @class Atbash
 * 
 * @brief Implements the Atbash cipher using character substitution.
 *
 * The Atbash cipher is a particular type of monoalphabetic cipher formed by 
 * taking the alphabet and mapping it to its reverse, so that the first letter 
 * becomes the last letter, the second letter becomes the second to last letter,
 * and so forth. This class provides methods to encode and decode strings using 
 * this cipher method, relying on a lookup table for fast character substitution.
 */
class Atbash : public KeyBaseEncryptor {
public:
    /**
     * @brief Constructs an Atbash cipher object.
     *
     * Initializes the lookup table used for encoding and decoding.
     */
    Atbash() = default;
    
    virtual ~Atbash() override = default;

private:
    /**
     * @brief Encodes a single character using the Atbash cipher.
     * 
     * Looks up the character in the pre-initialized lookup table to get its 
     * corresponding encoded character.
     * 
     * @param c The character to encode.
     * @return The encoded character.
     */
    char encode(char c) override;

    /**
     * @brief Decodes a single character using the Atbash cipher.
     * 
     * Since Atbash is a symmetric cipher, decoding is identical to encoding. 
     * This method simply returns the result of encode_char for the given character.
     * 
     * @param c The character to decode.
     * @return The decoded character.
     */
    char decode(char c) override;
};

}       //  namespace palantir

