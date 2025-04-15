#include <unordered_map>
#include <functional>
#include <cassert>

#include "lc3/alu.hpp"

namespace lc3 {

namespace ALU {

using AluFunc = std::function<uint16_t(uint16_t, uint16_t)>;

static std::unordered_map<OpCode, AluFunc> make_operation_map() {
    return {
        { OpCode::ADD, [](uint16_t a, uint16_t b) {
            return static_cast<uint16_t>(a + b);
        }},
        { OpCode::AND, [](uint16_t a, uint16_t b) {
            return static_cast<uint16_t>(a & b);
        }},
        { OpCode::NOT, [](uint16_t a, uint16_t) {
            return static_cast<uint16_t>(~a);
        }}
    };
}

static const std::unordered_map<OpCode, AluFunc> operation_map_ = make_operation_map();

uint16_t execute(OpCode opcode, uint16_t lhs, uint16_t rhs)
{
    std::unordered_map<OpCode, AluFunc>::const_iterator it = operation_map_.find(opcode);
    assert(it != operation_map_.end() && "Unsupported ALU operation");
    return it->second(lhs, rhs);
}

} // namespace ALU

} // namespace lc3
