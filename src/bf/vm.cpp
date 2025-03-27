#include "bf/vm.hpp"

namespace bf {

VM::VM(Memory& memory ,Program& program, Console& console)
: memory_{memory}
, program_{program}
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