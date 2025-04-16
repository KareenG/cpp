#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

#include "lc3/consts_and_sizes.hpp"

namespace lc3
{

/**
 * @brief Simulates the LC-3 memory space (65,536 16-bit words).
 *
 * Provides dense memory storage and access mechanisms for reading and writing values,
 * as well as support for loading a program starting at a specific address.
 */
class Memory {
public:
    /**
     * @brief Constructs a new memory instance.
     * 
     * @param start The program start address (default 0x3000).
     */
    explicit Memory(Address start = 0x3000);

    Memory(Memory const&) = delete;
    Memory(Memory&&) = delete;
    Memory& operator=(Memory const&) = delete;
    Memory& operator=(Memory&&) = delete;

    ~Memory() noexcept = default;

    /**
     * @brief Loads a vector of instruction words into memory at a given starting address.
     *
     * @param data The program data to load (moved in).
     * @param start_addr The address at which to begin loading.
     *
     * @throws MemoryBoundsException if the program does not fit.
     */
    void load_dense(std::vector<Word>&& data, Address start_addr);

    /**
     * @brief Gets the address where the program was loaded.
     * 
     * @return Address Program start address.
     */
    Address get_program_start() const noexcept;

    /**
     * @brief Reads a value from memory.
     * 
     * @param address The address to read from.
     * @return Word The value stored at the address.
     */
    Word read(Address address) const noexcept;

    /**
     * @brief Writes a value to memory.
     * 
     * @param address The address to write to.
     * @param value The 16-bit value to store.
     */
    void write(Address address, Word value) noexcept;

private:
    std::vector<Word> memory_;
    Address start_;
};

} // namespace lc3
