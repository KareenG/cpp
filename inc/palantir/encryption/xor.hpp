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
class XorEncryptor : public CharEncryptor {
public:
    /**
     * @brief Constructs a new Xor Encryptor object with the given key.
     * 
     * @param key The encryption key as a std::string. The key should not be empty
     * and, for more effective encryption, should be as long as the plaintext.
     */
    explicit XorEncryptor(std::string key);

    virtual ~XorEncryptor() override = default;

private:
    char encode(char c) override;
    char decode(char c) override;

private:
    /**
     * @brief The key used for XOR encryption.
     * 
     */
    std::string key_;
};

}  // namespace palantir
