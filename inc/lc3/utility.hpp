#pragma once

#include "lc3/consts_and_sizes.hpp"

namespace lc3 {

/**
 * @brief Checks if the host machine is little-endian.
 *
 * @return true if the system is little-endian, false otherwise.
 */
bool is_little_endian() noexcept;

/**
 * @brief Converts a 16-bit LC-3 word from big-endian to host byte order.
 *
 * Swaps the byte order only on little-endian hosts. On big-endian systems,
 * this function returns the input unchanged.
 *
 * @param value The 16-bit word to convert.
 * @return Word in host-endian format.
 */
Word from_big_endian(Word value) noexcept;

} // namespace lc3
