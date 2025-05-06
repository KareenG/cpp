#pragma once

#include <thread>
#include <vector>

#include "mt/thread_pool.hpp"

namespace mt
{

template< typename Task, typename SequenceContainer>
ThreadPool<Task, SequenceContainer>::ThreadPool(size_t num_threads, size_t initial_capacity)
: tasks_{initial_capacity}
, shutdown_called_{false}
, workers_([this]() {workers_function();}, num_threads)
{
}

template< typename Task, typename SequenceContainer>
void ThreadPool<Task, SequenceContainer>::submit(Task&& task)
{
    if (shutdown_called_.load(std::memory_order_acquire)) {
        throw std::runtime_error("Cannot submit more tasks: Thread pool is at shutdown");
    }
    tasks_.enqueue(std::move(task));
}

template< typename Task, typename SequenceContainer>
void ThreadPool<Task, SequenceContainer>::shutdown_graceful() {
    shutdown_called_ = true;

    for (size_t i = 0; i < workers(); ++i) {
        tasks_.enqueue(Task{}); // poison apples
    }

    workers_.shutdown_graceful();
}

template< typename Task, typename SequenceContainer>
void ThreadPool<Task, SequenceContainer>::shutdown_immediate()
{
    shutdown_called_ = true;
    for (size_t i = 0; i < workers(); ++i) {
        ThreadPoolPrivileged::enqueue_front(tasks_, Task{}); // poison apples
    }
    workers_.shutdown_immediate(); 
}

template< typename Task, typename SequenceContainer>
void ThreadPool<Task, SequenceContainer>::add_workers(size_t n)
{
    if (shutdown_called_.load(std::memory_order_acquire)) {
        throw std::runtime_error("Cannot add workers: Thread pool is at shutdown");
    }
    workers_.add_workers(n);
}

template< typename Task, typename SequenceContainer>
void ThreadPool<Task, SequenceContainer>::remove_workers(size_t n)
{
    if (shutdown_called_.load(std::memory_order_acquire)) {
        throw std::runtime_error("Cannot remove workers: Thread pool is at shutdown");
    }
    for (size_t i = 0; i < n; ++i) {
        tasks_.enqueue(Task{});
    }
    workers_.remove_workers(n);
}

template< typename Task, typename SequenceContainer>
size_t ThreadPool<Task, SequenceContainer>::workers() const
{
    return workers_.workers();
}

template< typename Task, typename SequenceContainer>
inline void ThreadPool<Task, SequenceContainer>::workers_function()
{
    for (;;) {
        Task task;
        tasks_.dequeue(task);

        try {
            task();
        } catch (const std::bad_function_call& ex) {
            // poison apples
            break;
        } catch (const std::exception& e) {
            std::osyncstream(std::cerr) << "[ThreadWorker] Task exception: " << e.what() << '\n';
        } catch (...) {
            assert(false && "[ThreadWorker] Unknown exception");
        }
    }
}

} // namespace mt

