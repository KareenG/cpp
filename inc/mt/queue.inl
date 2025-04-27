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
    full_.wait(lock, [this] { return !(this->full()); });
    this->push(new_val);
    empty_.notify_all();
}

template<typename T, typename Container>
void BlockingBoundedQueue<T, Container>::enqueue(T&& new_val)
{
    std::unique_lock<std::mutex> lock(mtx_);
    full_.wait(lock, [this] { return !(this->full()); });
    this->push(std::move(new_val));
    empty_.notify_all();
}

template<typename T, typename Container>
void BlockingBoundedQueue<T, Container>::dequeue(T& new_val)
{
    std::unique_lock<std::mutex> lock(mtx_);
    empty_.wait(lock, [this] { return !(this->empty()); });
    new_val = this->front();
    this->pop();
    full_.notify_all();
}

template<typename T, typename Container>
bool BlockingBoundedQueue<T, Container>::empty()
{
    return Container::empty();
}

template<typename T, typename Container>
bool BlockingBoundedQueue<T, Container>::full()
{
    return Container::size() >= capacity_;
}

template<typename T, typename Container>
size_t BlockingBoundedQueue<T, Container>::size()
{
    return Container::size();
}

template<typename T, typename Container>
size_t BlockingBoundedQueue<T, Container>::capacity()
{
    return capacity_;
}

} // namespace mt
