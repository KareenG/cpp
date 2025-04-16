#pragma once

#include <cstdint>
#include <unordered_map>
#include <functional>

namespace lc3 {

/**
 * @brief The LC-3 architecture word type (16-bit data unit).
 */
using Word = uint16_t;

/**
 * @brief The address type used for memory access.
 */
using Address = uint16_t;

/**
 * @brief Word size in bits (fixed to 16 for LC-3).
 */
inline constexpr int WordSize = 16;

/**
 * @brief Total number of memory locations (2^16).
 */
inline constexpr std::size_t MemorySize = 65'536; // 1 << 16


/**
 * @brief Enumeration of LC-3 registers indexes.
 */
enum class RegisterIndex : uint8_t {
    R0  = 0x0,
    R1  = 0x1,
    R2  = 0x2,
    R3  = 0x3,
    R4  = 0x4,
    R5  = 0x5,
    R6  = 0x6,
    R7  = 0x7,
    FR  = 0x8,  // flag register
};

/**
 * @brief Condition flags used to track the result of the last ALU operation.
 */
enum class ConditionFlag : uint16_t {
    POSITIVE = 0x1,
    ZERO     = 0x2,
    NEGATIVE = 0x4
};

/**
 * @brief Enumeration of LC-3 instruction opcodes.
 */
enum class OpCode : uint16_t {
    BR   = 0x0,  ///< Branch
    ADD  = 0x1,  ///< Add
    LD   = 0x2,  ///< Load
    ST   = 0x3,  ///< Store
    JSR  = 0x4,  ///< Jump to subroutine
    JSRR = 0x4,  ///< Jump to subroutine register (alias of JSR)
    AND  = 0x5,  ///< Bitwise AND
    LDR  = 0x6,  ///< Load base + offset
    STR  = 0x7,  ///< Store base + offset
    RTI  = 0x8,  ///< Return from interrupt
    NOT  = 0x9,  ///< Bitwise NOT
    LDI  = 0xA,  ///< Load indirect
    STI  = 0xB,  ///< Store indirect
    JMP  = 0xC,  ///< Jump
    RET  = 0xC,  ///< Return (alias of JMP)
    LEA  = 0xE,  ///< Load effective address
    TRAP = 0xF   ///< Execute trap
};

/**
 * @brief Categories of LC-3 instructions.
 */
enum class InstructionCategory {
    Operate,       ///< Arithmetic/logic operations
    DataMovement,  ///< Load/store operations
    Control,       ///< Branches, jumps, subroutines
    Trap           ///< Operating system routines
};

/**
 * @brief Mapping from OpCode to its instruction category.
 */
const std::unordered_map<OpCode, InstructionCategory> opcode_category = {
    // Operate
    {OpCode::ADD, InstructionCategory::Operate},
    {OpCode::AND, InstructionCategory::Operate},
    {OpCode::NOT, InstructionCategory::Operate},

    // Data Movement
    {OpCode::LD,  InstructionCategory::DataMovement},
    {OpCode::LDR, InstructionCategory::DataMovement},
    {OpCode::LDI, InstructionCategory::DataMovement},
    {OpCode::ST,  InstructionCategory::DataMovement},
    {OpCode::STR, InstructionCategory::DataMovement},
    {OpCode::STI, InstructionCategory::DataMovement},
    {OpCode::LEA, InstructionCategory::DataMovement},

    // Control
    {OpCode::BR,   InstructionCategory::Control},
    {OpCode::JMP,  InstructionCategory::Control},
    {OpCode::RET,  InstructionCategory::Control},
    {OpCode::JSR,  InstructionCategory::Control},
    {OpCode::JSRR, InstructionCategory::Control},

    // Trap
    {OpCode::TRAP, InstructionCategory::Trap},
};

/**
 * @brief LC-3 TRAP vector values.
 */
enum class TrapVector : uint8_t {
    GETC = 0x20,
    OUT  = 0x21,
    PUTS = 0x22,
    IN   = 0x23,
    HALT = 0x25,
};



} // namespace lc3
