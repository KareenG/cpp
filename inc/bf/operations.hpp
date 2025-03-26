#pragma once

#include <unordered_map>
#include <set>
#include <cstdint>

namespace bf {

/**
 * @brief Enum class for operation codes used in a Brainfudg-like language.
 */
enum class OpCode : uint8_t {
    MoveRight,      // >
    MoveLeft,       // <
    Increment,      // +
    Decrement,      // -
    Output,         // .
    Input,          // ,
    LoopStart,      // [
    LoopEnd,        // ]
    END
};

/**
 * @brief Maps characters to their corresponding OpCode.
 */
const std::unordered_map<char, OpCode> op_code_map = {
    {'>', OpCode::MoveRight},
    {'<', OpCode::MoveLeft},
    {'+', OpCode::Increment},
    {'-', OpCode::Decrement},
    {'.', OpCode::Output},
    {',', OpCode::Input},
    {'[', OpCode::LoopStart},
    {']', OpCode::LoopEnd}
};

} // namespace bf
    