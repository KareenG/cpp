#pragma once

#include <stdexcept>
#include <unistd.h>

#include "mt/periodic_executor.hpp"

namespace mt
{

template<typename Clock>
   /**
     * @brief Represents a scheduled task with its execution logic and timing.
     *
     * Each task stores:
     * - func_: the function to execute
     * - period_: the interval between executions
     * - next_run_: the next scheduled execution time
     */
class PeriodicExecutor<Clock>::Task {
public:
    TaskFunction func_;
    duration period_;
    time_point next_run_;

    bool operator<(const Task& other) const noexcept;
};

template<typename Clock>
bool PeriodicExecutor<Clock>::Task::operator<(const Task& other) const noexcept
{
    return next_run_ > other.next_run_; // Min-heap (earlier times come first)
}

template<typename Clock>
PeriodicExecutor<Clock>::PeriodicExecutor(Clock clock, bool start_paused)
: task_queue_{}
, executor_thread_([this] { run(); })
, mtx_{}
, control_cv_{}
, running_{true}
, paused_{start_paused}
, shutdown_{false}
, clock_{std::move(clock)}
{
}

template<typename Clock>
PeriodicExecutor<Clock>::~PeriodicExecutor() noexcept
{
    shutdown();
    if (executor_thread_.joinable()) {
        executor_thread_.join();
    }
}

template<typename Clock>
void PeriodicExecutor<Clock>::shutdown()
{
    std::lock_guard<std::mutex> lock(mtx_);
    if (shutdown_) {
        return;
    }
    running_ = false;
    shutdown_ = true;
    control_cv_.notify_all();
}

template<typename Clock>
void PeriodicExecutor<Clock>::submit(TaskFunction func, duration period)
{
    {
        std::lock_guard<std::mutex> lock(mtx_);
        if (shutdown_) {
            throw ExecutorDownException();
        }
    }
    Task task{std::move(func), period, clock_.get_next_start_time(period)};
    task_queue_.enqueue(std::move(task));
    control_cv_.notify_all();
}

template<typename Clock>
void PeriodicExecutor<Clock>::pause()
{
    std::lock_guard<std::mutex> lock(mtx_);
    if (shutdown_) {
        throw ExecutorDownException();
    }
    paused_ = true;
}

template<typename Clock>
void PeriodicExecutor<Clock>::resume()
{
    {
        std::lock_guard<std::mutex> lock(mtx_);
        if (shutdown_) {
            throw ExecutorDownException();
        }
        paused_ = false;
    }
    control_cv_.notify_all();
}

template<typename Clock>
std::size_t PeriodicExecutor<Clock>::size() const
{
    return task_queue_.size();
}

template<typename Clock>
void PeriodicExecutor<Clock>::run()
{
    while (true) {
        Task task;
        task_queue_.dequeue(task);
        {
            std::unique_lock<std::mutex> lock(mtx_);
            control_cv_.wait(lock, [this] { return !paused_ || !running_; });
            if (!running_){
                return;
            }
        }

        auto now = clock_.now();
        if (now < task.next_run_) {
            clock_.sleep_until_runtime(task.next_run_);
        }

        try
        {
            task.func_();
            task.next_run_ = clock_.get_next_start_time(task.period_);
            task_queue_.enqueue(std::move(task));
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        catch(...)
        {
            std::cerr << "Unexpected error occured.\n";
        }
    }
}

} // namespace mt

namespace mt::time_util {

template<typename ClockT>
typename Clock<ClockT>::time_point Clock<ClockT>::now() const noexcept
{
    return ClockT::now();
}

template<typename ClockT>
typename Clock<ClockT>::time_point Clock<ClockT>::get_next_start_time(duration period) const noexcept
{
    return now() + period;
}

template<typename ClockT>
void Clock<ClockT>::sleep_until_runtime(time_point activation_time) const
{
    std::this_thread::sleep_until(activation_time);
}

} // namespace mt::time_util