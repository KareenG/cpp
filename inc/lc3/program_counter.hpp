#pragma once

#include "lc3/consts_and_sizes.hpp"

namespace lc3 {

/**
 * @brief Represents the LC-3 program counter.
 *
 * Maintains and updates the current instruction address during execution.
 */
class ProgramCounter {
public:
    /**
     * @brief Constructs a new ProgramCounter with an optional start value.
     * 
     * @param pc Initial program counter value (default is 0x3000).
     */
    explicit ProgramCounter(Address pc = 0x3000) noexcept;

    ProgramCounter(ProgramCounter const&) = delete;
    ProgramCounter(ProgramCounter&&) = delete;
    ProgramCounter& operator=(ProgramCounter const&) = delete;
    ProgramCounter& operator=(ProgramCounter&&) = delete;
    
    ~ProgramCounter() noexcept = default;

    /**
     * @brief Gets the current program counter value.
     * 
     * @return Address Current PC value.
     */
    Address get() const noexcept;

    /**
     * @brief Sets the program counter to a new address.
     * 
     * @param new_pc The address to set as PC.
     */
    void set(Address new_pc) noexcept;

    /**
     * @brief Increments the program counter by an offset (default 1).
     * 
     * @param offset Value to increment the PC by.
     */
    void increment(Address offset = 1) noexcept;

private:
    Address p_counter_;
};

} // namespace lc3
