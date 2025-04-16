#include "lc3/terminal_io.hpp"

namespace lc3 {

TerminalIO::TerminalIO()
{
    tcgetattr(STDIN_FILENO, &original_);
    termios raw = original_;
    raw.c_lflag &= ~(ICANON | ECHO);  // Disable canonical input and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

TerminalIO::~TerminalIO()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &original_);
}

} // namespace lc3
