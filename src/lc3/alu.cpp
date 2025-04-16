#include <unordered_map>
#include <functional>
#include <cassert>

#include "lc3/alu.hpp"

namespace lc3 {

namespace ALU {

using AluFunc = std::function<Word(Word, Word)>;

static std::unordered_map<OpCode, AluFunc> make_operation_map() {
    return {
        { OpCode::ADD, [](Word a, Word b) {
            return static_cast<Word>(a + b);
        }},
        { OpCode::AND, [](Word a, Word b) {
            return static_cast<Word>(a & b);
        }},
        { OpCode::NOT, [](Word a, Word) {
            return static_cast<Word>(~a);
        }}
    };
}

static const std::unordered_map<OpCode, AluFunc> operation_map_ = make_operation_map();

uint16_t execute(OpCode opcode, Word lhs, Word rhs)
{
    std::unordered_map<OpCode, AluFunc>::const_iterator it = operation_map_.find(opcode);
    assert(it != operation_map_.end() && "Unsupported ALU operation");
    return it->second(lhs, rhs);
}

} // namespace ALU

} // namespace lc3
