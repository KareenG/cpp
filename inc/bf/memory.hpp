#pragma once

#include <vector>
#include <stddef.h>
#include <cstdint>

namespace bf {

/**
 * @brief Represents memory management for a Brainfudg-like interpreter.
 * 
 * Members:
 * - std::vector<uint8_t> tape_: The memory tape where data is stored.
 * - size_t pointer_: The current position of the data pointer on the tape.
 */
class Memory {
public:
    /**
     * @brief Constructs a Memory object with a specified tape size.
     *
     * @param size The size of the memory tape. Default is 30000.
     * 
     * @note Initializes the tape with a given size, setting all cells to zero and the pointer to the start.
     */
    Memory(size_t size = 30000);

    /**
     * @brief Reads the byte at the current pointer position.
     * 
     * @return int The value at the current pointer position.
     */
    int read();

    /**
     * @brief Writes a byte to the current pointer position.
     *
     * @param c The byte to write to the memory tape.
     */
    void write(uint8_t c);

    /**
     * @brief Moves the data pointer one position to the left.
     *
     * Ensures that the pointer does not move past the beginning of the tape.
     */
    void move_left();

    /**
     * @brief Moves the data pointer one position to the right.
     *
     * Ensures that the pointer does not move beyond the end of the tape.
     */
    void move_right();

private:
    std::vector<uint8_t> tape_;
    size_t pointer_;
};

} // namespace bf