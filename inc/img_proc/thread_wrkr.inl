#pragma once

#include "img_proc/thread_wrkr.hpp"

#include <thread>
#include <vector>

namespace img_proc {
    
ThreadWorker::ThreadWorker(std::size_t thread_count)
: thread_count_(thread_count)
{
}

void ThreadWorker::run(std::size_t total_rows, std::function<void(std::size_t, std::size_t)> task)
{
    std::vector<std::thread> threads;
    std::size_t rows_per_thread = total_rows / thread_count_;

    // Launch (thread_count_ - 1) threads
    for (std::size_t i = 1; i < thread_count_; ++i) {
        std::size_t start = i * rows_per_thread;
        std::size_t end = (i == thread_count_ - 1) ? total_rows : start + rows_per_thread;

        threads.emplace_back([=]() {
            task(start, end);
        });
    }

    // Main thread does the first chunk itself
    std::size_t start = 0;
    std::size_t end = (thread_count_ == 1) ? total_rows : rows_per_thread;
    task(start, end);

    // Now join the worker threads
    for (auto& t : threads) {
        t.join();
    }
}

} // namespace img_proc
