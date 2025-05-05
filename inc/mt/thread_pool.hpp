#pragma once

#include <thread>
#include <functional>
#include <vector>
#include <queue>
#include <atomic>
#include <mutex>
#include <condition_variable>

#include "mt/queue.hpp"

namespace mt
{

/**
 * @brief Manages worker threads that execute tasks from a shared queue.
 * 
 * @tparam F The task type, typically std::function<void()>.
 * @tparam SequenceContainer A thread-safe queue that supports enqueue and dequeue.
 * 
 * @details
 * - `workers_`      : Vector holding all active worker threads.
 * - `tasks_`        : Reference to a shared task queue from which tasks are dequeued.
 * - `queue_mutex_`  : Mutex used to protect thread operations such as adding or joining workers.
 * - `shutdown_`     : Atomic flag indicating whether shutdown has been initiated.
 */
template<typename F = std::function<void()>,
        typename SequenceContainer = BlockingBoundedQueue<F>>
/**
 * @note Requires:
 * - SequenceContainer must support: `enqueue(F)` and `dequeue(F&)`
 */
class ThreadWorker {
public:
    /**
     * @brief Construct a new ThreadWorker
     * 
     * @param tasks Reference to a thread-safe task queue
     * @param initial_threads Initial number of concurrent threads allowed
     */
    explicit ThreadWorker(SequenceContainer& tasks, size_t initial_threads);

    /**
     * @brief Destructor - triggers graceful shutdown
     */
    ~ThreadWorker();

    ThreadWorker(const ThreadWorker&) = delete;
    ThreadWorker& operator=(const ThreadWorker&) = delete;

    /**
     * @brief Adds up to n worker threads, not exceeding max_threads_
     * 
     * @param n Number of threads to add
     */
    void add_workers(size_t n);

    // /**
    //  * @brief Removes up to n worker threads by submitting null-tasks
    //  * 
    //  * @param n Number of threads to remove
    //  */
    // void remove_workers(size_t n);

    /**
     * @brief Enqueues a task to be executed by a worker thread
     * 
     * @param task The task to enqueue
     */
    void enqueue(F task);

    /**
     * @brief Gets the current number of worker threads.
     * 
     * @return size_t Current number of active worker threads.
     */
    size_t workers() const;

    /**
     * @brief Gracefully shuts down all worker threads after completing tasks
     */
    void shutdown_graceful();

private:
    void assert_only_poison_pills() const;

private:
    std::vector<std::thread> workers_;
    SequenceContainer& tasks_;
    std::mutex queue_mutex_;
    std::atomic<bool> shutdown_;
};

/**
 * @brief Thread pool interface for concurrent task execution.
 * 
 * @tparam F The task type, typically std::function<void()>.
 * @tparam SequenceContainer A thread-safe queue with enqueue/dequeue support.
 * 
 * @details
 * - `tasks_`      : Internal task queue.
 * - `worker_`     : Manages worker threads
 */
template<typename F = std::function<void()>,
        typename SequenceContainer = BlockingBoundedQueue<F>>
/** @note Requires:
* - SequenceContainer must support: `enqueue(F)` and `dequeue(F&)`
*/
class ThreadPool {
public:
    /**
     * @brief Construct a new ThreadPool object
     * 
     * @param num_threads Number of base worker threads to start with
     * @param extra_threads Optional additional threads
     */
    explicit ThreadPool(size_t num_threads = std::thread::hardware_concurrency() - 1);

    /**
     * @brief Destructor - gracefully shuts down all threads
     */
    ~ThreadPool();

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    /**
     * @brief Submit a task to be executed by the thread pool
     * 
     * @param task The task to run
     */
    void submit(F task);

    /**
     * @brief Shut down all threads after all tasks are completed
     */
    void shutdown_graceful();

    /**
     * @brief Adds additional worker threads dynamically
     * 
     * @param n Number of threads to add (default 1)
     */
    void add_workers(size_t n = 1);

    // /**
    //  * @brief Removes active worker threads by submitting null-tasks
    //  * 
    //  * @param n Number of threads to remove
    //  */
    // void remove_workers(size_t n = 1);
    
    /**
     * @brief Gets the current number of worker threads in the pool.
     * 
     * @return size_t Current number of active worker threads.
     */
    size_t workers() const;

private:
    SequenceContainer tasks_;
    ThreadWorker<F, SequenceContainer> worker_;
};

} // namespace mt

#include "mt/thread_pool.inl"