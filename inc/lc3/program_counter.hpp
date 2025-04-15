#pragma once

#include <cstdint>

namespace lc3
{

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
    explicit ProgramCounter(uint16_t pc = 0x3000) noexcept;

    /**
     * @brief Deleted copy constructor.
     */
    ProgramCounter(ProgramCounter const&) = delete;

    /**
     * @brief Deleted move constructor.
     */
    ProgramCounter(ProgramCounter&&) = delete;

    /**
     * @brief Deleted copy assignment operator.
     */
    ProgramCounter& operator=(ProgramCounter const&) = delete;

    /**
     * @brief Deleted move assignment operator.
     */
    ProgramCounter& operator=(ProgramCounter&&) = delete;

    /**
     * @brief Defaulted destructor.
     */
    ~ProgramCounter() noexcept = default;

    /**
     * @brief Gets the current program counter value.
     * 
     * @return Current PC value.
     */
    uint16_t get() const noexcept;

    /**
     * @brief Sets the program counter to a new address.
     * 
     * @param new_pc The address to set as PC.
     */
    void set(uint16_t new_pc) noexcept;

    /**
     * @brief Increments the program counter by an offset (default 1).
     * 
     * @param offset Value to increment the PC by.
     */
    void increment(uint16_t offset = 1) noexcept;

private:
    uint16_t p_counter_;
};

} // namespace lc3
