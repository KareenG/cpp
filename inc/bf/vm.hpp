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
 * @brief Represents the virtual machine that manages the execution of Brainfudg-like programs.
 *
 * This class encapsulates all components necessary for running a program, including memory, compiler,
 * program logic, console for input/output, and microcode for opcode execution. It allows loading
 * programs either from a precompiled sequence of opcodes or by compiling from source code.
 *
 * Members:
 * - Memory memory_: Handles the data storage for the VM.
 * - Compiler compiler_: Compiles source code into opcodes.
 * - Program program_: Handles the sequence of operation codes.
 * - Console console_: Handles input and output operations.
 * - Microcode microcode_: Executes the opcodes.
 */
class VM {
public:
    // /**
    //  * @brief Constructs the VM with a pre-existing program.
    //  *
    //  * Initializes the virtual machine with a reference to an existing Program instance.
    //  * This constructor is typically used when the program has already been compiled.
    //  *
    //  * @param code A reference to a Program containing compiled opcodes.
    //  */
    // VM(Program& code);

    /**
     * @brief Constructs the VM with precompiled opcodes.
     *
     * This constructor initializes the VM with a set of opcodes that are already compiled and ready for execution.
     * It sets up the necessary components including Memory, Program, Console, and Microcode,
     * and prepares the VM to execute the provided opcodes.
     *
     * @param opcodes A vector of OpCode representing the compiled program.
     */
    explicit VM(const std::vector<OpCode>& opcodes);

    /**
     * @brief Constructs the VM with predefined opcodes and a console.
     *
     * @param opcodes A vector of Brainfuck opcodes ready for execution.
     * @param console A reference to a Console object for input and output operations.
     *
     * @note Ensure the Console object remains valid throughout the VM's lifetime.
     */
    VM(const std::vector<OpCode>& opcodes, Console& console);

    /**
     * @brief Runs the program managed by the VM.
     *
     * Executes the opcodes in the Program instance, handling input and output through the Console,
     * and using the Microcode component to execute each opcode.
     */
    void run();
    
private:
    Memory memory_;
    Program program_;
    Console console_;
    Microcode microcode_;
};

} // namespace bf
