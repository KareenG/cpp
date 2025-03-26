#include <string>
#include <sstream>
#include <stack>
#include <iostream>

#include "bf/program.hpp"

namespace bf {

Program::Program(std::vector<OpCode> source)
: instructions{source}
, ip{0}
{
    build_jump_table();
}

void Program::jump(int offset) {
    int new_ip = (static_cast<int>(ip) + offset);
    if (new_ip >= 0 && static_cast<size_t>(new_ip) < instructions.size()) {
        ip = static_cast<size_t>(new_ip);
    }
}

OpCode Program::fetch_next() {
    if (ip < instructions.size()) {
        return instructions[ip++];
    } else {
        return OpCode::END;
    }
}

OpCode Program::fetch_current() {
    return instructions[ip];
}

bool Program::is_done() const 
{
    return instructions[ip] == OpCode::END;
}

void Program::build_jump_table() {
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

void Program::jump_forward_to_matching_end() {
    if (jump_table.find(ip) != jump_table.end()) {
        ip = jump_table[ip];
    }
}

void Program::jump_backward_to_matching_start() {
    if (jump_table.find(ip) != jump_table.end()) {
        ip = jump_table[ip];
    }
}

}
