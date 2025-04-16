#pragma once

#include <cstdint>

#include "lc3/program_counter.hpp"
#include "lc3/memory.hpp"
#include "lc3/registers.hpp"
#include "lc3/console.hpp"
#include "lc3/trap_handler.hpp"
#include "lc3/control_unit.hpp"
#include "lc3/decoder.hpp"

namespace lc3 {

/**
 * @brief The CPU class is responsible for fetching, decoding, and executing LC-3 instructions.
 *
 * It manages the program counter, register file, and delegates trap execution to TrapHandler.
 * This is the main execution engine of the LC-3 virtual machine.
 */
class CPU {
public:
    /**
     * @brief Constructs a CPU instance with memory and console for I/O.
     *
     * @param memory Reference to the LC-3 memory.
     * @param console Reference to the console for I/O operations.
     */
    explicit CPU(Memory& memory, Console& console);

    CPU(CPU const&) = delete;
    CPU(CPU&&) = delete;
    CPU& operator=(CPU const&) = delete;
    CPU& operator=(CPU&&) = delete;

    ~CPU() noexcept = default;

    /**
     * @brief Runs the instruction cycle until a HALT instruction is encountered.
     *
     * This loop repeatedly fetches, decodes, and executes instructions,
     * using handler functions provided by the ControlUnit.
     */
    void run() noexcept;

private:
    /**
     * @brief Fetches the next instruction from memory, decodes it,
     *        and returns a bound handler for execution.
     *
     * @return A function object that performs the decoded instruction.
     */
    std::function<void()> fetch_and_decode () noexcept;

private:
    ProgramCounter pc_;
    Memory& memory_;
    Registers reg_file_;
    TrapHandler trap_handler_;
    bool is_running_;
    ControlUnit control_unit_;
    
    friend ControlUnit;
};

} // namespace lc3
