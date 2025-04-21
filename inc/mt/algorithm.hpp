#pragma once

#include <vector>
#include <cstddef>

/**
 * @brief Multi-threaded algorithms for vector operations.
 *
 * This namespace contains utility functions that perform operations
 * such as maximum value search and sum computation using multiple threads.
 */
namespace mt
{

/**
 * @brief Finds the maximum value in a vector using multiple threads.
 *
 * Divides the vector into approximately equal chunks and launches a thread
 * for each chunk to compute its local maximum. After all threads complete,
 * the overall maximum is determined from the local maxima.
 *
 * @tparam T The value type of the vector elements (must support comparison).
 * @param arr The input vector to search.
 * @param num_thrd The number of threads to use. If 0, behavior is undefined and should be avoided.
 * @return The maximum value found in the vector.
 *
 * @throws std::invalid_argument If the input vector is empty or `num_thrd` is zero.
 */
template<typename T>
T find_max_using_thrds(const std::vector<T>& arr, size_t num_thrd = 0);

/**
 * @brief Calculates the sum of all elements in a vector using multiple threads.
 *
 * Splits the input vector into chunks, each processed by a separate thread
 * to calculate partial sums. The final result is the sum of all partial sums.
 *
 * @tparam T The value type of the vector elements (must support addition).
 * @param arr The input vector to sum.
 * @param num_thrd The number of threads to use. If 0, behavior is undefined and should be avoided.
 * @return The total sum of all elements in the vector.
 *
 * @throws std::invalid_argument If the input vector is empty or `num_thrd` is zero.
 */
template<typename T>
size_t calc_sum_using_thrds(const std::vector<T>& arr, size_t num_thrd = 0);

} // namespace mt

#include "mt/algorithm.inl"
