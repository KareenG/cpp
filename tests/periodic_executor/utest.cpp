#include "mu_test.h"

#include "mt/periodic_executor.hpp"
#include "mt/periodic_executor.inl"

#include <iostream>
#include <chrono>
#include <atomic>
#include <thread>

using namespace std::chrono;
using namespace std::chrono_literals; // enables literal suffixes, e.g. 24h, 1ms, 1s.

BEGIN_TEST(clock_now_monotonic)
    mt::time_util::Clock<> clk;
    auto t1 = clk.now();
    auto t2 = clk.now();
    ASSERT_THAT(t2 > t1 || t2 == t1);
END_TEST

BEGIN_TEST(clock_future_timepoint_is_greater)
    mt::time_util::Clock<> clk;
    auto now = clk.now();
    auto future = clk.get_next_start_time(std::chrono::milliseconds(100));
    ASSERT_THAT(future > now);
END_TEST

BEGIN_TEST(clock_sleep_blocks_until_target)
    mt::time_util::Clock<> clk;
    auto period = milliseconds(500);
    auto start = clk.now();
    auto target = start + period;
    clk.sleep_until_runtime(target);
    auto end = clk.now();
    ASSERT_THAT(end >= target);
END_TEST


BEGIN_TEST(executor_runs_tasks_without_pause)
    mt::time_util::Clock<> clk;

    mt::PeriodicExecutor<mt::time_util::Clock<>> executor(clk);

    std::atomic<int> a_count{0};
    std::atomic<int> b_count{0};

    executor.submit([&, start = clk.now()] {
        ++a_count;
        auto now = clk.now();
        std::cout << "🐱 Cat A [" << a_count << "] @ "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count()
                  << "ms\n";
    }, 100ms);

    executor.submit([&, start = clk.now()] {
        ++b_count;
        auto now = clk.now();
        std::cout << "😼 Cat B [" << b_count << "] @ "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count()
                  << "ms\n";
    }, 125ms);

    std::this_thread::sleep_for(505ms);

    ASSERT_THAT(a_count.load() >= 5 && a_count.load() <= 6);
    ASSERT_THAT(b_count.load() >= 4 && b_count.load() <= 5);
END_TEST

BEGIN_TEST(executor_resumes_after_pause)
    mt::time_util::Clock<> clk;

    mt::PeriodicExecutor<mt::time_util::Clock<>> executor(clk);

    std::atomic<int> c_count{0};

    executor.submit([&, start = clk.now()] {
        ++c_count;
        auto now = clk.now();
        std::cout << "😸 Cat C [" << c_count << "] @ "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count()
                  << "ms\n";
    }, 90ms);

    std::this_thread::sleep_for(180ms); // Executes ~2 times (at 90ms, 180ns).

    executor.pause();
    std::this_thread::sleep_for(300ms); // Pauses the executor. Then, sleeps for 300ms. During this time, no tasks should run.
    
    executor.resume();                  // Tasks resumes (at 180 + 300 = 480ms)
    std::this_thread::sleep_for(300ms); // Should run another ~5 times.

    ASSERT_THAT(c_count.load() <= 7);
END_TEST

BEGIN_TEST(executor_multiple_tasks_with_runtime_pause)
    mt::time_util::Clock<> clk;
    mt::PeriodicExecutor<mt::time_util::Clock<>> executor(clk);

    std::atomic<int> a_count{0};
    std::atomic<int> b_count{10};
    std::atomic<int> c_count{20};
    std::atomic<bool> paused{false};

    executor.submit([&, start = clk.now()] {
        ++a_count;
        auto now = clk.now();
        std::cout << "[A] ran (" << a_count.load() << ") @ "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count()
                  << "ms\n";
    }, 100ms);

    executor.submit([&, start = clk.now()] {
        ++b_count;
        auto now = clk.now();
        std::cout << "[B] ran (" << b_count.load() << ") @ "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count()
                  << "ms\n";
    }, 100ms);

    executor.submit([&, start = clk.now()] {
        ++c_count;
        auto now = clk.now();
        std::cout << "[C] ran (" << c_count.load() << ") @ "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count()
                  << "ms\n";
    }, 100ms);

    executor.submit([&, start = clk.now()] {
        if(!paused.exchange(true)) {
            auto now = clk.now();
            executor.pause();
            std::cout << "[PAUSE] triggered @ "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count()
                  << "ms\n";
        }
    }, 1100ms);


    std::this_thread::sleep_for(1200ms);
    executor.resume();
    std::this_thread::sleep_for(1100ms);

    int a_total = a_count.load(), b_total = b_count.load(), c_total = c_count.load();

    std::cout << "[SUMMARY] A: " << a_total << " B: " << b_total << " C: " << c_total << "\n";

    ASSERT_THAT(a_total == 3);
    ASSERT_THAT(b_total == 13);
    ASSERT_THAT(c_total == 23);
END_TEST


BEGIN_TEST(submit_after_executor_destruction_throws)
    std::atomic<int> counter{0};
    bool exception_thrown = false;
    mt::PeriodicExecutor<mt::time_util::Clock<>>* raw_executor = nullptr;

    {
        auto executor_ptr = std::make_unique<mt::PeriodicExecutor<mt::time_util::Clock<>>>(mt::time_util::Clock<>{});
        raw_executor = executor_ptr.get();

        executor_ptr->submit([&] { ++counter; }, 50ms);
        std::this_thread::sleep_for(150ms);
    }

    ASSERT_THAT(counter.load() > 0);

    try {
        raw_executor->submit([] {}, 100ms);
    } catch (const mt::ExecutorDownException&) {
        exception_thrown = true;
    }

    ASSERT_THAT(exception_thrown);
END_TEST


BEGIN_SUITE(PeriodicExecutorTests)
    TEST(clock_now_monotonic)
    TEST(clock_future_timepoint_is_greater)
    TEST(clock_sleep_blocks_until_target)

    TEST(executor_runs_tasks_without_pause)
    TEST(executor_resumes_after_pause)
    TEST(executor_multiple_tasks_with_runtime_pause)
    TEST(submit_after_executor_destruction_throws)
END_SUITE
