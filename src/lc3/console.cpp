#include "lc3/console.hpp"

namespace lc3 {

Console::Console(std::ostream& os, std::istream& is)
: os_{os}
, is_{is}
{
}

void Console::get_c(Registers& reg)
{
    char ch;
    // Skip over any leftover newlines in input stream
    while (is_.peek() == '\n') {
        is_.get();
    }
    os_.flush();

    is_ >> std::noskipws >> ch;  // Don't skip whitespace
    os_.flush();

    reg.write(0, static_cast<uint16_t>(ch), false);
}

void Console::out(const Registers& reg)
{
    char ch = static_cast<char>(reg.read(0) & 0x00FF);
    if (ch != '\0') {
        os_ << ch;
        os_.flush();
    }
}

void Console::put_s(const Registers& reg, const Memory& memory)
{
    uint16_t addr = reg.read(0);
    uint16_t val = memory.read(addr);

    while ((val & 0xFF) != 0) {  // Only check lower byte for null terminator
        char ch = static_cast<char>(val & 0xFF);  // lower byte only
        os_ << ch;
        addr++;
        val = memory.read(addr);
    }
    
    os_.flush();
}

void Console::in(Registers& reg)
{
    os_ << "Enter a character: ";
    os_.flush();

    char ch;
    is_.get(ch);
    reg.write(0, static_cast<uint16_t>(ch), false);
    os_ << ch << '\n';
    os_.flush();
}

} // namespace lc3
