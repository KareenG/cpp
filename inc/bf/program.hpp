#pragma once

#include <vector>
#include <stddef.h>

#include <bf/operations.hpp>

namespace bf {

/**
 * @brief Represents the program logic for a Brainfudg-like language interpreter.
 *
 * This class manages a program's instructions, handling instruction pointers and jump operations
 * for loops (i.e., '[' and ']' commands). It supports fetching and executing instructions,
 * navigating the instruction sequence, and determining when the program execution is complete.
 *
 * Members:
 * - std::vector<OpCode> instructions: Holds all the operation codes to be executed.
 * - size_t ip: Tracks the current position of the instruction pointer within the instruction list.
 * - std::unordered_map<size_t, size_t> jump_table: Maps starting indices of loops ('[') to their
 *   corresponding ending indices (']') to facilitate quick jumps within the program.
 */
class Program {
public:
    /**
     * @brief Constructs a Program object with a vector of opcodes.
     * 
     * @param source A vector of OpCode representing the program's source code.
     */
    explicit Program(std::vector<OpCode> source);

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

private:
    /**
     * @brief Builds a jump table to map loop starts ('[') to their corresponding loop ends (']') and vice versa.
     * 
     * This method is called during construction to prepare the program for efficient loop execution.
     */
    void build_jump_table();

private:
    std::vector<OpCode> instructions;
    size_t ip;
    std::unordered_map<size_t, size_t> jump_table;
};

}