#include <cassert>
#include "lc3/trap_handler.hpp"

namespace lc3 {

TrapHandler::TrapHandler(Console& console) noexcept
: console_{console}
{
    initialize_trap_map();
}

void TrapHandler::initialize_trap_map()
{
    trap_map_ = {
        {TrapVector::GETC, [this](Registers& r, const Memory&, bool&) {
            console_.read_char_no_echo(r);
        }},
        {TrapVector::OUT, [this](Registers const& r, const Memory&, bool&) {
            console_.write_char(r);
        }},
        {TrapVector::PUTS, [this](Registers const& r, const Memory& mem, bool&) {
            console_.write_string_from_memory(r, mem);
        }},
        {TrapVector::IN, [this](Registers& r, const Memory&, bool&) {
            console_.prompt_and_read_char(r);
        }},
        {TrapVector::HALT, [this](Registers&, const Memory&, bool& running) {
            running = false;
        }}
    };
}

void TrapHandler::handle(TrapVector trap_vector, Registers& regs, const Memory& memory, bool& running) noexcept
{
    auto it = trap_map_.find(trap_vector);
    assert(it != trap_map_.end() && "Unsupported TRAP vector");
    it->second(regs, memory, running);
}

} // namespace lc3
