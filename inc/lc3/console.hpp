#pragma once

#include <iostream>
#include <string>

#include "lc3/registers.hpp"
#include "lc3/memory.hpp"

namespace lc3 {

/**
 * @brief Handles input and output operations for TRAP instructions.
 *
 * This class abstracts TRAP routines such as GETC, OUT, PUTS, IN, and HALT,
 * interfacing with the provided input/output streams and register file.
 */
class Console {
public:
    /**
     * @brief Constructs a new Console object with the given output/input streams.
     *
     * @param os Output stream (defaults to std::cout).
     * @param is Input stream (defaults to std::cin).
     */
    explicit Console(std::ostream& os = std::cout, std::istream& is = std::cin);

    Console(Console const& other) = default;
    Console& operator=(Console const& other) = default;

    ~Console() noexcept = default;

    /**
     * @brief TRAP x20 - Reads a character from input without echoing it and stores it in R0.
     *
     * Uses low-level unbuffered input to read a single character directly from the terminal.
     *
     * @param reg Reference to the register file.
     */
    void read_char_no_echo(Registers& reg);

    /**
     * @brief TRAP x21 - Outputs the character in R0 to the output stream.
     *
     * Interprets the low byte of R0 as an ASCII character and prints it.
     *
     * @param reg Reference to the register file.
     */
    void write_char(const Registers& reg);

    /**
     * @brief TRAP x22 - Outputs a null-terminated string from memory starting at address in R0.
     *
     * Reads characters from memory one word at a time and prints the lower byte
     * until a null byte is encountered.
     *
     * @param reg Reference to the register file.
     * @param memory Reference to the memory.
     */
    void write_string_from_memory(const Registers& reg, const Memory& memory);

    /**
     * @brief TRAP x23 - Prompts the user and reads one character into R0, echoing it afterward.
     *
     * Displays a prompt, reads one character from input using unbuffered terminal I/O,
     * stores it in R0, and echoes it back to the screen followed by a newline.
     *
     * @param reg Reference to the register file.
     */
    void prompt_and_read_char(Registers& reg);

private:
    std::ostream& os_;
    std::istream& is_;
};

} // namespace lc3
