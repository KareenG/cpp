#pragma once

#include <iostream>

#include "bf/mem_arg_types.hpp"

namespace bf
{

/**
 * @brief Handles input and output operations for Brainfuck execution.
 *
 * The Console class is designed to abstract the input and output operations
 * used in the Brainfuck interpreter. It allows reading from and writing to
 * character streams, which can be directed to or from different sources such
 * as standard input/output or file streams.
 * 
 * @details
 * Members:
 * - std::ostream& os_: Output stream used for writing characters. Default is std::cout.
 * - std::istream& is_: Input stream used for reading characters. Default is std::cin.
 */
class Console {
public:
    /**
     * @brief Construct a new Console object.
     * 
     * Initializes the console with output and input streams. Default parameters
     * are standard output (std::cout) and standard input (std::cin).
     * 
     * @param os_ Reference to the output stream.
     * @param is_ Reference to the input stream.
     */
    Console(std::ostream& os = std::cout, std::istream& is = std::cin);

    /**
     * @brief Default copy constructor.
     */
    Console(Console const& other) = default;

    /**
     * @brief Default destructor.
     */
    ~Console() = default;

    /**
     * @brief Default copy assignment operator.
     */
    Console& operator=(Console const& other) = default;

    /**
     * @brief Read a single character from the input stream.
     * 
     * Reads a character from the input stream and returns it as a CellType value.
     * This function is typically used to fetch user input during Brainfuck execution.
     * 
     * @return CellType The character read from the input stream, converted to CellType.
     */
    CellType input_char();

     /**
     * @brief Write a single character to the output stream.
     * 
     * Outputs a character to the configured output stream. The character is provided
     * as a CellType and converted to char before writing.
     * 
     * @param c The character to print, specified as a CellType.
     */
    void print_char(CellType c);

private:
    std::ostream& os_;
    std::istream& is_;
};

} // namespace bf
