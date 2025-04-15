#pragma once

#include <cstdint>

namespace lc3 {

namespace decoder::bits {

/**
 * @brief Extracts the 4-bit opcode field from a raw instruction.
 * @param raw The raw 16-bit LC-3 instruction.
 * @return The opcode field (bits [15:12]).
 */
uint8_t opcode(uint16_t raw);

/**
 * @brief Extracts the 3-bit DR (destination register) field.
 * @param raw The raw instruction.
 * @return The destination register index (bits [11:9]).
 */
uint8_t dr(uint16_t raw);

/**
 * @brief Extracts the 3-bit SR (source register) field.
 * @param raw The raw instruction.
 * @return The source register index (bits [11:9]).
 */
uint8_t sr(uint16_t raw);

/**
 * @brief Extracts the 3-bit SR1 (first source register) field.
 * @param raw The raw instruction.
 * @return The SR1 field (bits [8:6]).
 */
uint8_t sr1(uint16_t raw);

/**
 * @brief Extracts the 3-bit SR2 (second source register) field.
 * @param raw The raw instruction.
 * @return The SR2 field (bits [2:0]).
 */
uint8_t sr2(uint16_t raw);

/**
 * @brief Extracts the 3-bit BaseR field.
 * @param raw The raw instruction.
 * @return The BaseR field (bits [8:6]).
 */
uint8_t base_r(uint16_t raw);

/**
 * @brief Extracts the 8-bit trap vector.
 * @param raw The raw instruction.
 * @return The trap vector (bits [7:0]).
 */
uint8_t trap_vector(uint16_t raw);

/**
 * @brief Extracts the 9-bit PC-relative offset field.
 * @param raw The raw instruction.
 * @return The raw offset9 field (bits [8:0]).
 */
uint16_t raw_pc_offset9(uint16_t raw);

/**
 * @brief Extracts the 11-bit PC-relative offset field.
 * @param raw The raw instruction.
 * @return The raw offset11 field (bits [10:0]).
 */
uint16_t raw_pc_offset11(uint16_t raw);

/**
 * @brief Extracts the 5-bit immediate field.
 * @param raw The raw instruction.
 * @return The raw imm5 field (bits [4:0]).
 */
uint16_t raw_imm5(uint16_t raw);

/**
 * @brief Extracts the 6-bit offset field for LDR/STR.
 * @param raw The raw instruction.
 * @return The raw offset6 field (bits [5:0]).
 */
uint16_t raw_offset6(uint16_t raw);

} // namespace decoder::bits

} // namespace lc3
