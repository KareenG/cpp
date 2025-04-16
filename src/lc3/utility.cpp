#include "lc3/utility.hpp"

namespace lc3 {

bool is_little_endian() noexcept {
    const uint16_t test = 0x1;
    return *reinterpret_cast<const uint8_t*>(&test) == 0x1;
}

Word from_big_endian(Word value) noexcept {
    if (is_little_endian()) {
        return static_cast<Word>((value >> 8) | (value << 8));
    }
    return value;
}

} // namespace lc3
