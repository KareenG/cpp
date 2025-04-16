#pragma once

#include <cstdint>

#include "lc3/consts_and_sizes.hpp"

namespace lc3 {

namespace ALU {

/**
 * @brief Executes an arithmetic or logic operation based on the provided OpCode.
 *
 * Supports the following ALU operations:
 * - ADD: Performs addition
 * - AND: Performs bitwise AND
 * - NOT: Performs bitwise NOT (ignores the second operand)
 *
 * @param opcode The operation to perform (must be one of ADD, AND, NOT).
 * @param lhs Left-hand side operand.
 * @param rhs Right-hand side operand (ignored for NOT).
 * @return Result of the ALU operation as a Word (16-bit).
 *
 * @note Asserts if the opcode is unsupported.
 */
Word execute(OpCode opcode, Word lhs, Word rhs);

} // namespace ALU

} // namespace lc3
