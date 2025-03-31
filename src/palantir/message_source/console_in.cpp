#include <iostream>
#include <string>
#include "palantir/message_source/console_in.hpp"

namespace palantir {

Console::Console(std::istream& input)
: input_stream_(input) 
{
}

std::string Console::get_message() 
{
    std::string line;
    std::getline(input_stream_, line);
    line.push_back('\n');
    return line;
}

bool Console::is_fully_processed() const 
{
    return input_stream_.eof();
}

} // namespace palantir
