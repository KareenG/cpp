#include "lc3/decoder_detail/bit_manipulations.hpp"
#include "lc3/decoder_detail/masks.hpp"

namespace lc3
{

namespace decoder::bit_manipulations {

int16_t sign_extend(uint16_t value, int bits)
{
    int16_t mask = 1 << (bits - 1);
    return (value ^ mask) - mask;
}

bool check_n(uint16_t raw)
{ 
    //return raw & 0x0800; 
    return raw & masks::COND_NEGATIVE;
}

bool check_z(uint16_t raw)
{ 
    //return raw & 0x0400;
    return raw & masks::COND_ZERO;
}

bool check_p(uint16_t raw)
{ 
    //return raw & 0x0200; 
    return raw & masks::COND_POSITIVE;
}

bool is_immediate(uint16_t raw)
{ 
    //return (raw >> 5) & 0x1;
    return raw & masks::COND_IMM5;
}

bool is_jsr(uint16_t raw)
{
    return raw & masks::BIT_11_MASK;
}
    
} // namespace decoder::bit_manipulations

} // namespace lc3
