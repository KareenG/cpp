#pragma once

#include <cstddef>
#include <functional>

/**
 * @brief Executes a given task in parallel across multiple threads.
 */
class ThreadWorker {
public:
    /**
     * @brief Constructs a ThreadWorker with a given number of threads.
     * @param thread_count Number of threads to launch.
     */
    explicit ThreadWorker(std::size_t thread_count);

    /**
     * @brief Runs a task function in parallel, splitting the range [0, total_rows).
     * @param total_rows Total number of rows to process.
     * @param task A function that receives a row range [start, end) to process.
     */
    void run(std::size_t total_rows, std::function<void(std::size_t, std::size_t)> task);

private:
    std::size_t thread_count_;
};

#include "imag_proc/thread_wrkr.inl"