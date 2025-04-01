#pragma once

#include <string>
#include <unordered_map>

#include "palantir/encryption/char_encryption.hpp"

namespace palantir {

/**
 * @class Rot13
 * 
 * @brief Implements the ROT13 encryption algorithm.
 *
 * ROT13 ("rotate by 13 places") is a simple letter substitution cipher that replaces a letter
 * with the 13th letter after it in the alphabet. ROT13 is a special case of the Caesar cipher,
 * developed in ancient Rome. Since the cipher operates by using rotations, encoding and decoding
 * are performed by the same operation.
 */
class Rot13 : public CharEncryptor {
public:
    /**
     * @brief Constructs a Rot13 cipher object.
     *
     * This constructor initializes the Rot13 cipher instance by setting up a lookup table
     * for quick character transformation.
     */
    Rot13();
    
    virtual ~Rot13() override = default;

protected:
    /**
     * @brief Encodes a single character using the ROT13 cipher.
     * 
     * This method looks up the character in the pre-initialized lookup table to perform
     * the ROT13 transformation, which is symmetric for encoding and decoding.
     *
     * @param c The character to encode.
     * @return The encoded character, which is the same as the decoded character in ROT13.
     */
    virtual char encode_char(char c) const override;

    /**
     * @brief Decodes a single character using the ROT13 cipher.
     * 
     * Decoding for ROT13 is the same as encoding. This method simply returns the result of 
     * encode_char for the given character.
     *
     * @param c The character to decode.
     * @return The decoded character.
     */
    virtual char decode_char(char c) const override;

private:
    /**
     * @brief Initializes the lookup table for the ROT13 cipher.
     *
     * Constructs the mapping for each character to its counterpart 13 characters away
     * in the alphabet.
     * 
     * @return An unordered map with character mappings for the ROT13 cipher.
     */
    std::unordered_map<char, char> initialize_LUT();

private:
    /**
     * @brief Lookup table for quick ROT13 transformation.
     * 
     */
    std::unordered_map<char, char> const lookup_table;
};

}       //  namespace palantir

