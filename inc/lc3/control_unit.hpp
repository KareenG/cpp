#pragma once

#include <cstdint>
#include <unordered_map>
#include <functional>

#include "lc3/consts_and_sizes.hpp"

namespace lc3 {

class CPU; // forward declaration

/**
 * @brief Responsible for mapping LC-3 instructions to their handler functions.
 *
 * The ControlUnit interprets the raw instruction and returns a callable handler
 * that performs the correct behavior based on the instruction category and opcode.
 */
class ControlUnit {



public:
    /**
     * @brief Construct a ControlUnit associated with the given CPU instance.
     */
    explicit ControlUnit(CPU& cpu);

    ControlUnit(ControlUnit const&) = delete;
    ControlUnit(ControlUnit&&) = delete;
    ControlUnit& operator=(ControlUnit const&) = delete;
    ControlUnit& operator=(ControlUnit&&) = delete;
    ~ControlUnit() noexcept = default;

    /**
     * @brief Decode the instruction and return a bound handler for execution.
     * 
     * @param instruction The 16-bit raw LC-3 instruction.
     * @return A function object that executes the decoded instruction.
     *
     * @throws UnknownInstructionException if the instruction has an invalid opcode.
     */
    std::function<void()> get_handler(Word instruction);

private:
    void initialize_maps();
    void operate_map();
    void initialize_data_movement_map();
    void initialize_control_map();
    void initialize_trap_map();
    void initialize_category_handler_map();

private:
    CPU& cpu_;  ///< Reference to parent CPU

    std::unordered_map<OpCode, std::function<void(CPU&, Word)>> operate_map_;
    std::unordered_map<OpCode, std::function<void(CPU&, Word)>> data_movement_map_;
    std::unordered_map<OpCode, std::function<void(CPU&, Word)>> control_map_;
    std::unordered_map<OpCode, std::function<void(CPU&, Word)>> trap_map_;
    std::unordered_map<InstructionCategory, std::function<std::function<void()>(CPU&, Word)>> category_handler_map_;
};

} // namespace lc3
