# pragma once

#include <vector>
#include <cstdint>

namespace bf {

/**
 * @brief Type definition for a cell used in the Brainfuck program's memory tape.
 *
 * Defines the type of each cell in the memory tape of a Brainfuck interpreter.
 * uint8_t is used to limit each cell to a single unsigned byte, which is sufficient
 * for the typical range of values Brainfuck operates with (0-255).
 */
using CellType = uint8_t;

/**
 * @brief Type definition for indexing into a vector of CellType.
 *
 * Represents the type used for indexing into the memory tape of a Brainfuck interpreter.
 * This type is derived from the size type of a vector of CellType, ensuring that it can
 * correctly represent the range of valid indices for any size of memory tape.
 */
using Index = std::vector<CellType>::size_type;

}
