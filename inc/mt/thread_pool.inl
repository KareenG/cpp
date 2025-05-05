#pragma once

#include <thread>
#include <vector>

#include "mt/thread_pool.hpp"

namespace mt
{

template<typename F, typename SequenceContainer>
ThreadPool<F, SequenceContainer>::ThreadPool(size_t num_threads, size_t initial_capacity)
: tasks_{initial_capacity}
, worker_([this]() {worker_function();}, num_threads)
, shutdown_called_{false}
{
}

template<typename F, typename SequenceContainer>
void ThreadPool<F, SequenceContainer>::submit(F&& task)
{
    if (!shutdown_called_.load(std::memory_order_acquire)) {
        tasks_.enqueue(std::move(task));
    }
}

template<typename F, typename SequenceContainer>
void ThreadPool<F, SequenceContainer>::shutdown_graceful() {
    shutdown_called_ = true;

    for (size_t i = 0; i < workers(); ++i) {
        tasks_.enqueue(F{}); // poison pills
    }

    worker_.shutdown_graceful();
}


template<typename F, typename SequenceContainer>
void ThreadPool<F, SequenceContainer>::shutdown_immediate()
{
    shutdown_called_ = true;
    for (size_t i = 0; i < workers(); ++i) {
        tasks_.enqueue_front(F{});
    }
    worker_.shutdown_immediate();
}


template<typename F, typename SequenceContainer>
void ThreadPool<F, SequenceContainer>::add_workers(size_t n)
{
    worker_.add_workers(n);
}

template<typename F, typename SequenceContainer>
void ThreadPool<F, SequenceContainer>::remove_workers(size_t n)
{
    for (size_t i = 0; i < n; ++i) {
        tasks_.enqueue(F{});
    }
    worker_.remove_workers(n);
}

template<typename F, typename SequenceContainer>
size_t ThreadPool<F, SequenceContainer>::workers() const
{
    return worker_.workers();
}

template<typename F, typename SequenceContainer>
inline void ThreadPool<F, SequenceContainer>::worker_function()
{
    for (;;) {
        F task;
        tasks_.dequeue(task);

        if (!task) {
            break;
        }
        
        try {
            task();
        } catch (const std::exception& e) {
            std::osyncstream(std::cerr) << "[ThreadWorker] Task exception: " << e.what() << '\n';
        } catch (...) {
            assert(false && "[ThreadWorker] Unknown exception");
        }
    }
}

} // namespace mt

