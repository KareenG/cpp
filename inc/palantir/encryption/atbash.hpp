#pragma once

#include <string>
#include <unordered_map>

#include "palantir/encryption/char_encryption.hpp"

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
class Atbash : public CharEncryptor {
public:
    /**
     * @brief Constructs an Atbash cipher object.
     *
     * Initializes the lookup table used for encoding and decoding.
     */
    Atbash();
    
    virtual ~Atbash() override = default;

protected:
    /**
     * @brief Encodes a single character using the Atbash cipher.
     * 
     * Looks up the character in the pre-initialized lookup table to get its 
     * corresponding encoded character.
     * 
     * @param c The character to encode.
     * @return The encoded character.
     */
    virtual char encode_char(char c) const override;

    /**
     * @brief Decodes a single character using the Atbash cipher.
     * 
     * Since Atbash is a symmetric cipher, decoding is identical to encoding. 
     * This method simply returns the result of encode_char for the given character.
     * 
     * @param c The character to decode.
     * @return The decoded character.
     */
    virtual char decode_char(char c) const override;

private:
    /**
     * @brief Initializes the lookup table for the Atbash cipher.
     * 
     * This method constructs the mapping of each character to its reverse in the 
     * alphabet to facilitate quick encoding and decoding operations.
     * 
     * @return An unordered map with character mappings for the Atbash cipher.
     */
    std::unordered_map<char, char> initialize_LUT();

private:
    /**
     * @brief The lookup table for character substitution.
     * 
     */
    std::unordered_map<char, char> const lookup_table;
};

}       //  namespace palantir

