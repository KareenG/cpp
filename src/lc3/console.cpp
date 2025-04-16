#include <unistd.h> // for read()

#include "lc3/console.hpp"

namespace lc3 {

Console::Console(std::ostream& os, std::istream& is)
: os_{os}
, is_{is}
{
}

void Console::read_char_no_echo(Registers& reg)
{
#ifdef BF_DEBUG
    char ch;
    // Skip over any leftover newlines in input stream
    while (is_.peek() == '\n') {
        is_.get();
    }
    os_.flush();

    is_ >> std::noskipws >> ch;  // Don't skip whitespace
    os_.flush();

    reg.write(RegisterIndex::R0, static_cast<uint16_t>(ch), false);
#else
    char ch;
    ssize_t result = read(STDIN_FILENO, &ch, 1);
    if (result > 0) {
        reg.write(RegisterIndex::R0, static_cast<uint16_t>(ch), false);
    }
#endif
}

void Console::write_char(const Registers& reg)
{
    char ch = static_cast<char>(reg.read(RegisterIndex::R0) & 0x00FF);
    if (ch != '\0') {
        os_ << ch;
        os_.flush();
    }
}

void Console::write_string_from_memory(const Registers& reg, const Memory& memory)
{
    uint16_t addr = reg.read(RegisterIndex::R0);
    uint16_t val = memory.read(addr);

    while ((val & 0xFF) != 0) {  // Only check lower byte for null terminator
        char ch = static_cast<char>(val & 0xFF);  // lower byte only
        os_ << ch;
        addr++;
        val = memory.read(addr);
    }
    
    os_.flush();
}

void Console::prompt_and_read_char(Registers& reg)
{
#ifdef BF_DEBUG
    os_ << "Enter a character: ";
    os_.flush();

    char ch;
    is_.get(ch);
    reg.write(RegisterIndex::R0, static_cast<uint16_t>(ch), false);
    os_ << ch << '\n';
    os_.flush();
#else
    char ch;
    // Skip any leftover newline characters
    while (is_.peek() == '\n') {
        is_.get();
    }
    os_.flush();

    is_ >> std::noskipws >> ch;
    os_.flush();

    reg.write(RegisterIndex::R0, static_cast<uint16_t>(ch), false);
#endif
}

} // namespace lc3
