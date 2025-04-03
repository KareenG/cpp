#pragma once

#include <string>

#include "palantir/encryption/encryption_abstract.hpp"

namespace palantir {

/**
 * @class RotateCharEncryptor
 * 
 * @brief Implements a character rotation-based encryption (Caesar cipher).
 *
 * This class provides methods to encode and decode strings using a rotation-based cipher,
 * where each character in the string is shifted by a set number of places down the alphabet.
 * The class maintains case sensitivity and wraps within the alphabet (A-Z, a-z).
 */
class RotateCharEncryptor : public EncryptionAbstract {
public:
    virtual ~RotateCharEncryptor() = default;

    /**
     * @brief Encodes a plaintext string into a ciphertext using character rotation.
     *
     * @param buffer The plaintext string to encode.
     * @return The encoded ciphertext string.
     */
    std::string encode(std::string const& buffer) override;

    /**
     * @brief Decodes a ciphertext string back into plaintext using the inverse of the
     *        character rotation used in encoding.
     *
     * @param buffer The ciphertext string to decode.
     * @return The decoded plaintext string.
     */
    std::string decode(std::string const& buffer) override;

protected:
    /**
     * @brief Sets the character shift used for encoding and decoding.
     *
     * @param shift The number of positions each character is shifted in the cipher.
     */
    void set_shift(int shift);

private:
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
    char shift_element(const char c, int shift);

private:
    /**
     * @brief The shift amount used for encoding and decoding.
     * 
     */
    int shift_ = 0;
};

}       // namespace palantir
