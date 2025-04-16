#pragma once

#include <stdexcept>
#include <string>

namespace lc3 {

/**
 * @brief Exception thrown when a file cannot be opened.
 */
class FileOpenException : public std::runtime_error {
public:
    explicit FileOpenException(const std::string& path);
};

/**
 * @brief Exception thrown when a program does not fit into available memory.
 */
class MemoryBoundsException : public std::runtime_error {
public:
    explicit MemoryBoundsException(std::size_t max_size);
};

/**
 * @brief Exception thrown when an unknown opcode is encountered.
 */
class InvalidOpcodeException : public std::runtime_error {
public:
    explicit InvalidOpcodeException(uint16_t raw_instruction);

private:
    static std::string to_hex(uint16_t inst);
};

} // namespace lc3
