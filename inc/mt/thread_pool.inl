#pragma once

#include <thread>
#include <vector>
#include <cassert>

#include "mt/thread_pool.hpp"

namespace mt
{
    
template<typename F, typename SequenceContainer>
ThreadWorker<F, SequenceContainer>::ThreadWorker(SequenceContainer& tasks, size_t initial_threads)
: workers_(initial_threads)
, tasks_(tasks)
, queue_mutex_()
, shutdown_(false)
{
    add_workers(initial_threads);
}

template<typename F, typename SequenceContainer>
ThreadWorker<F, SequenceContainer>::~ThreadWorker()
{
    shutdown_graceful();
    assert_only_poison_pills();
}

template<typename F, typename SequenceContainer>
void ThreadWorker<F, SequenceContainer>::add_workers(size_t n)
{
    if (shutdown_.load(std::memory_order_acquire) || n == 0) {
        return;
    }

    std::lock_guard<std::mutex> lock(queue_mutex_);

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
    if (shutdown_.load(std::memory_order_acquire)) {
        return;
    }
    tasks_.enqueue(std::move(task));
}

template<typename F, typename SequenceContainer>
size_t ThreadWorker<F, SequenceContainer>::workers() const
{
    std::lock_guard<std::mutex> lock(queue_mutex_);
    return workers_.size();
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
void ThreadWorker<F, SequenceContainer>::assert_only_poison_pills() const {
    for (size_t i = 0; i < tasks_.size(); ++i) {
        F task;
        tasks_.dequeue(task);
        assert(!task && "Non-null task found after shutdown");
    }
}

template<typename F, typename SequenceContainer>
ThreadPool<F, SequenceContainer>::ThreadPool(size_t num_threads)
: tasks_{}
, worker_{tasks_, num_threads}
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

