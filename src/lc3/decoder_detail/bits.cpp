#include "lc3/decoder_detail/bits.hpp"
#include "lc3/decoder_detail/masks.hpp"

namespace lc3
{

namespace decoder::bits {

uint8_t opcode(uint16_t raw)
{
    return (raw & masks::OPCODE_MASK) >> 12;
}

uint8_t dr(uint16_t raw)
{ 
    //return (raw >> 9) & 0x7;
    return (raw & masks::DR_MASK) >> 9;
}

uint8_t sr(uint16_t raw)
{ 
    //return (raw >> 9) & 0x7;
    return (raw & masks::SR_MASK) >> 9;
}

uint8_t sr1(uint16_t raw)
{
    //return (raw >> 6) & 0x7;
    return (raw & masks::SR1_MASK) >> 6;
}

uint8_t sr2(uint16_t raw)
{ 
    //return raw & 0x7;
    return (raw & masks::SR2_MASK);
}

uint8_t base_r(uint16_t raw)
{ 
    //return (raw >> 6) & 0x7;
    return (raw & masks::BASE_R_MASK) >> 6;
}

uint8_t trap_vector(uint16_t raw)
{ 
    //return raw & 0xFF;
    return raw & masks::TRAP_VEC_MASK;
}

uint16_t raw_pc_offset9(uint16_t raw)
{ 
    //return raw & 0x1FF;
    return raw & masks::OFFSET9_MASK;
}

uint16_t raw_pc_offset11(uint16_t raw)
{ 
    //return raw & 0x7FF;
    return raw & masks::OFFSET11_MASK;
}

uint16_t raw_imm5(uint16_t raw)
{ 
    //return raw & 0x1F;
    return raw & masks::IMM5_MASK;
}

uint16_t raw_offset6(uint16_t raw)
{ 
    //return raw & 0x3F;
    return raw & masks::OFFSET6_MASK;
}

} // namespace decoder::bits

} // namespace lc3