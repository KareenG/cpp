#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace lc3
{

static const size_t MEMORY_SIZE = 65'536; // 1 << 16

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
    explicit Memory(uint16_t start = 0x3000);

    /**
     * @brief Deleted copy constructor.
     */
    Memory(Memory const&) = delete;

    /**
     * @brief Deleted move constructor.
     */
    Memory(Memory&&) = delete;

    /**
     * @brief Deleted copy assignment operator.
     */
    Memory& operator=(Memory const&) = delete;

    /**
     * @brief Deleted move assignment operator.
     */
    Memory& operator=(Memory&&) = delete;

    /**
     * @brief Defaulted destructor.
     */
    ~Memory() noexcept = default;

    /**
     * @brief Loads a vector of instruction words into memory at a given starting address.
     *
     * @param data The program data to load (moved in).
     * @param start_addr The address at which to begin loading.
     * 
     * @note Asserts that the program fits in available memory.
     */
    void load_dense(std::vector<uint16_t>&& data, uint16_t start_addr);

    /**
     * @brief Gets the address where the program was loaded.
     * 
     * @return uint16_t Program start address.
     */
    uint16_t get_program_start() const noexcept;

    /**
     * @brief Reads a value from memory.
     * 
     * @param address The address to read from.
     * @return uint16_t The value stored at the address.
     */
    uint16_t read(uint16_t address) const noexcept;

    /**
     * @brief Writes a value to memory.
     * 
     * @param address The address to write to.
     * @param value The 16-bit value to store.
     */
    void write(uint16_t address, uint16_t value) noexcept;

private:
    std::vector<uint16_t> memory_;
    uint16_t start_;
};

} // namespace lc3
