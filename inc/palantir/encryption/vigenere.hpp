#pragma once

#include <string>
#include <array>

#include "palantir/encryption/encryption_abstract.hpp"

namespace palantir {

/**
 * @class Vigenere
 * 
 * @brief Implements the Vigenère cipher for encryption and decryption.
 *
 * The Vigenère cipher is a method of encrypting alphabetic text by using a repeating key,
 * each letter of which specifies the number of positions to shift the corresponding letter
 * of the plaintext. This class provides methods to encode and decode messages using
 * the Vigenère cipher, which is based on the Caesar cipher but uses a series of shifts
 * determined by a keyword.
 */
class Vigenere : public EncryptionAbstract { 
public:
     /**
     * @brief Constructs a Vigenere cipher object with a specific key.
     *
     * This constructor initializes the Vigenere cipher instance with a key that is used
     * for both encoding and decoding operations. The key should not be empty and should
     * contain only alphabetic characters.
     *
     * @param key The keyword used to derive the shifts for the Vigenère cipher.
     */
    explicit Vigenere(std::string key);
    
    virtual ~Vigenere() override = default;

     /**
     * @brief Encodes a string using the Vigenère cipher.
     *
     * Applies the Vigenère cipher to the input buffer using the initialized key,
     * returning the encrypted text. Non-alphabetic characters in the buffer are not
     * altered.
     *
     * @param buffer The string to encode.
     * @return The encoded string.
     */
    virtual std::string encode(std::string const& buffer) const override;

    /**
     * @brief Decodes a string that was encrypted using the Vigenère cipher.
     *
     * Reverses the Vigenère cipher on the input buffer using the same key that was used for
     * encoding, returning the original plaintext. Non-alphabetic characters in the buffer
     * are not altered.
     *
     * @param buffer The string to decode.
     * @return The decoded string.
     */
    virtual std::string decode(std::string const& buffer) const override;

private:
     /**
     * @brief Helper method to encode text using the Vigenère cipher.
     *
     * This method is a utility to handle the encoding process by applying the key
     * to each character in the input text based on the Vigenère algorithm.
     *
     * @param text The plaintext to encode.
     * @return The encoded text.
     */
    std::string encode_text(const std::string& text) const;

    /**
     * @brief Helper method to decode text using the Vigenère cipher.
     *
     * This method is a utility to handle the decoding process by reversing the key
     * application to each character in the input text based on the Vigenère algorithm.
     *
     * @param text The ciphertext to decode.
     * @return The decoded text.
     */
    std::string decode_text(const std::string& text) const;

private:
    /**
     * @brief The keyword used for encoding and decoding.
     * 
     */
    std::string key_;
};

}       //  namespace palantir

