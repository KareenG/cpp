// #pragma once

// namespace lc3 {

// namespace terminal {

// /**
//  * @brief Disables input buffering and echo for immediate, raw character input.
//  *
//  * This sets the terminal to non-canonical mode, allowing input to be read
//  * without pressing Enter and suppressing input echo.
//  */
// void disable_input_buffering();

// /**
//  * @brief Restores the terminal's original input settings.
//  *
//  * This should be called before the program exits to restore user terminal behavior.
//  */
// void restore_input_buffering();

// } // namespace terminal

// } // namespace lc3

#pragma once

#include <termios.h>
#include <unistd.h>

namespace lc3 {

/**
 * @brief Manages terminal input buffering state using RAII.
 *
 * Disables canonical mode and echo on construction,
 * and restores the original terminal state on destruction.
 */
class TerminalIO {
public:
    TerminalIO();                         ///< Disables input buffering
    ~TerminalIO();                        ///< Restores input buffering

    TerminalIO(const TerminalIO&) = delete;
    TerminalIO& operator=(const TerminalIO&) = delete;

private:
    termios original_;                    ///< Saved original terminal settings
};

} // namespace lc3

