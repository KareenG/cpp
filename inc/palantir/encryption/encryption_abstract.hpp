#pragma once

#include <string>

namespace palantir {

/**
 * @class EncryptionAbstract
 * 
 * @brief Abstract base class for encryption algorithms.
 *
 * This class provides the interface for encoding and decoding strings,
 * which must be implemented by derived classes to handle specific
 * encryption algorithms.
 */
class EncryptionAbstract {
public:
    EncryptionAbstract() = default;
    
    virtual ~EncryptionAbstract() = default;

    /**
     * @brief Encode a string using the implemented encryption algorithm.
     * 
     * @param buffer The string to encode.
     * @return The encoded string.
     */
    virtual std::string encode(std::string const& buffer) const = 0;

    /**
     * @brief Decode a string using the implemented encryption algorithm.
     * 
     * @param buffer The string to decode.
     * @return The decoded string.
     */
    virtual std::string decode(std::string const& buffer) const = 0;

protected:
    /**
     * @brief Copy constructor.
     * 
     * @param other The object to copy from.
     */
    EncryptionAbstract(EncryptionAbstract const& other) = default;

    /**
     * @brief Copy assignment operator.
     * 
     * @param other The object to assign from.
     * @return A reference to this instance.
     */
    EncryptionAbstract& operator=(EncryptionAbstract const& other) = default;
};

}       //  namespace palantir

