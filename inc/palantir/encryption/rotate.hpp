#pragma once

#include <unordered_map>

#include "palantir/encryption/char_encryption.hpp"

namespace palantir {

/**
 * @class RotateEncryptor
 * 
 * @brief Implements a rotational cipher with a customizable shift.
 *
 * The RotateEncryptor is a character-based encryption class that provides 
 * encoding and decoding functions for rotating characters by a specified number 
 * of positions in the alphabet. The class can be configured with any shift value,
 * allowing for versatile encodings similar to the Caesar cipher but with customizable
 * shifts. This class utilizes modular arithmetic to handle wrapping of characters 
 * at the alphabet boundaries.
 */
class RotateEncryptor : public CharEncryptor {
public:
    /**
     * @brief Constructs a RotateEncryptor with an optional shift value.
     *
     * This constructor initializes the RotateEncryptor instance with a specific shift value,
     * which determines how many positions characters will be shifted during encoding and decoding.
     * The default shift value is 13, which equates to a ROT13 cipher.
     *
     * @param shift The number of positions to shift each character. Default is 13.
     */
    explicit RotateEncryptor(int shift = 13);

protected:
    /**
     * @brief Encodes a single character by rotating it forward in the alphabet.
     * 
     * Shifts a character forward by the configured number of positions, wrapping around 
     * at the end of the alphabet. This function ensures characters remain within their
     * respective case (upper or lower).
     *
     * @param c The character to encode.
     * @return The encoded character.
     */
    virtual char encode_char(char c) const override;

    /**
     * @brief Decodes a single character by rotating it backward in the alphabet.
     * 
     * Shifts a character backward by the configured number of positions, wrapping around 
     * at the start of the alphabet. As with encoding, this function respects character casing.
     *
     * @param c The character to decode.
     * @return The decoded character.
     */
    virtual char decode_char(char c) const override;

private:
    /**
     * @brief The number of alphabet positions by which characters are shifted.
     * 
     */
    int shift_;
};

}  // namespace palantir
