#include "bf/console.hpp"

namespace bf {

Console::Console(std::ostream& os, std::istream& is)
: os_(os)
, is_(is) 
{
}

CellType Console::input_char() 
{
    char c;
    is_.get(c);
    return c;
}

void Console::print_char(CellType c) 
{
    os_ << c;
}

}