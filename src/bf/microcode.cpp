#include <iostream>
#include <sys/types.h>

#include "bf/microcode.hpp"

namespace bf {

Microcode::Microcode(Memory& memory, Program& program, Console& console)
: memory_{memory}
, program_{program}
, console_{console}
{
    build_commands();
}

int Microcode::index(OpCode op) 
{ 
    return static_cast<int>(op);
}

void Microcode::build_commands() {
    commands_[index(OpCode::Increment)] = [this](){ memory_.write(static_cast<uint8_t>(memory_.read() + 1)); };
    commands_[index(OpCode::Decrement)] = [this](){ memory_.write(static_cast<uint8_t>(memory_.read() - 1)); };
    commands_[index(OpCode::MoveLeft)] = [this](){ memory_.move_left(); };
    commands_[index(OpCode::MoveRight)] = [this](){ memory_.move_right(); };
    
    commands_[index(OpCode::Output)] = [this](){ 
        console_.write(memory_.read());
    };
    commands_[index(OpCode::Input)] = [this]() {
        unsigned char c = console_.read();
        memory_.write(c);
    };

    commands_[index(OpCode::LoopStart)] = [this]() {
        if (memory_.read() == 0) {
            program_.jump_forward_to_matching_end();
        }
    };

    commands_[index(OpCode::LoopEnd)] = [this]() {
        if (memory_.read() != 0) {
            program_.jump_backward_to_matching_start();
        }
    };
}

void Microcode::execute(OpCode op) 
{
    int index = Microcode::index(op);
    commands_[index]();
    program_.jump(1);
}

}