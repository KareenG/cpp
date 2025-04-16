#include "lc3/registers.hpp"

namespace lc3 {

static constexpr uint8_t FLAGS_REGISTER_INDEX = static_cast<uint8_t>(RegisterIndex::FR);

Registers::Registers() noexcept
: registers_{}
{
}

Word Registers::read(RegisterIndex index) const noexcept
{
    return registers_[static_cast<uint8_t>(index)];
}

void Registers::write(RegisterIndex index, Word value, bool update_flags) noexcept
{
    const uint8_t i = static_cast<uint8_t>(index);
    registers_[i] = value;

    if (i < FLAGS_REGISTER_INDEX && update_flags) {
        update_condition_flags(value);
    }
}

void Registers::update_condition_flags(Word value) noexcept
{
    if (value == 0) {
        registers_[FLAGS_REGISTER_INDEX] = static_cast<Word>(ConditionFlag::ZERO);
    } else if (value >> (WordSize - 1)) {
        registers_[FLAGS_REGISTER_INDEX] = static_cast<Word>(ConditionFlag::NEGATIVE);
    } else {
        registers_[FLAGS_REGISTER_INDEX] = static_cast<Word>(ConditionFlag::POSITIVE);
    }
}

ConditionFlag Registers::get_condition_flag() const noexcept
{
    return static_cast<ConditionFlag>(registers_[FLAGS_REGISTER_INDEX]);
}

} // namespace lc3
