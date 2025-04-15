#include "lc3/decoder.hpp"
#include "lc3/decoder_detail/bits.hpp"
#include "lc3/decoder_detail/bit_manipulations.hpp"

namespace lc3 {

namespace decoder {

OpCode get_opcode(uint16_t raw)
{
    return static_cast<OpCode>(bits::opcode(raw));
}

uint8_t get_dr(uint16_t raw)
{ 
    return bits::dr(raw); 
}

uint8_t get_sr(uint16_t raw)
{ 
    return bits::sr(raw); 
}

uint8_t get_sr1(uint16_t raw)
{ 
    return bits::sr1(raw); 
}

uint8_t get_sr2(uint16_t raw)
{ 
    return bits::sr2(raw); 
}

uint8_t get_base_r(uint16_t raw)
{ 
    return bits::base_r(raw); 
}

uint8_t get_trap_vector8(uint16_t raw)
{ 
    return bits::trap_vector(raw); 
}

int16_t get_signed_imm5(uint16_t raw)
{
    return bit_manipulations::sign_extend(bits::raw_imm5(raw), 5);
}

int16_t get_signed_offset9(uint16_t raw)
{
    return bit_manipulations::sign_extend(bits::raw_pc_offset9(raw), 9);
}

int16_t get_signed_offset11(uint16_t raw)
{
    return bit_manipulations::sign_extend(bits::raw_pc_offset11(raw), 11);
}

int16_t get_signed_offset6(uint16_t raw)
{
    return bit_manipulations::sign_extend(bits::raw_offset6(raw), 6);
}

bool is_immediate_mode(uint16_t raw)
{
    return bit_manipulations::is_immediate(raw);
}

bool branch_on_n(uint16_t raw)
{ 
    return bit_manipulations::check_n(raw); 
}

bool branch_on_z(uint16_t raw)
{ 
    return bit_manipulations::check_z(raw); 
}

bool branch_on_p(uint16_t raw)
{ 
    return bit_manipulations::check_p(raw); 
}

bool is_jsr(uint16_t raw_instruction)
{
    return bit_manipulations::is_jsr(raw_instruction);
}

uint16_t get_raw_value(uint16_t raw)
{ 
    return raw; 
}

} // namespace decoder

} // namespace lc3
