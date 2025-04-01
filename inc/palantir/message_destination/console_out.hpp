#pragma once

#include <iostream>
#include <string>
#include "palantir/message_destination/message_destination_abstract.hpp"

namespace palantir {

/**
 * @class ConsoleOutput
 * 
 * @brief Implements message output functionality to a standard output stream.
 *
 * ConsoleOutput is a concrete implementation of the MessageDestinationAbstract that directs
 * messages to an output stream. By default, it uses std::cout, but it can be configured to
 * use any output stream provided during construction. This flexibility allows the class
 * to be used for standard console output or for redirecting output to other streams like
 * std::ofstream or even std::stringstream for testing purposes.
 */
class ConsoleOutput : public MessageDestinationAbstract {
public:
    /**
     * @brief Constructs a ConsoleOutput object linked to a specific output stream.
     *
     * Initializes the ConsoleOutput with a reference to an output stream. The default
     * stream is std::cout, but this can be overridden to direct messages to other streams.
     *
     * @param output Reference to an std::ostream object which could be std::cout or any other
     *               output stream. Defaults to std::cout.
     */
    ConsoleOutput(std::ostream& output = std::cout);
    virtual ~ConsoleOutput() override = default;

    /**
     * @brief Sends a message to the designated output stream.
     *
     * Takes a string message and outputs it to the output stream initialized with the object.
     * This method ensures that any message handled by the ConsoleOutput object is made visible
     * on the configured output destination.
     *
     * @param message The string message to be sent to the output stream.
     */
    virtual void send_message(const std::string& message) override;

private:
    /**
     * @brief Reference to the output stream where messages are written.
     * 
     */
    std::ostream& output_stream_;
};

} // namespace palantir
