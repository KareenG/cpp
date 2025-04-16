#include "lc3/program_counter.hpp"

namespace lc3 {

ProgramCounter::ProgramCounter(Address pc) noexcept
: p_counter_{pc}
{
}

Address ProgramCounter::get() const noexcept
{
    return p_counter_;
}

void ProgramCounter::set(Address new_pc) noexcept
{
    p_counter_ = new_pc;
}

void ProgramCounter::increment(Address offset) noexcept
{
    p_counter_ += offset;
}

} // namespace lc3
