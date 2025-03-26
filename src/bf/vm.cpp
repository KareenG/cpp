#include "bf/vm.hpp"

namespace bf {

// VM::VM(Program& code)
// : memory_{}
// , program_{code}
// , console_{}
// , microcode_{memory_, program_, console_}
// {
// }

VM::VM(const std::vector<OpCode>& opcodes)
: memory_{}
, program_{opcodes}
, console_{}
, microcode_{memory_, program_, console_}
{
}

VM::VM(const std::vector<OpCode>& opcodes, Console& console)
: memory_{}
, program_{opcodes}
, console_{console}
, microcode_{memory_, program_, console_}
{
}

void VM::run()
{
  while(!program_.is_done()) {
    OpCode instruction = program_.fetch_current();
    microcode_.execute(instruction);
  }
}

} // namespace bf