#pragma once

#include <queue>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <cstddef>

namespace mt {

/**
 * @brief A thread-safe blocking priority queue.
 *
 * Supports blocking enqueue and dequeue operations while maintaining a priority order.
 * Elements with higher priority are dequeued first.
 *
 * @tparam T Element type
 * @tparam Compare Comparator to define priority (default: std::less<T> for max-heap)
 */
template<typename T, typename Compare = std::less<T>>
class ThreadSafePriorityQueue {
public:
    ThreadSafePriorityQueue() = default;
    ~ThreadSafePriorityQueue() noexcept = default;

    ThreadSafePriorityQueue(const ThreadSafePriorityQueue&) = delete;
    ThreadSafePriorityQueue& operator=(const ThreadSafePriorityQueue&) = delete;

    ThreadSafePriorityQueue(ThreadSafePriorityQueue&&) noexcept = default;
    ThreadSafePriorityQueue& operator=(ThreadSafePriorityQueue&&) noexcept = default;

    /**
     * @brief Enqueue a copy of an element into the queue.
     * @param val Element to enqueue.
     */
    void enqueue(const T& val);

    /**
     * @brief Enqueue a moved element into the queue.
     * @param val Element to move into the queue.
     */
    void enqueue(T&& val);

    /**
     * @brief Dequeue the highest-priority element.
     * @param out Output reference to store dequeued element.
     */
    void dequeue(T& out);

    /**
     * @brief Check if the queue is empty.
     * @return true if empty, false otherwise.
     */
    bool empty() const noexcept;

    /**
     * @brief Get the number of elements in the queue.
     * @return Size of the queue.
     */
    std::size_t size() const noexcept;

private:
    mutable std::mutex mtx_;
    std::condition_variable cv_;
    std::priority_queue<T, std::vector<T>, Compare> queue_;
};

} // namespace mt

#include "mt/thread_safe_priority_queue.inl"
