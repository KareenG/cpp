#pragma once

#include <cstdint>

namespace lc3 {

namespace decoder::masks {

/**
 * @brief Mask for extracting the opcode (bits [15:12]).
 */
constexpr uint16_t OPCODE_MASK = 0xF000;

/**
 * @brief Mask for extracting 5-bit immediate values (IMM5, bits [4:0]).
 */
constexpr uint16_t IMM5_MASK = 0x001F;

/**
 * @brief Mask for extracting a 9-bit PC-relative offset (bits [8:0]).
 */
constexpr uint16_t OFFSET9_MASK = 0x01FF;

/**
 * @brief Mask for extracting an 11-bit PC-relative offset (bits [10:0]).
 */
constexpr uint16_t OFFSET11_MASK = 0x07FF;

/**
 * @brief Mask for extracting a 6-bit offset (bits [5:0]).
 */
constexpr uint16_t OFFSET6_MASK = 0x003F;

/**
 * @brief Mask for extracting the destination register (DR, bits [11:9]).
 */
constexpr uint16_t DR_MASK = 0x0E00;

/**
 * @brief Mask for extracting the source register (SR, bits [11:9]).
 */
constexpr uint16_t SR_MASK = 0x0E00;

/**
 * @brief Mask for extracting the first source register (SR1, bits [8:6]).
 */
constexpr uint16_t SR1_MASK = 0x01C0;

/**
 * @brief Mask for extracting the second source register (SR2, bits [2:0]).
 */
constexpr uint16_t SR2_MASK = 0x0007;

/**
 * @brief Mask for extracting the base register (BaseR, bits [8:6]).
 */
constexpr uint16_t BASE_R_MASK = 0x01C0;

/**
 * @brief Mask for extracting the trap vector (bits [7:0]).
 */
constexpr uint16_t TRAP_VEC_MASK = 0x00FF;

/**
 * @brief Mask for checking if the instruction uses immediate mode (bit [5]).
 */
constexpr uint16_t COND_IMM5 = 0x0020;

/**
 * @brief Mask for checking bit 11 (used in JSR vs. JSRR distinction).
 */
constexpr uint16_t BIT_11_MASK = 0x0800;

/**
 * @brief Branch condition mask for negative flag (N).
 */
constexpr uint16_t COND_NEGATIVE = 0x0800;

/**
 * @brief Branch condition mask for zero flag (Z).
 */
constexpr uint16_t COND_ZERO = 0x0400;

/**
 * @brief Branch condition mask for positive flag (P).
 */
constexpr uint16_t COND_POSITIVE = 0x0200;

} // namespace decoder::masks

} // namespace lc3
