#pragma once

#include "palantir/encryption/char_encryption.hpp"

namespace palantir {

/**
 * @brief Implements XOR-based encryption and decryption.
 * 
 * The `XorEncryptor` class provides a simple implementation of XOR encryption, which is
 * a symmetric key encryption algorithm where the plaintext is XORed with a key.
 * If the key is shorter than the plaintext, it will repeat. This class demonstrates
 * basic usage and should not be used for secure communications as it is vulnerable to
 * various cryptographic attacks unless used under specific conditions (like a one-time pad).
 * 
 * Usage example:
 * ```
 * XorEncryptor encryptor("mysecretkey");
 * std::string encrypted = encryptor.encode("Hello World");
 * std::string decrypted = encryptor.decode(encrypted);
 * assert(decrypted == "Hello World");
 * ```
 */
class XorEncryptor : public EncryptionAbstract {
public:
    /**
     * @brief Constructs a new Xor Encryptor object with the given key.
     * 
     * @param key The encryption key as a std::string. The key should not be empty
     * and, for more effective encryption, should be as long as the plaintext.
     */
    explicit XorEncryptor(std::string key);

    virtual ~XorEncryptor() override = default;

    /**
     * @brief Encrypts the given text using the XOR cipher algorithm.
     * 
     * This method applies the XOR operation between the text and the key. If the
     * key is shorter than the text, the key repeats. Each character of the text
     * is XORed with a corresponding character from the key.
     * 
     * @param text The plaintext string to be encrypted.
     * @return std::string The encrypted text.
     */
    virtual std::string encode(const std::string& text) const override;

    /**
     * @brief Decrypts the given text using the XOR cipher algorithm.
     * 
     * Since XOR encryption is symmetric, the decode function is identical to the encode function.
     * The method re-applies the XOR operation to the encrypted text with the same key.
     * 
     * @param text The encrypted string to be decrypted.
     * @return std::string The decrypted text.
     */
    virtual std::string decode(const std::string& text) const override;

private:
    /**
     * @brief The key used for XOR encryption.
     * 
     */
    std::string key_;
};

}  // namespace palantir
