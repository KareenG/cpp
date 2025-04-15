#include "lc3/registers.hpp"

namespace lc3 {

static constexpr uint8_t FLAGS_REGISTER_INDEX = 8;

Registers::Registers() noexcept
: registers_(9, 0) // R0–R7 + flags
{
}

uint16_t Registers::read(uint8_t index) const noexcept
{
    assert(index <= FLAGS_REGISTER_INDEX);
    return registers_[index];
}

void Registers::write(uint8_t index, uint16_t value, bool update_flags) noexcept
{
    assert(index <= FLAGS_REGISTER_INDEX);
    registers_[index] = value;

    if (index < 8 && update_flags) {
        update_condition_flags(value);
    }
}

void Registers::update_condition_flags(uint16_t value) noexcept
{
    if (value == 0) {
        registers_[FLAGS_REGISTER_INDEX] = static_cast<uint16_t>(ConditionFlag::ZERO);
    } else if (value >> 15) {
        registers_[FLAGS_REGISTER_INDEX] = static_cast<uint16_t>(ConditionFlag::NEGATIVE);
    } else {
        registers_[FLAGS_REGISTER_INDEX] = static_cast<uint16_t>(ConditionFlag::POSITIVE);
    }
}

ConditionFlag Registers::get_condition_flag() const noexcept
{
    return static_cast<ConditionFlag>(registers_[FLAGS_REGISTER_INDEX]);
}

} // namespace lc3
