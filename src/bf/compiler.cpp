#include <stack>
#include <iostream>

#include "bf/compiler.hpp"

namespace bf {

std::vector<OpCode> Compiler::parse(const std::string& source) 
{
    std::string filtered = filter(source);
    std::vector<OpCode> operations;
    if (!validate(filtered)) {
        std::cerr <<("Error: Unmatched brackets or invalid operations");
        return {};
    }
    for (char c : filtered) {
        OpCode opcode = translate(c);
        if (opcode != OpCode::END) {
            operations.push_back(opcode);
        }
    }
    operations.push_back(OpCode::END);
    return operations;
}

std::string Compiler::filter(const std::string& source) 
{
    std::string filtered;
    for (char c : source) {
        std::unordered_map<char, OpCode>::const_iterator it = op_code_map.find(c);
        if (it != op_code_map.end()) {
            filtered.push_back(c);
        }
    }
    return filtered;
}

bool Compiler::validate(const std::string& source) 
{
    std::stack<size_t> bracket_stack;
    size_t index = 0;
    for (char c : source) {
        OpCode op = translate(c);
        switch (op) {
            case OpCode::LoopStart:
                bracket_stack.push(index);
                break;
            case OpCode::LoopEnd:
                if (bracket_stack.empty()) {
                    return false;
                }
                bracket_stack.pop();
                break;
            default:
                break;
        }
        index++;
    }
    return bracket_stack.empty();
}

OpCode Compiler::translate(char c) 
{
    std::unordered_map<char, OpCode>::const_iterator it = op_code_map.find(c);
    return it != op_code_map.end() ? it->second : OpCode::END;
}

}