#pragma once

#include <cstdint>
#include <cassert>

#include "lc3/console.hpp"
#include "lc3/registers.hpp"
#include "lc3/memory.hpp"

namespace lc3 {

/**
 * @brief Handles execution of LC-3 TRAP instructions.
 *
 * Centralizes TRAP vector dispatch logic and delegates input/output behavior
 * to a Console object.
 */
class TrapHandler {
public:
    /**
     * @brief Construct a TrapHandler that delegates to a console.
     *
     * @param console Reference to the Console instance.
     */
    explicit TrapHandler(Console& console) noexcept;

    /**
     * @brief Deleted copy constructor.
     */
    TrapHandler(TrapHandler const&) = delete;

    /**
     * @brief Deleted move constructor.
     */
    TrapHandler(TrapHandler&&) = delete;

    /**
     * @brief Deleted copy assignment operator.
     */
    TrapHandler& operator=(TrapHandler const&) = delete;

    /**
     * @brief Deleted move assignment operator.
     */
    TrapHandler& operator=(TrapHandler&&) = delete;

    /**
     * @brief Defaulted destructor.
     */
    ~TrapHandler() noexcept = default;

    /**
     * @brief Executes the behavior of a given TRAP vector.
     *
     * Dispatches control to the appropriate trap service (GETC, OUT, PUTS, IN, HALT).
     *
     * @param trap_vector The 8-bit trap vector.
     * @param regs Reference to the register file (used for passing arguments/results).
     * @param memory Const reference to memory (used for PUTS).
     * @param running Reference to a boolean flag that controls CPU execution.
     *
     * @note Asserts that the trap vector is supported.
     */
    void handle(uint8_t trap_vector, Registers& regs, const Memory& memory, bool& running) noexcept;

private:
    Console& console_;
};

} // namespace lc3
