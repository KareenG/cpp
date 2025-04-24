#pragma once

#include "imag_proc/thread_wrkr.hpp"

#include <thread>
#include <vector>

ThreadWorker::ThreadWorker(std::size_t thread_count)
: thread_count_(thread_count)
{
}

void ThreadWorker::run(std::size_t total_rows, std::function<void(std::size_t, std::size_t)> task)
{
    std::vector<std::thread> threads;
    std::size_t rows_per_thread = total_rows / thread_count_;

    for (std::size_t i = 0; i < thread_count_; ++i) {
        std::size_t start = i * rows_per_thread;
        std::size_t end = (i == thread_count_ - 1) ? total_rows : start + rows_per_thread;

        threads.emplace_back([=]() {
            task(start, end);
        });
    }

    for (auto& t : threads) {
        t.join();
    }
}
