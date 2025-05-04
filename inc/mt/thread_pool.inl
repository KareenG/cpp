#pragma once

#include <thread>
#include <vector>
#include <cassert>

#include "mt/thread_pool.hpp"

namespace mt
{
    
template<typename F, typename SequenceContainer>
ThreadWorker<F, SequenceContainer>::ThreadWorker(SequenceContainer& tasks, size_t max_threads)
: tasks_(tasks)
, queue_mutex_()
, shutdown_(false)
, max_threads_(max_threads)
{
    add_workers(max_threads_);
}

template<typename F, typename SequenceContainer>
ThreadWorker<F, SequenceContainer>::~ThreadWorker()
{
    shutdown_graceful();
    assert(tasks_.empty());
}

template<typename F, typename SequenceContainer>
void ThreadWorker<F, SequenceContainer>::add_workers(size_t n)
{
    if (shutdown_.load(std::memory_order_acquire) || n == 0) {
        return;
    }

    std::lock_guard<std::mutex> lock(queue_mutex_);

    size_t can_add = max_threads_ - workers_.size();
    n = std::min(n, can_add);

    for (size_t i = 0; i < n; ++i) {
        workers_.emplace_back([this] {
            while (true) {
                F task;
                tasks_.dequeue(task); // blocks until a task is available

                if (!task) {
                    return; // poison pill -> terminate thread
                }

                try {
                    task();
                } catch (const std::exception& e) {
                    // Log or handle known exception types
                    std::cerr << "[ThreadWorker] Task threw exception: " << e.what() << '\n';
                } catch (...) {
                    // Catch-all for non-std exceptions
                    std::cerr << "[ThreadWorker] Task threw unknown exception\n";
                }
            }
        });
    }
}

template<typename F, typename SequenceContainer>
void ThreadWorker<F, SequenceContainer>::enqueue(F task)
{
    if (shutdown_) {
        return;
    }
    tasks_.enqueue(std::move(task));
}

template<typename F, typename SequenceContainer>
void ThreadWorker<F, SequenceContainer>::shutdown_graceful()
{
    bool expected = false;
    if (!shutdown_.compare_exchange_strong(expected, true, std::memory_order_acq_rel)) {
        return; // already shut down
    }
    {
        std::lock_guard<std::mutex> lock(queue_mutex_);
        // Enqueue one poison pill for each thread
        for (size_t i = 0; i < workers_.size(); ++i) {
            tasks_.enqueue(nullptr);
        }
    }

    // Join all threads
    for (std::thread& worker : workers_) {
        if (worker.joinable()) {
            worker.join();
        }
    }

    workers_.clear();
}

template<typename F, typename SequenceContainer>
ThreadPool<F, SequenceContainer>::ThreadPool(size_t num_threads, size_t extra_threads)
: tasks_{}
, worker_{tasks_, num_threads + extra_threads}
{
}

template<typename F, typename SequenceContainer>
ThreadPool<F, SequenceContainer>::~ThreadPool()
{
    shutdown_graceful();
}

template<typename F, typename SequenceContainer>
void ThreadPool<F, SequenceContainer>::submit(F task)
{
    worker_.enqueue(std::move(task));
}

template<typename F, typename SequenceContainer>
void ThreadPool<F, SequenceContainer>::shutdown_graceful()
{
    worker_.shutdown_graceful();
}

template<typename F, typename SequenceContainer>
void ThreadPool<F, SequenceContainer>::add_workers(size_t n)
{
    worker_.add_workers(n);
}

} // namespace mt

