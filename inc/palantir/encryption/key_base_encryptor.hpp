#pragma once

#include <string>
#include "palantir/encryption/encryption_abstract.hpp"

namespace palantir {

/**
 * @class KeyBaseEncryptor
 * 
 * @brief Abstract base class for character-based encryption algorithms.
 *
 * This class extends EncryptionAbstract to provide a framework for
 * encoding and decoding strings on a character-by-character basis. It 
 * defines pure virtual functions for encoding and decoding individual 
 * characters, which must be implemented by derived classes.
 */
class KeyBaseEncryptor : public EncryptionAbstract {
public:
    /**
     * Constructor for KeyBaseEncryptor.
     * Optionally initializes the encryption key.
     * 
     * @param key The encryption key as a string.
     */
    explicit KeyBaseEncryptor(std::string key = {});

    /**
     * Default virtual destructor.
     */
    virtual ~KeyBaseEncryptor() = default;

    /**
     * Encode a string using the implemented character-based encryption algorithm.
     * 
     * Iterates over each character in the string, applies the encode method to each character,
     * and constructs the encoded string.
     * 
     * @param buffer The string to encode.
     * @return The encoded string.
     */
    std::string encode(const std::string& buffer) override;

    /**
     * Decode a string using the implemented character-based encryption algorithm.
     * 
     * Iterates over each character in the string, applies the decode method to each character,
     * and constructs the decoded string.
     * 
     * @param buffer The string to decode.
     * @return The decoded string.
     */
    std::string decode(const std::string& buffer) override;

protected:
    /**
     * Encode a single character using the derived class's encryption algorithm.
     * 
     * Must be implemented by derived classes to define how individual characters
     * are encoded.
     * 
     * @param c The character to encode.
     * @return The encoded character.
     */
    virtual char encode(char c) = 0;
    
    /**
     * Decode a single character using the derived class's decryption algorithm.
     * 
     * Must be implemented by derived classes to define how individual characters
     * are decoded.
     * 
     * @param c The character to decode.
     * @return The decoded character.
     */
    virtual char decode(char c) = 0;

    /**
     * Retrieves the current character from the encryption key and increments the index.
     * If the end of the key is reached, the index wraps around to the beginning.
     *
     * @return The current key character.
     */
    char get_key_char_and_inc_index();

private:
    std::string key_;
    size_t key_index_ = 0;
};

}
