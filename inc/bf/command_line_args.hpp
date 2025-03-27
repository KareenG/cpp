#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

namespace bf {
   
 /**
 * @brief Handles and validates command line arguments for a Brainfuck interpreter.
 *
 * This class provides static methods to parse command line arguments and retrieve the
 * Brainfuck code for compilation directly, without maintaining any internal state.
 */
class CommandLineArgs {
public:
    /**
     * @brief Validates the command line arguments and retrieves the Brainfuck code.
     * 
     * @param argc Number of command line arguments.
     * @param argv Array of command line arguments.
     * @param code String to store the extracted Brainfuck code or file contents.
     * @return bool True if arguments are valid and code is retrieved, false otherwise.
     */
    static bool get_code_for_compilation(int argc, char* argv[], std::string& code);
};
   
}       // namespace bf
