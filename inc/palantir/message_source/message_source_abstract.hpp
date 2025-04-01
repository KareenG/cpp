#pragma once

#include <string>

namespace palantir {

/**
 * @class MessageSourceAbstract
 * 
 * @brief Abstract base class for message source implementations.
 *
 * This class defines a common interface for all message source classes, which are responsible
 * for providing messages from various sources such as files, network streams, or standard input.
 * It enforces the implementation of methods to retrieve messages and to check if the source has
 * been fully processed.
 */
class MessageSourceAbstract {
public:
    MessageSourceAbstract() = default;
    
    virtual ~MessageSourceAbstract() = default;

    /**
     * @brief Retrieves a message from the source.
     *
     * This pure virtual function must be implemented by all concrete subclasses to handle
     * the specifics of retrieving messages from the source, depending on the nature of the source
     * (e.g., reading from a file, receiving from a network connection).
     *
     * @return A string representing the message retrieved from the source.
     */
    virtual std::string get_message() = 0;

    /**
     * @brief Checks if the message source has been fully processed.
     *
     * This pure virtual function should be implemented to indicate whether all messages from the
     * source have been retrieved. It's useful for determining when to stop reading from the source.
     *
     * @return true if all messages have been processed, false otherwise.
     */
    virtual bool is_fully_processed() const = 0;

protected:
    /**
     * @brief Copy constructor.
     * 
     * Protected copy constructor to prevent copying of instances but allow derived classes
     * to handle copying if necessary.
     */
    MessageSourceAbstract(MessageSourceAbstract const& other) = default;
    
    /**
     * @brief Copy assignment operator.
     *
     * Protected copy assignment operator to prevent assigning of instances but allow derived
     * classes to handle assignment if necessary.
     *
     * @return Reference to the current instance of the class.
     */
    MessageSourceAbstract& operator=(MessageSourceAbstract const& other) = default;
};

}       //  namespace palantir

