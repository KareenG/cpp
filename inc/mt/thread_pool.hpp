#pragma once

#include <thread>
#include <functional>
#include <vector>
#include <queue>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <cassert>   // for assert
#include <iostream>
#include <syncstream> // std::cerr is global to all threads! must wrap with osyncstream

#include "mt/queue.hpp"

namespace mt
{

/**
 * @brief Manages worker threads that execute tasks from a shared task queue.
 * 
 * @tparam F The task type, typically std::function<void()>.
 * @tparam SequenceContainer A thread-safe queue that supports enqueue and dequeue operations.
 * 
 * @details
 * - thread_function_      : The task function for worker threads
 * - workers_              : Vector holding all active worker threads.
 * - mutex_                : Mutex used to protect thread operations such as adding or joining workers.
 * - shutdown_             : Atomic flag indicating whether shutdown has been initiated.
 * - retiring_threads_     : Queue for retiring threads
 * - immediate_shutdown_   : Flag for immediate shutdown mode
 * 
 * @note Requires the `SequenceContainer` type to support:
 * - enqueue(F) and dequeue(F&)
 */
class ThreadWorker {
public:
    /**
     * @brief Constructs a ThreadWorker with a specified task function and number of threads.
     * 
     * @param thread_function The function each worker thread will execute.
     * @param num_threads Number of worker threads to create.
     */
    explicit ThreadWorker(std::function<void()> thread_function, size_t num_threads);

    /**
     * @brief Destructor - triggers graceful shutdown, ensuring all tasks are completed.
     */
    ~ThreadWorker();

    ThreadWorker(const ThreadWorker&) = delete;
    ThreadWorker& operator=(const ThreadWorker&) = delete;

    /**
     * @brief Adds up to `n` worker threads, not exceeding the maximum limit.
     * 
     * @param n Number of threads to add.
     */
    void add_workers(size_t n);

    /**
     * @brief Removes up to `n` worker threads by submitting null-tasks to the queue.
     * 
     * @param n Number of threads to remove.
     */
    void remove_workers(size_t n);

    /**
     * @brief Returns the current number of active worker threads.
     * 
     * @return size_t The number of active worker threads.
     */
    size_t workers() const;

    /**
     * @brief Gracefully shuts down all worker threads after completing their tasks.
     */
    void shutdown_graceful();

    /**
     * @brief Immediately shuts down worker threads after current tasks are completed, without waiting for new tasks.
     */
    void shutdown_immediate();

private:
    std::function<void()> thread_function_;
    std::vector<std::thread> workers_;
    mutable std::mutex mutex_;
    std::atomic<bool> shutdown_;
    BlockingBoundedQueue<std::thread::id> retiring_threads_;
    std::atomic<bool> immediate_shutdown_;
};


/**
 * @brief Manages a pool of worker threads that execute tasks concurrently.
 * 
 * @tparam F The task type, typically std::function<void()>.
 * @tparam SequenceContainer A thread-safe queue with enqueue/dequeue support.
 * 
 * @details
 * - tasks_           : Internal task queue holding tasks for worker threads.
 * - worker_          : Manages the worker threads.
 * - shutdown_called_ : Atomic flag indicating if a shutdown has been called.
 */
template<typename F = std::function<void()>,
        typename SequenceContainer = BlockingBoundedQueue<F>>
/** 
 * @note Requires the `SequenceContainer` type to support:
 * - enqueue(F) and dequeue(F&)
 */
class ThreadPool {
public:
    /**
     * @brief Constructs a ThreadPool with a specified number of worker threads.
     * 
     * @param num_threads Number of base worker threads to start with.
     * @param initial_capacity Maximum capacity of the task queue (default: 1024).
     */
    explicit ThreadPool(size_t num_threads = std::thread::hardware_concurrency(), size_t initial_capacity = 1024);

    /**
     * @brief Destructor - gracefully shuts down all worker threads.
     */
    ~ThreadPool() = default;

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    /**
     * @brief Submits a task to be executed by the thread pool.
     * 
     * @param task The task to run.
     */
    void submit(F&& task);

    /**
     * @brief Gracefully shuts down all worker threads after all tasks are completed.
     */
    void shutdown_graceful();

    /**
     * @brief Immediately shuts down worker threads after current tasks are completed.
     */
    void shutdown_immediate();

    /**
     * @brief Adds additional worker threads to the pool.
     * 
     * @param n Number of threads to add (default: 1).
     */
    void add_workers(size_t n = 1);

    /**
     * @brief Removes active worker threads by submitting null-tasks.
     * 
     * @param n Number of threads to remove (default: 1).
     */
    void remove_workers(size_t n = 1);

    /**
     * @brief Returns the current number of worker threads in the pool.
     * 
     * @return size_t The number of active worker threads.
     */
    size_t workers() const;

private:
    /**
     * @brief Function executed by each worker thread to process tasks.
     */
    void worker_function();

private:
    SequenceContainer tasks_;
    ThreadWorker worker_;
    std::atomic<bool> shutdown_called_;
};

} // namespace mt

#include "mt/thread_pool.inl"
