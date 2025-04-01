#pragma once

#include <string>

namespace palantir {

/**
 * @class MessageDestinationAbstract
 * 
 * @brief Abstract base class for message destination implementations.
 *
 * This class defines a common interface for all message destination classes, which are responsible
 * for handling the output of messages. It enforces the implementation of a method to send messages,
 * ensuring that all concrete subclasses provide their specific handling mechanism for message delivery.
 */
class MessageDestinationAbstract {
public:
    MessageDestinationAbstract() = default;

    virtual ~MessageDestinationAbstract() = default;

    /**
     * @brief Sends a message to the designated destination.
     *
     * This pure virtual function must be implemented by all concrete subclasses to handle
     * the specifics of message delivery, depending on the destination's nature (e.g., to a file,
     * over a network, or to a console).
     *
     * @param mes The message to be sent, passed as a constant reference to a string.
     */
    virtual void send_message(std::string const& mes) = 0;

protected:
    /**
     * @brief Copy constructor.
     * 
     * Protected copy constructor to prevent copying of instances but allow derived classes
     * to handle copying if necessary.
     */
    MessageDestinationAbstract(MessageDestinationAbstract const& other) = default;

    /**
     * @brief Copy assignment operator.
     *
     * Protected copy assignment operator to prevent assigning of instances but allow derived
     * classes to handle assignment if necessary.
     *
     * @return Reference to the current instance of the class.
     */
    MessageDestinationAbstract& operator=(MessageDestinationAbstract const& other) = default;
};

}       //  namespace palantir

