#pragma once

#include <string>
#include <vector>
#include <cstdint>

#include "lc3/consts_and_sizes.hpp"

namespace lc3 {

/**
 * @brief Loads a binary LC-3 program from file into memory format.
 *
 * The Loader reads a `.bin` LC-3 object file, extracts the origin address,
 * and returns a vector of LC-3 instructions (Words) ready to be loaded into memory.
 */
class Loader {
public:
    /**
     * @brief Loads the binary file and returns the instruction vector.
     * 
     * The first two bytes of the file represent the origin address; the remainder
     * are interpreted as 16-bit instructions in big-endian format.
     * 
     * @param file_path Path to the LC-3 binary file.
     * @return A vector of LC-3 Words (instructions).
     *
     * @throws FileOpenException if the file cannot be opened.
     */
    std::vector<Word> load(std::string const& file_path);

    /**
     * @brief Returns the start address extracted from the last loaded program.
     *
     * @return The 16-bit origin address.
     */
    Address get_start_address() const noexcept;

private:
    Address start_address_ = 0x3000;
};

} // namespace lc3
