#pragma once

#include <fstream>
#include <string>

#include "palantir/message_source/message_source_abstract.hpp"

namespace palantir {

/**
 * @class FileSource
 * 
 * @brief Implements message source functionality for reading messages from a file.
 *
 * FileSource is a concrete implementation of the MessageSourceAbstract that reads
 * messages from a specified file. This class manages the file opening, reading, and closing
 * operations, ensuring that messages are read sequentially from the file and indicating when
 * the end of the file is reached.
 */
class FileSource : public MessageSourceAbstract {
public:
    /**
     * @brief Constructs a FileSource object associated with a specific file.
     *
     * This constructor opens a file stream to the specified file name for reading. If the file
     * cannot be opened, it throws an std::runtime_error, ensuring that the object does not
     * exist without a valid file source.
     *
     * @param file_name The name of the file to read messages from.
     */
    explicit FileSource(std::string const& file_name);
    
    ~FileSource() override;

    /**
     * @brief Retrieves the next message from the file.
     *
     * This method reads a line from the file and returns it. It is intended to read messages
     * one at a time from the file, typically one message per line.
     *
     * @return A string containing the next message from the file. If the end of the file is reached,
     * an empty string is returned.
     */
    std::string get_message() override;

    /**
     * @brief Checks if all messages from the file have been read.
     *
     * This method determines if the end of the file has been reached, which is an indication
     * that all messages have been processed.
     *
     * @return true if all messages have been read (i.e., end of file is reached), false otherwise.
     */
    bool is_fully_processed() const override;

private:
    /**
     * @brief The name of the file from which messages are read.
     * 
     */
    std::string file_name_{};

    /**
     * @brief File stream used for reading messages from the file.
     * 
     */
    std::ifstream file_stream_;
};

}       //  namespace palantir

