#pragma once

#include <vector>
#include <cstdint>
#include <cassert>

namespace lc3 {

/**
 * @brief Condition flags used to track the result of the last ALU operation.
 */
enum class ConditionFlag : uint16_t {
    POSITIVE = 0x1,
    ZERO     = 0x2,
    NEGATIVE = 0x4
};

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

    /**
     * @brief Deleted copy constructor.
     */
    Registers(Registers const&) = delete;

    /**
     * @brief Deleted move constructor.
     */
    Registers(Registers&&) = delete;

    /**
     * @brief Deleted copy assignment operator.
     */
    Registers& operator=(Registers const&) = delete;

    /**
     * @brief Deleted move assignment operator.
     */
    Registers& operator=(Registers&&) = delete;

    /**
     * @brief Defaulted destructor.
     */
    ~Registers() noexcept = default;

    /**
     * @brief Reads the value of the specified register.
     * @param index Register index [0–7] for R0–R7, or 8 for flags.
     * @return Value stored in the register.
     * @note Asserts that index is within bounds.
     */
    uint16_t read(uint8_t index) const noexcept;

    /**
     * @brief Writes a value to the specified register.
     * @param index Register index [0–7].
     * @param value Value to store.
     * @param update_flags Whether to update condition flags based on the value.
     * @note Asserts that index is within bounds.
     */
    void write(uint8_t index, uint16_t value, bool update_flags = true) noexcept;

    /**
     * @brief Returns the current condition flag.
     */
    ConditionFlag get_condition_flag() const noexcept;

private:
    /**
     * @brief Updates the condition flags based on the result of an operation.
     * @param value The value to evaluate.
     *
     * @note Asserts that value is valid 16-bit input.
     * @note Updates the internal condition flags register.
     */
    void update_condition_flags(uint16_t value) noexcept;

private:
    std::vector<uint16_t> registers_; ///< R0–R7 + FLAGS (index 8).
};

} // namespace lc3
