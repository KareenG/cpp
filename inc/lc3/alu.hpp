#pragma once

#include <cstdint>

#include "lc3/decoder.hpp"

namespace lc3 {

namespace ALU {

/**
 * @brief Executes an arithmetic or logic operation based on the provided OpCode.
 *
 * This function supports ADD, AND, and NOT operations. The NOT operation ignores the second operand.
 * 
 * @param opcode Operation to perform (ADD, AND, or NOT).
 * @param lhs The left-hand-side operand.
 * @param rhs The right-hand-side operand. Ignored for NOT.
 * @return The 16-bit result of the ALU operation.
 *
 * @note Asserts that the opcode is ADD, AND, or NOT.
 */
uint16_t execute(OpCode opcode, uint16_t lhs, uint16_t rhs);

} // namespace ALU

} // namespace lc3














// #pragma once

// #include <cstdint>
// #include <unordered_map>
// #include <functional>

// #include "lc3/decoder.hpp"

// namespace lc3 {

// namespace ALU {
// // class ALU {
// // public:
// using AluFunc = std::function<uint16_t(uint16_t, uint16_t)>;

//     //ALU();

// uint16_t execute(lc3::OpCode opcode, uint16_t lhs, uint16_t rhs);

// //private:
// std::unordered_map<lc3::OpCode, AluFunc> operation_map_;

// //};

// } // ALU

// } // namespace lc3