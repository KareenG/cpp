#pragma once

#include <iostream>
#include <string>
#include "palantir/message_source/message_source_abstract.hpp"

namespace palantir {

/**
 * @class ConsoleInput
 * 
 * @brief Implements message input functionality from a standard input stream.
 *
 * ConsoleInput is a concrete implementation of the MessageSourceAbstract that reads
 * messages from an input stream. By default, it uses std::cin, but it can be configured to
 * use any input stream provided during construction. This flexibility allows the class
 * to be used for standard console input or for redirecting input from other streams like
 * std::ifstream or even std::stringstream for testing purposes.
 */
class ConsoleInput : public MessageSourceAbstract {
public:
    /**
     * @brief Constructs a ConsoleInput object linked to a specific input stream.
     *
     * Initializes the ConsoleInput with a reference to an input stream. The default
     * stream is std::cin, but this can be overridden to accept messages from other streams.
     *
     * @param input Reference to an std::istream object which could be std::cin or any other
     *              input stream. Defaults to std::cin.
     */
    ConsoleInput(std::istream& input = std::cin);

    ~ConsoleInput() override = default;

    /**
     * @brief Retrieves a message from the configured input stream.
     *
     * This method reads a line from the input stream and returns it as a message.
     * It is primarily designed to read from std::cin or similar streams, handling user input
     * from the console or other text sources.
     *
     * @return A string containing the message read from the input stream.
     */
    std::string get_message() override;

    /**
     * @brief Checks if the input source has been fully processed.
     *
     * In the context of ConsoleInput, this method checks if the end of the input stream
     * has been reached, which would indicate no more input is available.
     *
     * @return true if the end of the stream has been reached, false otherwise.
     */
    bool is_fully_processed() const override;

private:
    /**
     * @brief Reference to the input stream from which messages are read.
     * 
     */
    std::istream& input_stream_;
};

} // namespace palantir
