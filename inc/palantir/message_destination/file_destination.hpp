#pragma once

#include <fstream>

#include "palantir/message_destination/message_destination_abstract.hpp"

namespace palantir {

/**
 * @class FileDestination
 * 
 * @brief Implements message output functionality to a file.
 *
 * FileDestination is a concrete implementation of the MessageDestinationAbstract that writes
 * messages to a specified file. This class manages the file opening, writing, and closing
 * operations, ensuring that all messages are persisted to the file system.
 */
class FileDestination : public MessageDestinationAbstract {
public:
    /**
     * @brief Constructs a FileDestination object associated with a specific file.
     *
     * This constructor opens a file stream to the specified file name. If the file
     * cannot be opened or created, it throws an std::runtime_error.
     *
     * @param file_name The name of the file to write messages to.
     */
    explicit FileDestination(const std::string& file_name);
    
    ~FileDestination() override;

    /**
     * @brief Sends a message to the associated file.
     *
     * Writes the given message to the file specified during construction.
     * If the file stream is not open or encounters an error, it throws an std::runtime_error.
     *
     * @param message The string message to be written to the file.
     */
    void send_message(const std::string& message) override;

private:
    /**
     * @brief The name of the file where messages will be written.
     * 
     */
    std::string file_name_;

    /**
     * @brief File stream used for writing messages to the file.
     * 
     */
    std::ofstream file_stream_;
};

}       //  namespace palantir

