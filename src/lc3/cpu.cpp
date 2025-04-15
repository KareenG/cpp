#include <cassert>

#include "lc3/cpu.hpp"
#include "lc3/alu.hpp"

namespace lc3
{
    
CPU::CPU(Memory& mem, Console& console)
: pc_{mem.get_program_start()}
, memory_{mem}
, reg_file_{}
, trap_handler_{console}
{
}

void CPU::run() noexcept
{
    bool running = true;
    while(running) {
        uint16_t instruction = fetch_instruction();
        execute_instruction(instruction, running);
    }
}

uint16_t CPU::fetch_instruction() noexcept
{
    uint16_t current_pc = pc_.get();    // this is PC pointing to current instruction
    uint16_t instruction = memory_.read(current_pc);
    pc_.increment();                    // PC is now PC + 1
    return instruction;
}

void CPU::execute_instruction(uint16_t raw_inst, bool& running) noexcept
{
    OpCode op = decoder::get_opcode(raw_inst);
    std::unordered_map<OpCode, InstructionCategory>::const_iterator it = opcode_category.find(op);
    assert(it != opcode_category.end() && "Unknown opcode encountered");

    switch(it->second) {
        case InstructionCategory::Operate:
            handle_operate_instruction(op, raw_inst);
            break;
        case InstructionCategory::DataMovement:
            handle_data_movement_instruction(op, raw_inst);
            break;
        case InstructionCategory::Control:
            handle_control_instruction(op, raw_inst);
            break;
        case InstructionCategory::Trap:
            handle_trap_instruction(raw_inst, running);
            break;
    }
}

void CPU::handle_operate_instruction(OpCode op, uint16_t raw_inst) noexcept
{
    const uint8_t dr = decoder::get_dr(raw_inst);
    const uint8_t sr1 = decoder::get_sr1(raw_inst);
    const bool is_imm = decoder::is_immediate_mode(raw_inst);

    uint16_t lhs = reg_file_.read(sr1);
    uint16_t rhs = 0;

    switch(op) {
        case OpCode::ADD:
        case OpCode::AND:
            if (is_imm) {
                rhs = static_cast<uint16_t>(decoder::get_signed_imm5(raw_inst));
            } else {
                const uint8_t sr2 = decoder::get_sr2(raw_inst);
                rhs = reg_file_.read(sr2);
            }
            reg_file_.write(dr, ALU::execute(op, lhs, rhs));
            break;

        case OpCode::NOT:
            reg_file_.write(dr, ALU::execute(op, lhs, 0)); // rhs unused
            break;

        default:
            break;
    }
}

void CPU::handle_data_movement_instruction(OpCode op, uint16_t raw_inst) noexcept
{
    uint8_t dr;
    uint8_t sr;
    uint8_t base_r;
    int16_t offset;

    switch(op) {
        case OpCode::LD: 
            dr = decoder::get_dr(raw_inst);
            offset = decoder::get_signed_offset9(raw_inst);
            reg_file_.write(dr, memory_.read(pc_.get() + offset));
            break;
        
        case OpCode::ST: 
            sr = decoder::get_sr(raw_inst);
            offset = decoder::get_signed_offset9(raw_inst);
            memory_.write(pc_.get() + offset, reg_file_.read(sr));
            break;
        
        case OpCode::LDR: 
            dr = decoder::get_dr(raw_inst);
            base_r = decoder::get_base_r(raw_inst);
            offset = decoder::get_signed_offset6(raw_inst);
            reg_file_.write(dr, memory_.read(reg_file_.read(base_r) + offset));
            break;

        case OpCode::STR: 
            sr = decoder::get_sr(raw_inst);
            base_r = decoder::get_base_r(raw_inst);
            offset = decoder::get_signed_offset6(raw_inst);
            memory_.write(reg_file_.read(base_r) + offset, reg_file_.read(sr));
            break;
        
        case OpCode::LDI: 
            dr = decoder::get_dr(raw_inst);
            offset = decoder::get_signed_offset9(raw_inst);
            reg_file_.write(dr, memory_.read(memory_.read(pc_.get() + offset)));
            break;
        
        case OpCode::STI: 
            sr = decoder::get_sr(raw_inst);
            offset = decoder::get_signed_offset9(raw_inst);
            memory_.write(memory_.read(pc_.get() + offset), reg_file_.read(sr));
            break;
        
        case OpCode::LEA:
            dr = decoder::get_dr(raw_inst);
            offset = decoder::get_signed_offset9(raw_inst);
            reg_file_.write(dr, pc_.get() + offset);
            break;

        default:
            break; 
    }
}

void CPU::handle_control_instruction(OpCode op, uint16_t raw_inst) noexcept
{
    int16_t offset;
    ConditionFlag current_flag;
    bool take_branch;
    uint8_t base_r;

    switch(op) {
        case OpCode::BR:
            offset = decoder::get_signed_offset9(raw_inst);
            current_flag = reg_file_.get_condition_flag();

            take_branch =
                (decoder::branch_on_n(raw_inst) && current_flag == ConditionFlag::NEGATIVE) ||
                (decoder::branch_on_z(raw_inst) && current_flag == ConditionFlag::ZERO)     ||
                (decoder::branch_on_p(raw_inst) && current_flag == ConditionFlag::POSITIVE);

            if (take_branch) {
                pc_.increment(offset);
            }
            break;
        
        case OpCode::JMP:   // handles both JMP and RET, RET is just JMP BR=R7
            base_r = decoder::get_base_r(raw_inst);
            pc_.set(reg_file_.read(base_r));
            break;
        
        case OpCode::JSR:   // handles both JSR and JSRR
            reg_file_.write(7, pc_.get(), false);
            if (decoder::is_jsr(raw_inst)) {
                // JSR → PC-relative jump
                offset = decoder::get_signed_offset11(raw_inst);
                pc_.increment(offset);
            } else {
                // JSRR → Register jump
                base_r = decoder::get_base_r(raw_inst);
                pc_.set(reg_file_.read(base_r));
            }
            break;

        default:
            break; 
    }
}

void CPU::handle_trap_instruction(uint16_t raw_inst, bool& running) noexcept
{
    uint8_t trap_vector = decoder::get_trap_vector8(raw_inst);
    trap_handler_.handle(trap_vector, reg_file_, memory_, running);
}

} // namespace lc3