#include <iostream>
#include <string>
#include "palantir/message_destination/console_out.hpp"

namespace palantir {

ConsoleOutput::ConsoleOutput(std::ostream& output)
: output_stream_{output}
{
}

void ConsoleOutput::send_message(const std::string& message)
{
    output_stream_ << message << '\n';
}

} // namespace palantir
