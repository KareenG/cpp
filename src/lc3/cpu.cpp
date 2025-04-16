#include <cassert>
#include <functional>

#include "lc3/consts_and_sizes.hpp"
#include "lc3/cpu.hpp"

namespace lc3
{
    
CPU::CPU(Memory& mem, Console& console)
: pc_{mem.get_program_start()}
, memory_{mem}
, reg_file_{}
, trap_handler_{console}
, is_running_{false}
, control_unit_(*this)
{
}

void CPU::run() noexcept
{
    is_running_ = true;
    while (is_running_) {
        std::function<void()> instruction_handler = fetch_and_decode();
        instruction_handler();
    }
}

std::function<void()> CPU::fetch_and_decode () noexcept
{
    Word instruction = memory_.read(pc_.get());
    pc_.increment();                                    // PC is now PC + 1
    return control_unit_.get_handler(instruction);
}

} // namespace lc3