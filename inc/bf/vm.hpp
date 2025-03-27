#pragma once

#include <sys/types.h>
#include <string>

#include "bf/memory.hpp"
#include "bf/program.hpp"
#include "bf/microcode.hpp"
#include "bf/compiler.hpp"
#include "bf/console.hpp"

namespace bf {

/**
 * @brief Represents the virtual machine that manages the execution of Brainfuck-like programs.
 *
 * This class serves as the central execution engine for a Brainfuck-like language, coordinating
 * between the program's compiled code, memory model, input/output, and opcode execution logic.
 * It can execute programs that are either pre-compiled or compiled at runtime from source.
 *
 * Members:
 * - Memory& memory_: Reference to the Memory instance that stores data cells manipulated by the program.
 * - Program& program_: Reference to the Program instance that stores the opcode sequence and controls program flow.
 * - Console& console_: Reference to the Console instance used for input and output operations.
 * - Microcode microcode_: Instance of Microcode that interprets and executes the opcodes.
 */
class VM {
public:
    /**
     * @brief Constructs a VM with references to its main components.
     * 
     * Initializes the VM with references to existing Memory, Program, and Console instances.
     * This allows the VM to perform operations using the provided instances without owning them,
     * facilitating flexibility in memory management and reuse of components.
     *
     * @param memory Reference to a Memory instance for data storage.
     * @param program Reference to a Program instance for opcode management and execution control.
     * @param console Reference to a Console instance for handling input and output.
     */
    VM(Memory& memory ,Program& program, Console& console);

    /**
     * @brief Executes the program managed by this VM.
     *
     * Orchestrates the execution process by repeatedly fetching and executing opcodes from the Program,
     * interacting with the Memory for data manipulation, and utilizing the Console for any needed input or output.
     * The process continues until the program completes (i.e., when all opcodes are processed).
     */
    void run();
    
private:
    Memory& memory_;
    Program& program_;
    Console& console_;
    Microcode microcode_;
};

} // namespace bf
