#pragma once

#include <type_traits>
#include <cstddef>
#include <queue>
#include <condition_variable>
#include <mutex>

/**
 * @brief A thread-safe blocking bounded queue with fixed capacity.
 * 
 * @tparam T Type of elements stored in the queue.
 * @tparam Container Container type to store elements. Must behave like FIFO (default: std::deque<T>).
 * 
 * Internally, it inherits from the container type (default std::queue<T>).
 * 
 * @details Private Members
 * - size_t capacity_: Maximum capacity of the queue.
 * - std::mutex mtx_: Mutex to synchronize access to the queue.
 * - std::condition_variable full_: Condition variable to block on full queue during enqueue.
 * - std::condition_variable empty_: Condition variable to block on empty queue during dequeue.
 */
namespace mt
{

// Forward declaration of internal privilege logic
namespace details {
    template<typename T>
    struct PrivilegedOps;
}

// Grants access to privileged operations
template<typename WithPrivilege>
class Secret {
private:
    friend WithPrivilege;
    Secret() = default;
};

/**
 * @brief A thread-safe blocking bounded queue with fixed capacity.
 * 
 * @tparam T Type of elements stored in the queue.
 * @tparam WithPrivilege Internal class allowed to call enqueue_front.
 * @tparam Container Container type to store elements. Must behave like FIFO (default: std::deque<T>).
 */
template<typename T, typename WithPrivilege, typename Container = std::deque<T>>
class BlockingBoundedQueueImpl : private Container {
public:
    // Cache-aware default capacity: 32 blocks of 64 bytes each
    inline static constexpr std::size_t k_default_block_size_bytes = 64;
    inline static constexpr std::size_t k_default_block_count = 32;
    inline static constexpr std::size_t k_default_capacity =
        (k_default_block_size_bytes / sizeof(T)) * k_default_block_count;

    /**
     * @brief Construct a BlockingBoundedQueue with a given capacity.
     * 
     * @param initial_capacity Maximum number of elements the queue can hold.
     */
    explicit BlockingBoundedQueueImpl(std::size_t initial_capacity = k_default_capacity);

    ~BlockingBoundedQueueImpl() noexcept = default;

    BlockingBoundedQueueImpl(BlockingBoundedQueueImpl const& other) = delete;
    BlockingBoundedQueueImpl(BlockingBoundedQueueImpl&& other) = default;

    BlockingBoundedQueueImpl& operator=(BlockingBoundedQueueImpl const& other) = delete;
    BlockingBoundedQueueImpl& operator=(BlockingBoundedQueueImpl&& other) = default;

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
    bool empty() const noexcept;

    /**
     * @brief Check if the queue is full.
     * 
     * @return true if full, false otherwise.
     */
    bool full() const noexcept;

    /**
     * @brief Get the current number of elements.
     * 
     * @return Current size of the queue.
     */
    std::size_t size() const noexcept;

    /**
     * @brief Get the maximum capacity of the queue.
     * 
     * @return Maximum number of elements the queue can hold.
     */
    std::size_t capacity() const noexcept;

private:
    /**
     * @brief Enqueue a copy of an element at the front of the deque. Blocks if full.
     * 
     * @param new_val The value to enqueue at the front.
     */
    void enqueue_front(T const& new_val, Secret<WithPrivilege>);

    /**
     * @brief Enqueue a moved element at the front of the deque. Blocks if full.
     * 
     * @param new_val The value to move and enqueue at the front.
     */
    void enqueue_front(T&& new_val, Secret<WithPrivilege>);
    friend WithPrivilege;

private:
    std::size_t capacity_;
    mutable std::mutex mtx_;
    std::condition_variable not_full_;
    std::condition_variable not_empty_;
};

/**
 * @brief Public-facing alias. The user only sees this clean name.
 * 
 * @tparam T Element type.
 */
template<typename T, typename Container = std::deque<T>>
using BlockingBoundedQueue = BlockingBoundedQueueImpl<T, details::PrivilegedOps<T>, Container>;

} // namespace mt

#include "mt/queue.inl"
