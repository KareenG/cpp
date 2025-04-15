#pragma once

#include <cstdint>

namespace lc3 {

namespace decoder::bit_manipulations {

/**
 * @brief Sign-extends a bitfield value to a 16-bit signed integer.
 * 
 * @example
 * Let’s say:
 *   value is an unsigned integer from a bits-bit field.
 * You want to interpret `value` as a signed number. Then:
 *   sign_extend(value, bits) = (value ^ sign_bit_mask) - sign_bit_mask
 * Where:
 *   sign_bit_mask = 1 << (bits - 1)
 * 
 * This works because:
 *  - XORing flips the sign bit.
 *  - Subtracting the mask repositions the number around 0.
 * 
 * @param value The unsigned value to be sign-extended.
 * @param bits The number of bits in the original field.
 * @return The sign-extended 16-bit integer.
 */
int16_t sign_extend(uint16_t value, int bits);

/**
 * @brief Checks if the N (negative) flag is set in a BR instruction.
 * @param raw The raw 16-bit instruction.
 * @return True if the N condition bit is set.
 */
bool check_n(uint16_t raw);

/**
 * @brief Checks if the Z (zero) flag is set in a BR instruction.
 * @param raw The raw 16-bit instruction.
 * @return True if the Z condition bit is set.
 */
bool check_z(uint16_t raw);

/**
 * @brief Checks if the P (positive) flag is set in a BR instruction.
 * @param raw The raw 16-bit instruction.
 * @return True if the P condition bit is set.
 */
bool check_p(uint16_t raw);

/**
 * @brief Checks if the instruction uses immediate mode (IMM5).
 * @param raw The raw 16-bit instruction.
 * @return True if immediate mode is enabled.
 */
bool is_immediate(uint16_t raw);

/**
 * @brief Checks if a JSR/JSRR instruction is in JSR (PC-relative) mode.
 * @param raw The raw 16-bit instruction.
 * @return True if bit 11 is set (indicating JSR).
 */
bool is_jsr(uint16_t raw);

} // namespace decoder::bit_manipulations

} // namespace lc3
