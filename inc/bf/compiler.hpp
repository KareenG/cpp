# pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "bf/operations.hpp"
#include "bf/program.hpp"

namespace bf {

/**
 * @brief This class is responsible for compiling source code from a high-level representation
 * into a set of operation codes (OpCodes) as defined in 'operations.hpp'.
 */
class Compiler {
public:
    /**
     * @brief Compiles the given source string into a Program.
     * 
     * This method involves parsing the source code into opcodes, building a jump table for loop control,
     * and creating a Program instance with these components.
     * 
     * @param source The Brainfuck source code to be compiled.
     * @return Program The compiled program.
     */
    Program compile(const std::string& source);

    /**
     * @brief Parses the given source string into a vector of opcodes.
     * 
     * Filters the source to remove non-relevant characters, validates the filtered source for correct syntax,
     * and translates each valid character into an OpCode, collecting them into a vector. The vector is
     * returned with an 'END' OpCode marking the completion.
     * 
     * @param source The source code to be parsed.
     * @return std::vector<OpCode> The vector of parsed opcodes.
     * 
     * @note If validation fails, logs an error to standard error output and returns an empty vector.
     */
    std::vector<OpCode> parse(const std::string& source);

    /**
     * @brief Builds a jump table for matching loop start and end points.
     * 
     * This function generates mappings from loop start indices to their corresponding loop end indices
     * and vice versa, facilitating efficient control flow during program execution.
     * 
     * @param instructions The vector of opcodes previously parsed from the source.
     * @param jump_table Reference to an unordered_map to store the loop start and end mappings.
     */
    void build_jump_table(std::vector<OpCode> instructions, std::unordered_map<size_t, size_t>& jump_table);

private:
    /**
     * @brief Filters the source code to remove any non-instruction characters.
     * 
     * This method helps in cleaning the input source code by removing characters
     * that are not part of the programming language syntax.
     * 
     * @param source The unfiltered source code.
     * @return std::string The filtered source code.
     */
    std::string filter(const std::string& source);

    /**
     * @brief Translates a single character into its corresponding OpCode.
     * 
     * @param c The character to translate.
     * @return OpCode The corresponding opcode of the character.
     */
    OpCode translate(char c);

    /**
     * @brief Validates the source code for correct bracket pairing.
     * 
     * This method ensures that all loop start and end markers ('[' and ']') in the source code are correctly paired.
     *
     * @param source The source code to validate, consisting of characters that are translated into OpCodes.
     * @return bool True if all loops are properly closed and no unmatched loop end markers are found, false otherwise.
     */
    bool validate(const std::string& source);
};

}