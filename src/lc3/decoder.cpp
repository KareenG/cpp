#include "lc3/decoder.hpp"
#include "lc3/decoder_detail/bits.hpp"
#include "lc3/decoder_detail/bit_manipulations.hpp"

namespace lc3 {
    
namespace decoder {

OpCode get_opcode(Word raw)
{
    return static_cast<OpCode>(bits::opcode(raw));
}

RegisterIndex get_dr(Word raw)
{ 
    return static_cast<RegisterIndex>(bits::dr(raw)); 
}

RegisterIndex get_sr(Word raw)
{ 
    return static_cast<RegisterIndex>(bits::sr(raw)); 
}

RegisterIndex get_sr1(Word raw)
{ 
    return static_cast<RegisterIndex>(bits::sr1(raw)); 
}

RegisterIndex get_sr2(Word raw)
{ 
    return static_cast<RegisterIndex>(bits::sr2(raw)); 
}

RegisterIndex get_base_r(Word raw)
{ 
    return static_cast<RegisterIndex>(bits::base_r(raw)); 
}

TrapVector get_trap_vector8(Word raw)
{ 
    return static_cast<TrapVector>(bits::trap_vector(raw)); 
}

int16_t get_signed_imm5(Word raw)
{
    return bit_manipulations::sign_extend(bits::raw_imm5(raw), 5);
}

int16_t get_signed_offset9(Word raw)
{
    return bit_manipulations::sign_extend(bits::raw_pc_offset9(raw), 9);
}

int16_t get_signed_offset11(Word raw)
{
    return bit_manipulations::sign_extend(bits::raw_pc_offset11(raw), 11);
}

int16_t get_signed_offset6(Word raw)
{
    return bit_manipulations::sign_extend(bits::raw_offset6(raw), 6);
}

bool is_immediate_mode(Word raw)
{
    return bit_manipulations::is_immediate(raw);
}

bool branch_on_n(Word raw)
{ 
    return bit_manipulations::check_n(raw); 
}

bool branch_on_z(Word raw)
{ 
    return bit_manipulations::check_z(raw); 
}

bool branch_on_p(Word raw)
{ 
    return bit_manipulations::check_p(raw); 
}

bool is_jsr(Word raw)
{
    return bit_manipulations::is_jsr(raw);
}

Word get_raw_value(Word raw)
{ 
    return raw; 
}

} // namespace decoder

} // namespace lc3
