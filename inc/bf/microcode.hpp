#pragma once

#include <functional>
#include <sys/types.h>
#include <cstdint>

#include "bf/operations.hpp"
#include "bf/memory.hpp"
#include "bf/program.hpp"
#include "bf/console.hpp"

namespace bf {

/**
 * @brief Manages the execution of microcode instructions based on opcodes.
 *
 * This class serves as a controller that interprets and executes operations
 * defined as opcodes, manipulating the state of memory, program, and console
 * based on the instructions given in a Brainfudg-like language.
 * 
 * Members:
 * - Memory& memory_: Reference to the Memory component used for data storage and manipulation.
 * - Program& program_: Reference to the Program component managing the instruction flow.
 * - Console& console_: Reference to the Console component for input/output operations.
 * - std::array<std::function<void()>, static_cast<uint8_t>(OpCode::END)> commands_: 
 *   Array of command functions, each corresponding to an opcode, to execute the associated operation.
 */
class Microcode {
public:
    /**
     * @brief Constructs a Microcode object with references to memory, program, and console.
     * 
     * Initializes the microcode interpreter with necessary components to execute commands.
     * 
     * @param memory Reference to Memory used for data storage and manipulation.
     * @param program Reference to Program managing the instruction flow.
     * @param console Reference to Console for input/output operations.
     */
    explicit Microcode(Memory& memory, Program& program, Console& console);

    /**
     * @brief Retrieves the index of an opcode in the command array.
     * 
     * @param op The opcode whose index is to be retrieved.
     * @return int The index of the provided opcode.
     */
    int index(OpCode op);

    /**
     * @brief Executes the command associated with the given opcode.
     * 
     * Executes the function mapped to the opcode in the commands array.
     * 
     * @param op The opcode to execute.
     */
    void execute(OpCode op);
    
private:  
    /**
     * @brief Builds the commands array by associating opcodes with their corresponding functions.
     * 
     * This method initializes the command mapping, setting up the functional behavior for each opcode.
     */
    void build_commands();

private:
    Memory& memory_;
    Program& program_;
    Console& console_;
    std::array<std::function<void()>, static_cast<uint8_t>(OpCode::END)> commands_;
};

}