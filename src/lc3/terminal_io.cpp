// #include "lc3/terminal.hpp"

// #include <unistd.h>     // STDIN_FILENO
// #include <termios.h>    // struct termios

// namespace lc3 {

// namespace terminal {

// static struct termios original_tio;

// /**
//  * @brief Disables canonical mode and echo for raw character input.
//  */
// void disable_input_buffering()
// {
//     tcgetattr(STDIN_FILENO, &original_tio); // Save current settings
//     struct termios new_tio = original_tio;
//     new_tio.c_lflag &= ~ICANON & ~ECHO;
//     tcsetattr(STDIN_FILENO, TCSANOW, &new_tio); // Apply new settings
// }

// /**
//  * @brief Restores the terminal settings to what they were before disabling buffering.
//  */
// void restore_input_buffering()
// {
//     tcsetattr(STDIN_FILENO, TCSANOW, &original_tio);
// }

// } // namespace terminal

// } // namespace lc3


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
