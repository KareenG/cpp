#include <cassert>

#include "lc3/control_unit.hpp"
#include "lc3/alu.hpp"
#include "lc3/decoder.hpp"
#include "lc3/lc3_exceptions.hpp"
#include "lc3/cpu.hpp"  // Must be included in the .cpp to access CPU members

namespace lc3 {

ControlUnit::ControlUnit(CPU& cpu)
: cpu_{cpu}
{  
    initialize_maps();
}

void ControlUnit::initialize_maps()
{
    operate_map();
    initialize_data_movement_map();
    initialize_control_map();
    initialize_trap_map();
    initialize_category_handler_map();
}

std::function<void()> ControlUnit::get_handler(Word instruction)
{
    assert(!category_handler_map_.empty() && "Category handler map must be initialized");

    OpCode op = decoder::get_opcode(instruction);

    auto cat_it = opcode_category.find(op);
    if (cat_it == opcode_category.end()) {
        throw InvalidOpcodeException(static_cast<Word>(op));
    }

    InstructionCategory category = cat_it->second;
    auto handler_it = category_handler_map_.find(category);
    assert(handler_it != category_handler_map_.end() && "Missing handler for instruction category");

    // Call the category lambda to return the actual handler
    return handler_it->second(cpu_, instruction);
}

void ControlUnit::initialize_category_handler_map()
{
    category_handler_map_ = {
        {
            InstructionCategory::Operate,
            [this](CPU& cpu, Word inst) -> std::function<void()> {
                OpCode op = decoder::get_opcode(inst);
                auto it = operate_map_.find(op);
                if (it == operate_map_.end()) {
                    throw InvalidOpcodeException(static_cast<Word>(op));
                }
                return [&, inst, handler = it->second]() { handler(cpu, inst); };
            }
        },
        {
            InstructionCategory::DataMovement,
            [this](CPU& cpu, Word inst) -> std::function<void()> {
                OpCode op = decoder::get_opcode(inst);
                auto it = data_movement_map_.find(op);
                if (it == data_movement_map_.end()) {
                    throw InvalidOpcodeException(static_cast<Word>(op));
                }
                return [&, inst, handler = it->second]() { handler(cpu, inst); };
            }
        },
        {
            InstructionCategory::Control,
            [this](CPU& cpu, Word inst) -> std::function<void()> {
                OpCode op = decoder::get_opcode(inst);
                auto it = control_map_.find(op);
                if (it == control_map_.end()) {
                    throw InvalidOpcodeException(static_cast<Word>(op));
                }
                return [&, inst, handler = it->second]() { handler(cpu, inst); };
            }
        },
        {
            InstructionCategory::Trap,
            [this](CPU& cpu, Word inst) -> std::function<void()> {
                OpCode op = decoder::get_opcode(inst);
                auto it = trap_map_.find(op);
                if (it == trap_map_.end()) {
                    throw InvalidOpcodeException(static_cast<Word>(op));
                }
                return [&, inst, handler = it->second]() { handler(cpu, inst); };
            }
        }
    };
}

void ControlUnit::operate_map()
{
    operate_map_ = {
        {OpCode::ADD, [](CPU& cpu, Word inst) {
            const RegisterIndex dr = decoder::get_dr(inst);
            const RegisterIndex sr1 = decoder::get_sr1(inst);
            const bool is_imm = decoder::is_immediate_mode(inst);
            Word lhs = cpu.reg_file_.read(sr1);
            Word rhs = is_imm ? static_cast<Word>(decoder::get_signed_imm5(inst))
                                  : cpu.reg_file_.read(decoder::get_sr2(inst));
            cpu.reg_file_.write(dr, ALU::execute(OpCode::ADD, lhs, rhs));
        }},
        {OpCode::AND, [](CPU& cpu, Word inst) {
            const RegisterIndex dr = decoder::get_dr(inst);
            const RegisterIndex sr1 = decoder::get_sr1(inst);
            const bool is_imm = decoder::is_immediate_mode(inst);
            Word lhs = cpu.reg_file_.read(sr1);
            Word rhs = is_imm ? static_cast<Word>(decoder::get_signed_imm5(inst))
                                  : cpu.reg_file_.read(decoder::get_sr2(inst));
            cpu.reg_file_.write(dr, ALU::execute(OpCode::AND, lhs, rhs));
        }},
        {OpCode::NOT, [](CPU& cpu, Word inst) {
            const RegisterIndex dr = decoder::get_dr(inst);
            const RegisterIndex sr1 = decoder::get_sr1(inst);
            cpu.reg_file_.write(dr, ALU::execute(OpCode::NOT, cpu.reg_file_.read(sr1), 0));
        }}
    };
}

void ControlUnit::initialize_data_movement_map()
{
    data_movement_map_ = {
        {OpCode::LD, [](CPU& cpu, Word inst) {
            RegisterIndex dr = decoder::get_dr(inst);
            int16_t offset = decoder::get_signed_offset9(inst);
            cpu.reg_file_.write(dr, cpu.memory_.read(cpu.pc_.get() + offset));
        }},
        {OpCode::LDR, [](CPU& cpu, Word inst) {
            RegisterIndex dr = decoder::get_dr(inst);
            RegisterIndex base_r = decoder::get_base_r(inst);
            int16_t offset = decoder::get_signed_offset6(inst);
            cpu.reg_file_.write(dr, cpu.memory_.read(cpu.reg_file_.read(base_r) + offset));
        }},
        {OpCode::LDI, [](CPU& cpu, Word inst) {
            RegisterIndex dr = decoder::get_dr(inst);
            int16_t offset = decoder::get_signed_offset9(inst);
            cpu.reg_file_.write(dr, cpu.memory_.read(cpu.memory_.read(cpu.pc_.get() + offset)));
        }},
        {OpCode::ST, [](CPU& cpu, Word inst) {
            RegisterIndex sr = decoder::get_sr(inst);
            int16_t offset = decoder::get_signed_offset9(inst);
            cpu.memory_.write(cpu.pc_.get() + offset, cpu.reg_file_.read(sr));
        }},
        {OpCode::STR, [](CPU& cpu, Word inst) {
            RegisterIndex sr = decoder::get_sr(inst);
            RegisterIndex base_r = decoder::get_base_r(inst);
            int16_t offset = decoder::get_signed_offset6(inst);
            cpu.memory_.write(cpu.reg_file_.read(base_r) + offset, cpu.reg_file_.read(sr));
        }},
        {OpCode::STI, [](CPU& cpu, Word inst) {
            RegisterIndex sr = decoder::get_sr(inst);
            int16_t offset = decoder::get_signed_offset9(inst);
            cpu.memory_.write(cpu.memory_.read(cpu.pc_.get() + offset), cpu.reg_file_.read(sr));
        }},
        {OpCode::LEA, [](CPU& cpu, Word inst) {
            RegisterIndex dr = decoder::get_dr(inst);
            int16_t offset = decoder::get_signed_offset9(inst);
            cpu.reg_file_.write(dr, cpu.pc_.get() + offset);
        }}
    };
}

void ControlUnit::initialize_control_map()
{
    control_map_ = {
        {OpCode::BR, [](CPU& cpu, Word inst) {
            int16_t offset = decoder::get_signed_offset9(inst);
            ConditionFlag flag = cpu.reg_file_.get_condition_flag();
            if ((decoder::branch_on_n(inst) && flag == ConditionFlag::NEGATIVE) ||
                (decoder::branch_on_z(inst) && flag == ConditionFlag::ZERO) ||
                (decoder::branch_on_p(inst) && flag == ConditionFlag::POSITIVE)) {
                cpu.pc_.increment(offset);
            }
        }},
        {OpCode::JMP, [](CPU& cpu, Word inst) {
            RegisterIndex base_r = decoder::get_base_r(inst);
            cpu.pc_.set(cpu.reg_file_.read(base_r));
        }},
        {OpCode::JSR, [](CPU& cpu, Word inst) {
            cpu.reg_file_.write(RegisterIndex::R7, cpu.pc_.get(), false);
            if (decoder::is_jsr(inst)) {
                cpu.pc_.increment(decoder::get_signed_offset11(inst));
            } else {
                RegisterIndex base_r = decoder::get_base_r(inst);
                cpu.pc_.set(cpu.reg_file_.read(base_r));
            }
        }}
    };
}

void ControlUnit::initialize_trap_map()
{
    trap_map_ = {
        {OpCode::TRAP, [](CPU& cpu, Word inst) {
            TrapVector trap_vector = decoder::get_trap_vector8(inst);
            cpu.trap_handler_.handle(trap_vector, cpu.reg_file_, cpu.memory_, cpu.is_running_);
        }}
    };
}

} // namespace lc3
