#pragma once

#include <type_traits>
#include <cstddef>
#include <queue>
#include <condition_variable>
#include <mutex>

namespace mt
{

/**
 * @brief A thread-safe blocking bounded queue with fixed capacity.
 * 
 * @tparam T Type of elements stored in the queue.
 * @tparam Container Container type to store elements. Must behave like FIFO (default: std::queue<T>).
 * 
 * Internally, it inherits from the container type (default std::queue<T>).
 * 
 * @details Private Members
 * - size_t capacity_: Maximum capacity of the queue.
 * - std::mutex mtx_: Mutex to synchronize access to the queue.
 * - std::condition_variable full_: Condition variable to block on full queue during enqueue.
 * - std::condition_variable empty_: Condition variable to block on empty queue during dequeue.
 */
template<typename T, typename Container = std::queue<T>>
class BlockingBoundedQueue : private Container
{ 
    static_assert(
        std::is_same_v<Container, std::queue<T>>,
        "BlockingBoundedQueue requires a FIFO container like std::queue"
        );

public:
    /**
     * @brief Construct a BlockingBoundedQueue with a given capacity.
     * 
     * @param initial_size Maximum number of elements the queue can hold.
     */
    explicit BlockingBoundedQueue(size_t initial_size = 0);

    /**
     * @brief Enqueue a copy of an element into the queue. Blocks if full.
     * 
     * @param new_val The value to enqueue.
     */
    void enqueue(T const& new_val);

    /**
     * @brief Enqueue a moved element into the queue. Blocks if full.
     * 
     * @param new_val The value to move and enqueue.
     */
    void enqueue(T&& new_val);

    /**
     * @brief Dequeue an element from the queue. Blocks if empty.
     * 
     * @param new_val Reference to store the dequeued value.
     */
    void dequeue(T& new_val);

    /**
     * @brief Check if the queue is empty.
     * 
     * @return true if empty, false otherwise.
     */
    bool empty();

    /**
     * @brief Check if the queue is full.
     * 
     * @return true if full, false otherwise.
     */
    bool full();

    /**
     * @brief Get the current number of elements.
     * 
     * @return Current size of the queue.
     */
    size_t size();

    /**
     * @brief Get the maximum capacity of the queue.
     * 
     * @return Maximum number of elements the queue can hold.
     */
    size_t capacity();

private:
    size_t capacity_;
    std::mutex mtx_;
    std::condition_variable full_;
    std::condition_variable empty_;
};

} // namespace mt

#include "mt/queue.inl"
