#include "mt/thread_pool.hpp"

namespace mt
{
    
ThreadWorker::ThreadWorker(std::function<void()> thread_function, size_t num_threads)
: thread_function_{thread_function}
, workers_{}
, mutex_{}
, shutdown_{false}
, retiring_threads_{}
{
    workers_.reserve(num_threads);
    add_workers(num_threads);
}

ThreadWorker::~ThreadWorker()
{
    shutdown_immediate();
}

void ThreadWorker::add_workers(size_t n)
{
    if (shutdown_.load(std::memory_order_acquire) || n == 0) {
        return;
    }

    std::lock_guard<std::mutex> lock(mutex_);

    for (size_t i = 0; i < n; ++i) {
        workers_.emplace_back([this]() {
                thread_function_();
                retiring_threads_.enqueue(std::this_thread::get_id());
        });
    }
}

void ThreadWorker::remove_workers(size_t n)
{
    if (n == 0) {
        return; // already shut down
    }
    
    for (size_t i = 0; i < n; ++i) {
        std::thread::id retiring_id;
        retiring_threads_.dequeue(retiring_id);
        
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = std::find_if(workers_.begin(), workers_.end(), [&](const std::thread& t) {
            return t.get_id() == retiring_id;
        });
        
        if (it != workers_.end()) {
            if (it->joinable()) {
                it->join();
            }
            workers_.erase(it);
        }
    }
}

size_t ThreadWorker::workers() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return workers_.size();
}

void ThreadWorker::shutdown_graceful()
{
    shutdown_.store(true, std::memory_order_release);
    remove_workers(workers());
}

void ThreadWorker::shutdown_immediate()
{
    shutdown_graceful();
}

} // namespace mt