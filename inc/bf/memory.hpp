#pragma once

#include <vector>
#include <stddef.h>
#include <cstdint>

#include "bf/mem_arg_types.hpp"

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
     * @brief Default destructor.
     */
    ~Memory() = default;

    /**
     * @brief Default copy constructor.
     */
    Memory(Memory const& other) = default;

    /**
     * @brief Default copy assignment operator.
     */
    Memory& operator=(Memory const& other) = default;

    /**
     * @brief Reads the byte at the current pointer position.
     * 
     * @return int The value at the current pointer position.
     */
    CellType read();

    /**
     * @brief Writes a byte to the current pointer position.
     *
     * @param c The byte to write to the memory tape.
     */
    void write(CellType c);

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

#ifdef BF_DEBUG
    CellType operator[](Index index) const;
#endif
    // CellType operator[](Index index) const;
private:
    std::vector<CellType> tape_;
    Index pointer_;
};

} // namespace bf