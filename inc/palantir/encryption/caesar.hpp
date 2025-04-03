#pragma once

#include "palantir/encryption/rotate.hpp"

namespace palantir {

/**
 * @class Caesar
 * 
 * @brief Implements the Caesar cipher, a type of substitution cipher in which 
 * each letter in the plaintext is shifted a certain number of places down the alphabet.
 *
 * This class provides methods to encode and decode strings using the Caesar cipher
 * technique, characterized by shifting letters by a predefined number. The class
 * can handle both encoding and decoding, applying the inverse shift for decoding.
 */
class Caesar : public RotateCharEncryptor { //CharEncryptor
public:
    /**
     * @brief Constructs a Caesar cipher object with a specific shift.
     *
     * Initializes a Caesar cipher with the provided shift value, used to encode and decode messages.
     *
     * @param shift The number of positions each character in the text is shifted. 
     *              The default shift value is 3.
     */
    explicit Caesar(int shift = 3);
    
    virtual ~Caesar() override = default;
};

}       //  namespace palantir


























//#include "palantir/encryption/char_encryption.hpp"
//private:
    /**
     * @brief Encodes a single character using the Caesar cipher shift.
     * 
     * Shifts a character forward in the alphabet by the configured shift amount, wrapping around
     * at the end of the alphabet.
     *
     * @param c The character to encode.
     * @return The encoded character.
     */
    //char encode(char c) override;

    /**
     * @brief Decodes a single character that was encoded using the Caesar cipher shift.
     * 
     * Shifts a character backward in the alphabet by the configured shift amount, wrapping around
     * at the start of the alphabet.
     *
     * @param c The character to decode.
     * @return The decoded character.
     */
    //char decode(char c) override;

//private:
    /**
     * @brief Shifts a single character by the specified shift value.
     *
     * This method wraps the character shift operation, taking care of alphabet wrapping
     * and maintaining case sensitivity.
     *
     * @param c The character to shift.
     * @param shift The amount to shift the character.
     * @return The shifted character.
     */
    //char shift_char(const char c, int shift);

// private:
//     int shift_;