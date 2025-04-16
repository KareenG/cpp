#include "lc3/lc3_exceptions.hpp"
#include <cstdio> // for std::snprintf

namespace lc3 {

FileOpenException::FileOpenException(const std::string& path)
    : std::runtime_error("Failed to open file: " + path)
{
}

MemoryBoundsException::MemoryBoundsException(std::size_t max_size)
    : std::runtime_error("Program too large to fit in memory of size " + std::to_string(max_size))
{
}

InvalidOpcodeException::InvalidOpcodeException(uint16_t raw_instruction)
    : std::runtime_error("Unknown opcode: 0x" + to_hex(raw_instruction))
{
}

std::string InvalidOpcodeException::to_hex(uint16_t inst)
{
    char buffer[5]; // 4 hex digits + null terminator
    std::snprintf(buffer, sizeof(buffer), "%04X", inst);
    return std::string(buffer);
}

} // namespace lc3
