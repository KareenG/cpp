#pragma once

#include "mt/queue.hpp"

namespace mt::details {

/**
 * @brief Internal-only access class to privileged methods like enqueue_front.
 * 
 * @tparam T Element type of the BlockingBoundedQueue.
 */
template<typename T>
struct PrivilegedOps {
    using Queue = mt::BlockingBoundedQueue<T>;

    static void push_front(Queue& q, const T& val) {
        q.enqueue_front(val, mt::Secret<PrivilegedOps<T>>{});
    }

    static void push_front(Queue& q, T&& val) {
        q.enqueue_front(std::move(val), mt::Secret<PrivilegedOps<T>>{});
    }
};

} // namespace mt::details


namespace mt {

template<typename T, typename WithPrivilege, typename Container>
BlockingBoundedQueueImpl<T, WithPrivilege, Container>::BlockingBoundedQueueImpl(std::size_t capacity)
: capacity_{capacity}
{
}

template<typename T, typename WithPrivilege, typename Container>
void BlockingBoundedQueueImpl<T, WithPrivilege, Container>::enqueue(const T& new_val)
{
    std::unique_lock lock(mtx_);
    not_full_.wait(lock, [this] { return Container::size() < capacity_; });
    this->push_back(new_val);
    not_empty_.notify_all();
}

template<typename T, typename WithPrivilege, typename Container>
void BlockingBoundedQueueImpl<T, WithPrivilege, Container>::enqueue(T&& new_val)
{
    std::unique_lock lock(mtx_);
    not_full_.wait(lock, [this] { return Container::size() < capacity_; });
    this->push_back(std::move(new_val));
    not_empty_.notify_all();
}

template<typename T, typename WithPrivilege, typename Container>
void BlockingBoundedQueueImpl<T, WithPrivilege, Container>::enqueue_front(const T& new_val, Secret<WithPrivilege>)
{
    std::unique_lock lock(mtx_);
    not_full_.wait(lock, [this] { return Container::size() < capacity_; });
    this->push_front(new_val);
    not_empty_.notify_all();
}

template<typename T, typename WithPrivilege, typename Container>
void BlockingBoundedQueueImpl<T, WithPrivilege, Container>::enqueue_front(T&& new_val, Secret<WithPrivilege>)
{
    std::unique_lock lock(mtx_);
    not_full_.wait(lock, [this] { return Container::size() < capacity_; });
    this->push_front(std::move(new_val));
    not_empty_.notify_all();
}

template<typename T, typename WithPrivilege, typename Container>
void BlockingBoundedQueueImpl<T, WithPrivilege, Container>::dequeue(T& new_val)
{
    std::unique_lock lock(mtx_);
    not_empty_.wait(lock, [this] { return !Container::empty(); });
    new_val = std::move(this->front());
    this->pop_front();
    not_full_.notify_all();
}

template<typename T, typename WithPrivilege, typename Container>
bool BlockingBoundedQueueImpl<T, WithPrivilege, Container>::empty() const noexcept
{
    std::scoped_lock lock(mtx_);
    return Container::empty();
}

template<typename T, typename WithPrivilege, typename Container>
bool BlockingBoundedQueueImpl<T, WithPrivilege, Container>::full() const noexcept
{
    std::scoped_lock lock(mtx_);
    return Container::size() >= capacity_;
}

template<typename T, typename WithPrivilege, typename Container>
std::size_t BlockingBoundedQueueImpl<T, WithPrivilege, Container>::size() const noexcept
{
    std::scoped_lock lock(mtx_);
    return Container::size();
}

template<typename T, typename WithPrivilege, typename Container>
std::size_t BlockingBoundedQueueImpl<T, WithPrivilege, Container>::capacity() const noexcept
{
    return capacity_;
}

} // namespace mt


// #pragma once

// #include "mt/queue.hpp"

// namespace mt
// {

// template<typename T, typename Container>
// BlockingBoundedQueue<T, Container>::BlockingBoundedQueue(size_t capacity)
// : capacity_{capacity}
// {
// }

// template<typename T, typename Container>
// void BlockingBoundedQueue<T, Container>::enqueue(T const& new_val)
// {
//     std::unique_lock<std::mutex> lock(mtx_);
//     not_full_.wait(lock, [this] { return !(Container::size() == capacity_); });
//     this->push_back(new_val);
//     not_empty_.notify_all();
// }

// template<typename T, typename Container>
// void BlockingBoundedQueue<T, Container>::enqueue(T&& new_val)
// {
//     std::unique_lock<std::mutex> lock(mtx_);
//     not_full_.wait(lock, [this] { return !(Container::size() == capacity_); });
//     this->push_back(std::move(new_val));
//     not_empty_.notify_all();
// }

// template<typename T, typename Container>
// void BlockingBoundedQueue<T, Container>::enqueue_front(T const& new_val)
// {
//     std::unique_lock<std::mutex> lock(mtx_);
//     not_full_.wait(lock, [this] { return !(Container::size() == capacity_); });
//     this->push_front(new_val);
//     not_empty_.notify_all();
// }

// template<typename T, typename Container>
// void BlockingBoundedQueue<T, Container>::enqueue_front(T&& new_val)
// {
//     std::unique_lock<std::mutex> lock(mtx_);
//     not_full_.wait(lock, [this] { return !(Container::size() == capacity_); });
//     this->push_front(std::move(new_val));
//     not_empty_.notify_all();
// }

// // template<typename T, typename Container>
// // void BlockingBoundedQueue<T, Container>::dequeue(T& new_val)
// // {
// //     std::unique_lock<std::mutex> lock(mtx_);
// //     not_empty_.wait(lock, [this] { return !(Container::empty()); });
// //     new_val = this->front();
// //     this->pop();
// //     not_full_.notify_all();
// // }
// template<typename T, typename Container>
// void BlockingBoundedQueue<T, Container>::dequeue(T& new_val)
// {
//     std::unique_lock<std::mutex> lock(mtx_);
//     not_empty_.wait(lock, [this] { return !(Container::empty()); });
//     new_val = this->front();
//     this->pop_front();
//     not_full_.notify_all();
// }

// template<typename T, typename Container>
// bool BlockingBoundedQueue<T, Container>::empty() const noexcept
// {
//     std::unique_lock<std::mutex> lock(mtx_);
//     return Container::empty();
// }

// template<typename T, typename Container>
// bool BlockingBoundedQueue<T, Container>::full() const noexcept
// {
//     return size() == capacity_;
// }

// template<typename T, typename Container>
// size_t BlockingBoundedQueue<T, Container>::size() const noexcept
// {
//     std::unique_lock<std::mutex> lock(mtx_);
//     return Container::size();
// }

// template<typename T, typename Container>
// size_t BlockingBoundedQueue<T, Container>::capacity() const noexcept
// {
//     return capacity_;
// }

// } // namespace mt