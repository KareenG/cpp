#pragma once

#include <cstdint>

#include "lc3/program_counter.hpp"
#include "lc3/memory.hpp"
#include "lc3/registers.hpp"
#include "lc3/console.hpp"
#include "lc3/trap_handler.hpp"
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

    /**
     * @brief Deleted copy constructor.
     */
    CPU(CPU const&) = delete;

    /**
     * @brief Deleted move constructor.
     */
    CPU(CPU&&) = delete;

    /**
     * @brief Deleted copy assignment operator.
     */
    CPU& operator=(CPU const&) = delete;

    /**
     * @brief Deleted move assignment operator.
     */
    CPU& operator=(CPU&&) = delete;

    /**
     * @brief Defaulted destructor.
     */
    ~CPU() noexcept = default;

    /**
     * @brief Runs the main instruction fetch-decode-execute loop until HALT.
     */
    void run() noexcept;

private:
    /**
     * @brief Fetches the next instruction from memory.
     * @return The 16-bit instruction.
     * @note Increments the program counter.
     */
    uint16_t fetch_instruction() noexcept;

    /**
     * @brief Dispatches execution based on the instruction's opcode category.
     * @param raw_inst The 16-bit instruction.
     * @param running Reference to the CPU running flag.
     * @note Asserts that the opcode is known.
     */
    void execute_instruction(uint16_t raw_inst, bool& running) noexcept;

    /**
     * @brief Handles ADD, AND, and NOT instructions.
     * @param op Operation code (must be ADD, AND, or NOT).
     * @param raw_inst Encoded instruction.
     */
    void handle_operate_instruction(OpCode op, uint16_t raw_inst) noexcept;

    /**
     * @brief Handles load/store related instructions (LD, LDI, LDR, LEA, ST, STR, STI).
     * @param op The opcode.
     * @param raw_inst The instruction.
     */
    void handle_data_movement_instruction(OpCode op, uint16_t raw_inst) noexcept;

    /**
     * @brief Handles branch and jump control flow instructions (BR, JMP, JSR, etc).
     * @param op The opcode.
     * @param raw_inst The instruction.
     */
    void handle_control_instruction(OpCode op, uint16_t raw_inst) noexcept;

    /**
     * @brief Handles TRAP instructions using the trap handler.
     * @param raw_inst The instruction.
     * @param running Reference to the CPU running flag.
     * @note Asserts that the trap code is supported.
     */
    void handle_trap_instruction(uint16_t raw_inst, bool& running) noexcept;

private:
    ProgramCounter pc_;
    Memory& memory_;
    Registers reg_file_;
    TrapHandler trap_handler_;
};

} // namespace lc3
