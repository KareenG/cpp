#pragma once

#include "mt/thread_safe_priority_queue.hpp"

namespace mt {

template<typename T, typename Compare>
void ThreadSafePriorityQueue<T, Compare>::enqueue(const T& val)
{
    std::lock_guard<std::mutex> lock(mtx_);
    queue_.push(val);
    cv_.notify_one();
}

template<typename T, typename Compare>
void ThreadSafePriorityQueue<T, Compare>::enqueue(T&& val)
{
    std::lock_guard<std::mutex> lock(mtx_);
    queue_.push(std::move(val));
    cv_.notify_one();
}

template<typename T, typename Compare>
void ThreadSafePriorityQueue<T, Compare>::dequeue(T& out)
{
    std::unique_lock<std::mutex> lock(mtx_);
    cv_.wait(lock, [this] { return !queue_.empty(); });
    out = std::move(const_cast<T&>(queue_.top()));
    queue_.pop();
}

template<typename T, typename Compare>
bool ThreadSafePriorityQueue<T, Compare>::empty() const noexcept
{
    std::lock_guard<std::mutex> lock(mtx_);
    return queue_.empty();
}

template<typename T, typename Compare>
std::size_t ThreadSafePriorityQueue<T, Compare>::size() const noexcept
{
    std::lock_guard<std::mutex> lock(mtx_);
    return queue_.size();
}

} // namespace mt