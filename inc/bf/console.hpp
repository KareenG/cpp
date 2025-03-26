#pragma once

#include <iostream>
#include <sstream>
#include <string>

namespace bf {

/**
 * @brief Represents an I/O console.
 *
 * The Console class manages I/O differently depending on its mode:
 * - In Runtime mode, it interfaces with standard I/O streams, providing real-time interaction.
 * - In DEBUG mode, it uses internal string streams to simulate I/O, which is particularly useful for automated testing 
 *   and debugging, as it avoids side effects and allows inspection and manipulation of I/O data.
 *
 * @member mode Mode The operational mode of the console, which determines how I/O is handled.
 * @member test_output_buffer std::ostringstream An output buffer used in DEBUG mode to capture output data for testing.
 * @member test_input_buffer std::istringstream An input buffer used in DEBUG mode to supply predefined input data for tests.
 */
class Console {
public:
    /**
     * @brief Enum to distinguish between operational modes of the Console.
     */
    enum class Mode {
        Runtime,
        DEBUG
    };
    /**
     * @brief Constructs a Console with optional mode settings and initial test data.
     *
     * @param mode The mode in which the console operates, default is Runtime.
     * @param testData Initial data to load into the input buffer in DEBUG mode.
     */
    explicit Console(Mode mode = Mode::Runtime, const std::string& test_data = "");

    /**
     * @brief Copy constructor.
     *
     * Creates a new console by copying the state of another console, including the contents
     * of its input and output buffers.
     *
     * @param other The console to copy.
     */
    Console(const Console& other);

    /**
     * @brief Sets new test data for the console's input buffer when in DEBUG mode.
     *
     * This method only affects the console if it is in DEBUG mode. It resets the input buffer
     * with new test data provided.
     *
     * @param test_data The new test data to load into the input buffer.
     */
    void set_test_data(const std::string& test_data);

    /**
     * @brief Writes a character based on the console's current mode.
     *
     * In Runtime mode, outputs directly to std::cout. In DEBUG mode, writes to an internal test output buffer.
     *
     * @param c The character to output, represented as an int.
     */
    void write(int c);

    /**
     * @brief Reads a character based on the console's current mode.
     *
     * In Runtime mode, reads from std::cin. In DEBUG mode, reads from an internal test input buffer.
     * This method handles EOF by clearing EOF flags to allow further read operations.
     *
     * @return The character read, returned as an unsigned char.
     */
    unsigned char read();

    /**
     * @brief Retrieves the contents of the test output buffer.
     *
     * This method is useful in DEBUG mode to inspect what has been written to the output buffer.
     *
     * @return A string containing the contents of the test output buffer.
     */
    std::string get_test_output() const;

    /**
     * @brief Clears the contents of the test output buffer.
     *
     * This method is used in DEBUG mode to reset the output buffer, typically between tests.
     */
    void clear_test_output();

private:
    Mode mode;
    std::ostringstream test_output_buffer;
    std::istringstream test_input_buffer;
};

}