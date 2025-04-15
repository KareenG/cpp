#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace lc3 {

/**
 * @brief Loads a binary LC-3 program from file into memory format.
 *
 * The Loader is responsible for reading a binary `.bin` LC-3 object file,
 * extracting the origin address, and returning a vector of 16-bit instructions
 * to be loaded into memory.
 *
 * The returned program data is already converted to host byte order.
 */
class Loader {
public:
    /**
     * @brief Loads the binary file and returns a vector of instructions.
     * 
     * The first two bytes of the file are interpreted as the origin address,
     * and the following bytes are read as 16-bit LC-3 instruction words.
     * 
     * @param file_path Path to the binary LC-3 object file.
     * @return std::vector<uint16_t> containing LC-3 instructions.
     * 
     * @note Asserts or throws if the file cannot be opened or read.
     */
    std::vector<uint16_t> load(std::string const& file_path);

    /**
     * @brief Returns the start address extracted from the last loaded program.
     *
     * @return The 16-bit origin address.
     */
    uint16_t get_start_address() const noexcept;

private:
    uint16_t start_address_ = 0x3000;
};

} // namespace lc3
