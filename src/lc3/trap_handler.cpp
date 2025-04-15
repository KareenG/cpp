#include "lc3/trap_handler.hpp"

namespace lc3 {

TrapHandler::TrapHandler(Console& console) noexcept
: console_{console}
{
}

void TrapHandler::handle(uint8_t trap_vector, Registers& regs, const Memory& memory, bool& running) noexcept
{
    switch(trap_vector) {
        case 0x20: 
            console_.get_c(regs); 
            break;
        case 0x21: 
            console_.out(regs); 
            break;
        case 0x22: 
            console_.put_s(regs, memory); 
            break;
        case 0x23: 
            console_.in(regs); 
            break;
        case 0x25: 
            running = false;
            break;
        default:
            assert(false && "Unhandled TRAP vector");
            break;
    }
}

} // namespace lc3
