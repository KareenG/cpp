#pragma once

#include <ctime>

#include <cstddef>
#include <functional>
#include <stdexcept>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <memory>

#include "mt/thread_safe_priority_queue.hpp"

namespace mt
{
    
namespace time_util {

/**
 * @brief Generic clock wrapper based on std::chrono clocks.
 *
 * This class abstracts time-related utilities using the specified std::chrono-compatible clock.
 * It provides convenient methods for retrieving the current time, scheduling future events, and 
 * sleeping until a target time point.
 * 
 * The interface is suitable for use in periodic scheduling systems, timeouts, and general time management.
 *
 * @tparam ClockT The underlying std::chrono clock type. Defaults to std::chrono::steady_clock.
 *         Must provide:
 *         - static time_point ClockT::now() noexcept
 *         - ClockT::time_point type (a monotonic or system time point)
 *         - ClockT::duration type (used to specify time intervals)
 * 
 * @note The resulting Clock<T>::time_point supports all relational operators: <, <=, >, >=, ==, !=
 *       These operators are preferred over any manual comparison functions in client code.
 *
 * @par Example
 * @code
 * mt::time_util::Clock<> clock;
 * auto now = clock.now();
 * auto deadline = clock.get_next_start_time(std::chrono::milliseconds(500));
 * clock.sleep_until_runtime(deadline);
 * @endcode
 */
template<typename ClockT = std::chrono::steady_clock>
/** @requires ClockT must define a static now() function, and associated time_point and duration types.
 *            Typically std::chrono::steady_clock, system_clock, or high_resolution_clock.
 *            These often map to POSIX clocks (e.g., CLOCK_MONOTONIC, CLOCK_REALTIME), but are type-safe 
 *            and portable.
 */
class Clock {
public:
    using time_point = typename ClockT::time_point;
    using duration   = typename ClockT::duration;

    /**
     * @brief Returns the current time point from the clock.
     * 
     * @return A time_point representing the current time.
     * @note Equivalent to ClockT::now().
     */
    time_point now() const noexcept;

    /**
     * @brief Computes the time point that is a specified duration after now().
     * 
     * @param period The duration to add to the current time.
     * @return A future time_point that is now + period.
     */
    time_point get_next_start_time(duration period) const noexcept;

    /**
     * @brief Blocks the calling thread until the given activation time is reached.
     * 
     * @param activation_time The target time_point to sleep until.
     * @note Uses std::this_thread::sleep_until().
     */
    void sleep_until_runtime(time_point activation_time) const;
};

} // namespace time_util
     
/**
 * @brief A periodic executor that schedules and runs tasks at fixed intervals.
 *
 * This class creates a dedicated thread to manage and execute submitted tasks.
 * Tasks are enqueued in a blocking bounded queue and executed periodically according to their schedule.
 *
 * Thread-safety:
 * - All public methods (`submit`, `pause`, `resume`, `shutdown`, `size`) are thread-safe.
 * - Calls after `shutdown()` will throw `std::runtime_error`.
 * - Internally uses mutexes and atomics to protect shared state.
 * - The executor thread is joined automatically in the destructor.
 *
 * Concurrency contract:
 * - Methods can be safely called from multiple threads.
 * - Tasks are guaranteed to execute in the correct time order.
 * - After destruction, further calls to control methods will throw.
 *
 * @tparam Clock The clock type (default: mt::time_util::Clock<>).
 */
template<typename Clock = time_util::Clock<>>
class PeriodicExecutor {
public:
    using TaskFunction = std::function<void()>;
    using time_point = typename Clock::time_point;
    using duration = typename Clock::duration;

    /**
     * @brief Constructs a new PeriodicExecutor.
     * 
     * @param clock Clock instance for time tracking and scheduling.
     * @param start_paused If true, tasks will not execute until `resume()` is called.
     */
    PeriodicExecutor(Clock clock, bool start_paused = false);

    /**
     * @brief Destructor. Stops all task execution and joins the background thread.
     *
     * Automatically shuts down the executor. No need for manual shutdown.
     * All subsequent method calls will throw.
     */
    ~PeriodicExecutor() noexcept;

    PeriodicExecutor(const PeriodicExecutor&) = delete;
    PeriodicExecutor& operator=(const PeriodicExecutor&) = delete;
    PeriodicExecutor(PeriodicExecutor&&) noexcept = delete;
    PeriodicExecutor& operator=(PeriodicExecutor&&) noexcept = delete;

    /**
     * @brief Submits a task for periodic execution.
     *
     * @param func The task to execute periodically.
     * @param period The interval between executions.
     * @throws std::runtime_error if the executor has been shut down.
     */
    void submit(TaskFunction func, duration period);

    /**
     * @brief Pauses execution of tasks. Scheduled times remain unchanged.
     *
     * @note pause() doesn't instantly cancel already-scheduled execution.
     * @throws std::runtime_error if the executor has been shut down.
     */
    void pause();

    /**
     * @brief Resumes execution after a pause.
     *
     * @throws std::runtime_error if the executor has been shut down.
     */
    void resume();

    /**
     * @brief Returns the number of currently managed tasks.
     *
     * @return The number of tasks in the executor’s queue.
     */
    std::size_t size() const;

private:
    /**
     * @brief Represents a scheduled task with its execution logic and timing.
     */
    class Task;

    /**
     * @brief Main execution loop running in a dedicated thread.
     *
     * Dequeues tasks, waits until their scheduled time, executes them,
     * and reschedules them for their next run.
     *
     * Behavior:
     * - Waits on condition variable if paused or no tasks are ready.
     * - Executes tasks only when their time arrives.
     * - Exits cleanly when the executor is destroyed.
     */
    void run();

    /**
     * @brief Internal shutdown mechanism.
     * 
     * Called once from destructor to stop task execution and wake the worker.
     * Subsequent submissions or control calls will throw.
     */
    void shutdown();

private:
    mt::ThreadSafePriorityQueue<Task> task_queue_;
    std::thread executor_thread_;
    mutable std::mutex mtx_;
    std::condition_variable control_cv_;
    bool running_;
    bool paused_;
    bool shutdown_;
    time_util::Clock<> clock_;
};

class ExecutorDownException : public std::runtime_error {
public:
    inline ExecutorDownException()
    : std::runtime_error("Executor has been shut down")
    {
    }
};

} // namespace mt

#include "mt/periodic_executor.inl"