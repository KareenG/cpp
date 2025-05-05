#pragma once

#include "mt/queue.hpp"

namespace mt
{

template<typename T, typename Container>
BlockingBoundedQueue<T, Container>::BlockingBoundedQueue(size_t capacity)
: capacity_{capacity}
{
}

template<typename T, typename Container>
void BlockingBoundedQueue<T, Container>::enqueue(T const& new_val)
{
    std::unique_lock<std::mutex> lock(mtx_);
    not_full_.wait(lock, [this] { return !(Container::size() == capacity_); });
    this->push_back(new_val);
    not_empty_.notify_all();
}

template<typename T, typename Container>
void BlockingBoundedQueue<T, Container>::enqueue(T&& new_val)
{
    std::unique_lock<std::mutex> lock(mtx_);
    not_full_.wait(lock, [this] { return !(Container::size() == capacity_); });
    this->push_back(std::move(new_val));
    not_empty_.notify_all();
}

template<typename T, typename Container>
void BlockingBoundedQueue<T, Container>::enqueue_front(T const& new_val)
{
    std::unique_lock<std::mutex> lock(mtx_);
    not_full_.wait(lock, [this] { return !(Container::size() == capacity_); });
    this->push_front(new_val);
    not_empty_.notify_all();
}

template<typename T, typename Container>
void BlockingBoundedQueue<T, Container>::enqueue_front(T&& new_val)
{
    std::unique_lock<std::mutex> lock(mtx_);
    not_full_.wait(lock, [this] { return !(Container::size() == capacity_); });
    this->push_front(std::move(new_val));
    not_empty_.notify_all();
}

// template<typename T, typename Container>
// void BlockingBoundedQueue<T, Container>::dequeue(T& new_val)
// {
//     std::unique_lock<std::mutex> lock(mtx_);
//     not_empty_.wait(lock, [this] { return !(Container::empty()); });
//     new_val = this->front();
//     this->pop();
//     not_full_.notify_all();
// }
template<typename T, typename Container>
void BlockingBoundedQueue<T, Container>::dequeue(T& new_val)
{
    std::unique_lock<std::mutex> lock(mtx_);
    not_empty_.wait(lock, [this] { return !(Container::empty()); });
    new_val = this->front();
    this->pop_front();
    not_full_.notify_all();
}

template<typename T, typename Container>
bool BlockingBoundedQueue<T, Container>::empty() const noexcept
{
    std::unique_lock<std::mutex> lock(mtx_);
    return Container::empty();
}

template<typename T, typename Container>
bool BlockingBoundedQueue<T, Container>::full() const noexcept
{
    return size() == capacity_;
}

template<typename T, typename Container>
size_t BlockingBoundedQueue<T, Container>::size() const noexcept
{
    std::unique_lock<std::mutex> lock(mtx_);
    return Container::size();
}

template<typename T, typename Container>
size_t BlockingBoundedQueue<T, Container>::capacity() const noexcept
{
    return capacity_;
}

} // namespace mt
