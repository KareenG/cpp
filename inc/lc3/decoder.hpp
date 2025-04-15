#pragma once

#include <cstdint>
#include <functional>
#include <unordered_map>

namespace lc3 {

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

namespace decoder {

/**
 * @brief Extracts the opcode field from an instruction.
 */
OpCode get_opcode(uint16_t raw_instruction);

/**
 * @brief Extracts the DR (destination register) from the instruction.
 */
uint8_t get_dr(uint16_t raw_instruction);

/**
 * @brief Extracts the SR (source register) from the instruction.
 */
uint8_t get_sr(uint16_t raw_instruction);

/**
 * @brief Extracts SR1 (first source register) from the instruction.
 */
uint8_t get_sr1(uint16_t raw_instruction);

/**
 * @brief Extracts SR2 (second source register) from the instruction.
 */
uint8_t get_sr2(uint16_t raw_instruction);

/**
 * @brief Returns whether the instruction is in immediate mode.
 */
bool is_immediate_mode(uint16_t raw_instruction);

/**
 * @brief Returns the sign-extended 5-bit immediate value.
 */
int16_t get_signed_imm5(uint16_t raw_instruction);

/**
 * @brief Returns the sign-extended 9-bit PC offset.
 */
int16_t get_signed_offset9(uint16_t raw_instruction);

/**
 * @brief Returns the sign-extended 11-bit PC offset.
 */
int16_t get_signed_offset11(uint16_t raw_instruction);

/**
 * @brief Returns the sign-extended 6-bit offset.
 */
int16_t get_signed_offset6(uint16_t raw_instruction);

/**
 * @brief Extracts the base register used in control/data instructions.
 */
uint8_t get_base_r(uint16_t raw_instruction);

/**
 * @brief Extracts the 8-bit TRAP vector.
 */
uint8_t get_trap_vector8(uint16_t raw_instruction);

/**
 * @brief Returns true if the BR instruction will branch on negative.
 */
bool branch_on_n(uint16_t raw_instruction);

/**
 * @brief Returns true if the BR instruction will branch on zero.
 */
bool branch_on_z(uint16_t raw_instruction);

/**
 * @brief Returns true if the BR instruction will branch on positive.
 */
bool branch_on_p(uint16_t raw_instruction);

/**
 * @brief Returns true if the instruction is a JSR (not JSRR).
 */
bool is_jsr(uint16_t raw_instruction);

/**
 * @brief Returns the raw instruction unchanged.
 */
uint16_t get_raw_value(uint16_t raw_instruction);

} // namespace decoder

} // namespace lc3

