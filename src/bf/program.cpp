#include <string>
#include <sstream>
#include <stack>
#include <iostream>

#include "bf/program.hpp"

namespace bf {

Program::Program(std::vector<OpCode> source)
: instructions_{source}
, ip_{0}
{
    build_jump_table();
    instructions_.push_back(OpCode::HALT); // in case we forgot halt at the end
}

Program::Program(std::vector<OpCode> source, std::unordered_map<size_t, size_t> jump_t)
: instructions_{source}
, ip_{0}
, jump_table_{jump_t}
{
}

void Program::jump(int offset) 
{
    int new_ip = (static_cast<int>(ip_) + offset);
    if (new_ip >= 0 && static_cast<size_t>(new_ip) < instructions_.size()) {
        ip_ = static_cast<size_t>(new_ip);
    }
}

OpCode Program::fetch_next() 
{
    if (ip_ < instructions_.size()) {
        return instructions_[ip_++];
    } else {
        return OpCode::HALT;
    }
}

OpCode Program::fetch_current() 
{
    return instructions_[ip_];
}

bool Program::is_done() const 
{
    return instructions_[ip_] == OpCode::HALT;
}

void Program::build_jump_table() 
{
    std::stack<size_t> loopStack;
    for (size_t i = 0; i < instructions_.size(); ++i) {
        if (instructions_[i] == OpCode::LoopStart) {
            loopStack.push(i);
        } else if (instructions_[i] == OpCode::LoopEnd) {
            if (!loopStack.empty()) {
                size_t start = loopStack.top();
                loopStack.pop();
                jump_table_[start] = i;
                jump_table_[i] = start;
            }
        }
    }
}

void Program::jump_forward_to_matching_end() 
{
    if (jump_table_.find(ip_) != jump_table_.end()) {
        ip_ = jump_table_[ip_];
    }
}

void Program::jump_backward_to_matching_start() 
{
    if (jump_table_.find(ip_) != jump_table_.end()) {
        ip_ = jump_table_[ip_];
    }
}

// for debug
const std::vector<OpCode>& Program::get_instructions() const 
{
    return instructions_;
}

const std::unordered_map<size_t, size_t>& Program::get_jump_table() const 
{
    return jump_table_;
}

}
