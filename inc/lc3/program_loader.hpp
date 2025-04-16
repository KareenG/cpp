#pragma once

#include <string>
#include <vector>

#include "lc3/loader.hpp"
#include "lc3/memory.hpp"

namespace lc3 {

namespace program_loader {

/**
 * @brief Loads an LC-3 binary file into memory at the address specified in the file.
 *
 * This function uses the Loader to read a `.bin` file, then stores the decoded LC-3 instructions
 * into the provided memory starting from the program's origin address.
 *
 * @param file_path Path to the LC-3 binary file.
 * @param memory Reference to the memory instance to load data into.
 *
 * @throws FileOpenException if the file cannot be opened.
 * @throws MemoryBoundsException if the program does not fit in memory.
 */
void program_loader(const std::string& file_path, Memory& memory);

} // namespace program_loader

} // namespace lc3
