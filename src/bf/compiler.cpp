#include <stack>
#include <iostream>

#include "bf/compiler.hpp"

namespace bf {

Program Compiler::compile(const std::string& source)
{
    std::vector<OpCode> instructions  = Compiler::parse(source);
    std::unordered_map<size_t, size_t> jump_table;
    Compiler::build_jump_table(instructions , jump_table);
    return Program(instructions , jump_table);
}

void Compiler::build_jump_table(const std::vector<OpCode> instructions, std::unordered_map<size_t, size_t>& jump_table) 
{
    std::stack<size_t> loopStack;
    for (size_t i = 0; i < instructions.size(); ++i) {
        if (instructions[i] == OpCode::LoopStart) {
            loopStack.push(i);
        } else if (instructions[i] == OpCode::LoopEnd) {
            if (!loopStack.empty()) {
                size_t start = loopStack.top();
                loopStack.pop();
                jump_table[start] = i;
                jump_table[i] = start;
            }
        }
    }
}

std::vector<OpCode> Compiler::parse(const std::string& source) 
{
    std::string filtered = filter(source);
    std::vector<OpCode> operations;
    if (!validate(filtered)) {
        std::cerr << "Error: Unmatched brackets or invalid operations" << '\n';

        return {};
    }
    for (char c : filtered) {
        OpCode opcode = translate(c);
        if (opcode != OpCode::HALT) {
            operations.push_back(opcode);
        }
    }
    operations.push_back(OpCode::HALT);
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
    return it != op_code_map.end() ? it->second : OpCode::HALT;
}

}