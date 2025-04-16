#pragma once

#include <functional>
#include <unordered_map>

#include "lc3/consts_and_sizes.hpp"

namespace lc3 {

namespace decoder {

/**
 * @brief Extracts the opcode field from an instruction.
 */
OpCode get_opcode(Word raw_instruction);

/**
 * @brief Extracts the DR (destination register) from the instruction.
 */
RegisterIndex get_dr(Word raw_instruction);

/**
 * @brief Extracts the SR (source register) from the instruction.
 */
RegisterIndex get_sr(Word raw_instruction);

/**
 * @brief Extracts SR1 (first source register) from the instruction.
 */
RegisterIndex get_sr1(Word raw_instruction);

/**
 * @brief Extracts SR2 (second source register) from the instruction.
 */
RegisterIndex get_sr2(Word raw_instruction);

/**
 * @brief Returns whether the instruction is in immediate mode.
 */
bool is_immediate_mode(Word raw_instruction);

/**
 * @brief Returns the sign-extended 5-bit immediate value.
 */
int16_t get_signed_imm5(Word raw_instruction);

/**
 * @brief Returns the sign-extended 9-bit PC offset.
 */
int16_t get_signed_offset9(Word raw_instruction);

/**
 * @brief Returns the sign-extended 11-bit PC offset.
 */
int16_t get_signed_offset11(Word raw_instruction);

/**
 * @brief Returns the sign-extended 6-bit offset.
 */
int16_t get_signed_offset6(Word raw_instruction);

/**
 * @brief Extracts the base register used in control/data instructions.
 */
RegisterIndex get_base_r(Word raw_instruction);

/**
 * @brief Extracts the 8-bit TRAP vector.
 */
TrapVector get_trap_vector8(Word raw_instruction);

/**
 * @brief Returns true if the BR instruction will branch on negative.
 */
bool branch_on_n(Word raw_instruction);

/**
 * @brief Returns true if the BR instruction will branch on zero.
 */
bool branch_on_z(Word raw_instruction);

/**
 * @brief Returns true if the BR instruction will branch on positive.
 */
bool branch_on_p(Word raw_instruction);

/**
 * @brief Returns true if the instruction is a JSR (not JSRR).
 */
bool is_jsr(Word raw_instruction);

/**
 * @brief Returns the raw instruction unchanged.
 */
Word get_raw_value(Word raw_instruction);

} // namespace decoder

} // namespace lc3
