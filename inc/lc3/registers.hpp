#pragma once

#include <array>

#include "lc3/consts_and_sizes.hpp"

namespace lc3 {

/**
 * @brief Represents the LC-3 register file (R0–R7 + condition flags).
 *
 * Provides read and write access to the general-purpose registers and
 * automatically updates condition flags (N, Z, P) on writes.
 */
class Registers {
public:
    /**
     * @brief Constructs and initializes all registers to 0.
     */
    Registers() noexcept;

    Registers(Registers const&) = delete;
    Registers(Registers&&) = delete;
    Registers& operator=(Registers const&) = delete;
    Registers& operator=(Registers&&) = delete;
    
    ~Registers() noexcept = default;

    /**
     * @brief Reads the value of the specified register.
     * @param index Register index [R0–R7] or FR for flags.
     * @return The 16-bit value stored in the register.
     */
    Word read(RegisterIndex index) const noexcept;

    /**
     * @brief Writes a value to the specified register.
     * @param index Register index [R0–R7].
     * @param value The 16-bit value to store.
     * @param update_flags Whether to update condition flags based on the value.
     */
    void write(RegisterIndex index, Word value, bool update_flags = true) noexcept;

    /**
     * @brief Returns the current condition flag.
     * @return One of NEGATIVE, ZERO, POSITIVE.
     */
    ConditionFlag get_condition_flag() const noexcept;

private:
    void update_condition_flags(Word value) noexcept;

private:
    std::array<Word, 9> registers_; ///< R0–R7 + FR (condition flags at index 8)
};

} // namespace lc3
