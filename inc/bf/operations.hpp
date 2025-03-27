#pragma once

#include <unordered_map>
#include <cstdint>

namespace bf {

/**
 * @brief Enum class for operation codes used in a Brainfuck-like language.
 *
 * This enumeration defines the set of operation codes that represent the possible commands
 * in the Brainfuck programming language, including command characters for moving the data pointer,
 * modifying data at the data pointer, input/output operations, and loop controls.
 */
enum class OpCode : uint8_t {
    MoveRight,      ///< Corresponds to '>'  moves the data pointer to the right.
    MoveLeft,       ///< Corresponds to '<', moves the data pointer to the left.
    Increment,      ///< Corresponds to '+', increments the byte at the data pointer.
    Decrement,      ///< Corresponds to '-', decrements the byte at the data pointer.
    Output,         ///< Corresponds to '.', outputs the byte at the data pointer as a character.
    Input,          ///< Corresponds to ',', accepts one byte of input, storing it at the data pointer.
    LoopStart,      ///< Corresponds to '[', if the byte at the data pointer is zero, jump forward to the command to the matching 'LoopEnd'.
    LoopEnd,        ///< Corresponds to ']', if the byte at the data pointer is nonzero, jump back to the command to the matching 'LoopStart'.
    HALT,           ///< Special operation to signify the end of execution.
    END             ///< Marks the end of the opcode list - the number of operations.
};

/**
 * @brief Maps characters from the Brainfuck programming language to their corresponding OpCode.
 *
 * This mapping is utilized by the compiler to translate Brainfuck source code into the
 * corresponding operational codes that the virtual machine can execute.
 */
const std::unordered_map<char, OpCode> op_code_map = {
    {'>', OpCode::MoveRight},
    {'<', OpCode::MoveLeft},
    {'+', OpCode::Increment},
    {'-', OpCode::Decrement},
    {'.', OpCode::Output},
    {',', OpCode::Input},
    {'[', OpCode::LoopStart},
    {']', OpCode::LoopEnd}
};

} // namespace bf
