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
    /**
     * @brief Disables input buffering
     * 
     */
    TerminalIO();

    /**
     * @brief Restores input buffering
     * 
     */
    ~TerminalIO();

    TerminalIO(const TerminalIO&) = delete;
    TerminalIO& operator=(const TerminalIO&) = delete;

private:
    /**
     * @brief Saved original terminal settings
     * 
     */
    termios original_;
};

} // namespace lc3

