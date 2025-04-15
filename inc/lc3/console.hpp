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
 *
 * @details
 * Members:
 * - std::ostream& os_: Output stream (default: std::cout).
 * - std::istream& is_: Input stream (default: std::cin).
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

    /**
     * @brief Default copy constructor.
     */
    Console(Console const& other) = default;

    /**
     * @brief Default copy assignment.
     */
    Console& operator=(Console const& other) = default;

    /**
     * @brief Default destructor.
     */
    ~Console() noexcept = default;

    /**
     * @brief TRAP x20 - Reads a character from input (no echo) and stores it in R0.
     *
     * @param reg Reference to the register file.
     * @note Asserts that input is available. Clears newlines.
     */
    void get_c(Registers& reg);

    /**
     * @brief TRAP x21 - Outputs the character in R0 to the output stream.
     *
     * @param reg Reference to the register file.
     * @note Asserts that R0 contains a valid ASCII character.
     */
    void out(const Registers& reg);

    /**
     * @brief TRAP x22 - Outputs null-terminated string from memory at address in R0.
     *
     * @param reg Reference to the register file.
     * @param memory Reference to the memory.
     * @note Asserts that memory contains a valid null-terminated ASCII string.
     */
    void put_s(const Registers& reg, const Memory& memory);

    /**
     * @brief TRAP x23 - Prompts user, reads one character into R0, and echoes it.
     *
     * @param reg Reference to the register file.
     * @note Asserts that input is available.
     */
    void in(Registers& reg);

private:
    std::ostream& os_;
    std::istream& is_;
};

} // namespace lc3
