#pragma once

#include <vector>
#include <stddef.h>

#include <bf/operations.hpp>

namespace bf {

/**
 * @brief Manages the execution logic for a Brainfuck-like language interpreter.
 *
 * This class encapsulates a program's instructions, handling the instruction pointer,
 * managing jump operations for loops ('[' and ']'), and executing the instructions.
 * It provides mechanisms to navigate the instruction sequence and determine when
 * the program execution is complete.
 *
 * @details
 * Members:
 * - std::vector<OpCode> instructions_: Holds all operation codes that the program will execute.
 * - size_t ip_: Tracks the current position of the instruction pointer within the instruction list.
 * - std::unordered_map<size_t, size_t> jump_table_: Maps loop start indices ('[') to their
 *   corresponding loop end indices (']') for efficient navigation within loops.
 */
class Program {
public:
    /**
     * @brief Constructs a Program object with a vector of opcodes.
     * 
     * @param source A vector of OpCode representing the program's source code.
     */
    Program(std::vector<OpCode> source); 

    /**
     * @brief Constructs a Program object with a list of opcodes and an existing jump table.
     *
     * This constructor can be used when the jump table is already known, avoiding redundant calculations.
     * 
     * @param source A vector of OpCode representing the program's instructions.
     * @param jump_t An existing jump table mapping loop start and end indices.
     */
    Program(std::vector<OpCode> source, std::unordered_map<size_t, size_t> jump_t);

    /**
     * @brief Default copy constructor.
     */
    Program(Program const& other) = default;

    /**
     * @brief Default destructor.
     */
    ~Program() = default;

    /**
     * @brief Default copy assignment operator.
     */
    Program& operator=(Program const& other) = default;

    /**
     * @brief Fetches the next opcode in the program sequence and increments the instruction pointer.
     * 
     * @return OpCode The next opcode to execute.
     */
    OpCode fetch_next();

    /**
     * @brief Fetches the current opcode without incrementing the instruction pointer.
     * 
     * @return OpCode The current opcode at the instruction pointer.
     */
    OpCode fetch_current();

    /**
     * @brief Jumps the instruction pointer by a specified offset.
     * 
     * @param offset The offset to jump from the current instruction pointer position.
     */
    void jump(int offset);

    /**
     * @brief Jumps forward to the matching ']' opcode for loops.
     * 
     * Used when encountering a loop start with a zero at the current cell.
     */
    void jump_forward_to_matching_end();

    /**
     * @brief Jumps backward to the matching '[' opcode for loops.
     * 
     * Used when encountering a loop end with a non-zero at the current cell.
     */
    void jump_backward_to_matching_start();

    /**
     * @brief Checks if the program has finished executing.
     * 
     * @return bool True if the instruction pointer has reached the end of the instructions, false otherwise.
     */
    bool is_done() const;

    //for debug mode
    const std::vector<OpCode>& get_instructions() const;
    const std::unordered_map<size_t, size_t>& get_jump_table() const;

private:
    /**
     * @brief Builds a jump table to map loop starts ('[') to their corresponding loop ends (']') and vice versa.
     * 
     * This method is called during construction to prepare the program for efficient loop execution.
     */
    void build_jump_table();

private:
    std::vector<OpCode> instructions_;
    size_t ip_;
    std::unordered_map<size_t, size_t> jump_table_;
};

}