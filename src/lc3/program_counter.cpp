#include "lc3/program_counter.hpp"

namespace lc3
{

ProgramCounter::ProgramCounter(uint16_t pc) noexcept
: p_counter_{pc}
{
}

uint16_t ProgramCounter::get() const noexcept
{
    return p_counter_;
}

void ProgramCounter::set(uint16_t new_pc) noexcept
{
    p_counter_ = new_pc;
}

void ProgramCounter::increment(uint16_t offset) noexcept
{
    p_counter_ += offset;
}

} // namespace lc3
