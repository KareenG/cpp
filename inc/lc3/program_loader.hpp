#pragma once

#include <vector>
#include <string>

#include "lc3/loader.hpp"
#include "lc3/memory.hpp"

namespace lc3 {

/**
 * @brief Loads an LC-3 binary program and commits it into memory.
 *
 * This class uses a `Loader` to parse a binary file and places the loaded
 * instructions into the `Memory` starting at the origin specified in the binary.
 */
class ProgramLoader {
public:
    /**
     * @brief Constructs a ProgramLoader and immediately loads the given file into memory.
     *
     * @param file_path Path to the LC-3 binary (.bin) file.
     * @param memory Reference to the memory to load the program into.
     * @throws std::runtime_error if the file cannot be read or program is too large.
     */
    explicit ProgramLoader(std::string const& file_path, Memory& memory);

    /**
     * @brief Deleted copy constructor.
     */
    ProgramLoader(ProgramLoader const&) = delete;

    /**
     * @brief Deleted move constructor.
     */
    ProgramLoader(ProgramLoader&&) = delete;

    /**
     * @brief Deleted copy assignment.
     */
    ProgramLoader& operator=(ProgramLoader const&) = delete;

    /**
     * @brief Deleted move assignment.
     */
    ProgramLoader& operator=(ProgramLoader&&) = delete;

    /**
     * @brief Defaulted destructor.
     */
    ~ProgramLoader() noexcept = default;

private:
    Loader loader_;
    Memory& memory_;
};

} // namespace lc3
