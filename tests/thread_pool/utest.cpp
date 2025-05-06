#include "mu_test.h"

#include <iostream>
#include <chrono>
#include <numeric>
#include <functional>

#include "mt/queue.hpp"
#include "mt/thread_pool.hpp"

BEGIN_TEST(thread_pool_runs_all_tasks)
    std::atomic<int> counter{0};
    mt::ThreadPool<> pool(2);

    for (int i = 0; i < 10; ++i) {
        pool.submit([&counter] {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            ++counter;
        });
    }

    pool.shutdown_graceful();
    ASSERT_EQUAL(counter.load(), 10);
END_TEST

BEGIN_TEST(thread_pool_shutdown_blocks_submission)
    std::atomic<int> counter{0};
    mt::ThreadPool<> pool(2);

    pool.submit([&counter] { ++counter; });
    pool.shutdown_graceful();

    int before = counter.load();

    bool exception_thrown = false;
    try {
        pool.submit([&counter] { ++counter; });
    } catch (const std::runtime_error& e) {
        exception_thrown = true;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    ASSERT_THAT(exception_thrown);
    ASSERT_EQUAL(counter.load(), before);
END_TEST

BEGIN_TEST(thread_pool_runs_all_tasks_and_shutdown_cleanly)
    using Task = std::function<void()>;
    mt::ThreadPool<Task> pool(4); 
    std::atomic<int> counter{0};
    const int num_tasks = 100;
    for (int i = 0; i < num_tasks; ++i) {
        pool.submit([&counter] {
            counter.fetch_add(1, std::memory_order_relaxed);
        });
    }
    pool.shutdown_graceful();
    ASSERT_EQUAL(counter.load(), num_tasks);
END_TEST

BEGIN_TEST(submit_tasks_to_thread_pool)
    using Task = std::function<void()>;
    mt::ThreadPool<Task> pool(2);
    std::atomic<bool> task1_completed{false};
    std::atomic<bool> task2_completed{false};
    // Submit task 1
    pool.submit([&task1_completed] {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        task1_completed.store(true, std::memory_order_release);
    });
    // Submit task 2
    pool.submit([&task2_completed] {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        task2_completed.store(true, std::memory_order_release);
    });

    pool.shutdown_graceful();
    // Assert that both tasks were completed
    ASSERT_THAT(task1_completed.load(std::memory_order_acquire));
    ASSERT_THAT(task2_completed.load(std::memory_order_acquire));
END_TEST

BEGIN_TEST(thread_pool_add_and_remove_workers)
    std::atomic<int> counter{0};
    mt::ThreadPool<> pool(1); // Start with 1 thread

    pool.add_workers(2);  // Increase to 3
    for (int i = 0; i < 100; ++i) {
        pool.submit([&counter] {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            ++counter;
        });
    }

    pool.remove_workers(2); // Back to 1
    pool.shutdown_graceful();

    bool add_fail = false;
    bool remove_fail = false;
    try { pool.add_workers(1); } catch (...) { add_fail = true; }
    try { pool.remove_workers(1); } catch (...) { remove_fail = true; }

    ASSERT_EQUAL(counter.load(), 100);
    ASSERT_THAT(add_fail);
    ASSERT_THAT(remove_fail);
END_TEST

BEGIN_TEST(thread_pool_add_and_remove_immediate_workers)
    std::atomic<int> counter{0};
    mt::ThreadPool<> pool(1);

    pool.add_workers(2);
    for (int i = 0; i < 100; ++i) {
        pool.submit([&counter] {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            ++counter;
        });
    }

    pool.remove_workers(2);
    pool.shutdown_immediate();

    bool add_fail = false;
    try { pool.add_workers(1); } catch (...) { add_fail = true; }

    ASSERT_THAT(counter.load() <= 100);
    ASSERT_THAT(add_fail);
END_TEST

BEGIN_TEST(thread_pool_shutdown_immediate_stops_new_tasks)
    std::atomic<int> counter{0};

    {
        mt::ThreadPool<> pool(2);

        for (int i = 0; i < 10; ++i) {
            pool.submit([&counter] {
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
                ++counter;
            });
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(25));
        pool.shutdown_immediate();

        bool exception_thrown = false;
        try {
            pool.submit([] {}); // should fail
        } catch (...) {
            exception_thrown = true;
        }

        ASSERT_THAT(exception_thrown);
    }

    int final = counter.load();
    ASSERT_THAT(final > 0);
    ASSERT_THAT(final < 10);
END_TEST

BEGIN_TEST(many_tasks_tp_8_test)
    using Task = std::function<void()>;
    mt::ThreadPool<Task> pool(8);
    const int num_tasks = 100000;
    std::vector<int> results(num_tasks, 0);
    for (int i = 0; i < num_tasks; ++i) {
        pool.submit([&results, i]() {
            ++results[i];
        });
    }
    pool.shutdown_graceful();
    int res = std::accumulate(results.begin(), results.end(), 0);
    ASSERT_EQUAL(res, num_tasks);
END_TEST

BEGIN_TEST(thread_pool_immediate_is_faster_than_graceful)
    using namespace std::chrono;

    constexpr int kTaskCount = 1500;
    constexpr int kTaskDelayMs = 4;

    std::atomic<int> counter_graceful{0};
    std::atomic<int> counter_immediate{0};

    mt::ThreadPool<> pool_graceful(100);
    for (int i = 0; i < kTaskCount; ++i) {
        pool_graceful.submit([&counter_graceful, kTaskDelayMs] {
            std::this_thread::sleep_for(std::chrono::milliseconds(kTaskDelayMs));
            ++counter_graceful;
        });
    }

    auto start_graceful = high_resolution_clock::now();
    pool_graceful.shutdown_graceful();
    auto end_graceful = high_resolution_clock::now();
    auto duration_graceful = duration_cast<milliseconds>(end_graceful - start_graceful).count();

    mt::ThreadPool<> pool_immediate(100);
    for (int i = 0; i < kTaskCount; ++i) {
        pool_immediate.submit([&counter_immediate, kTaskDelayMs] {
            std::this_thread::sleep_for(std::chrono::milliseconds(kTaskDelayMs));
            ++counter_immediate;
        });
    }

    auto start_immediate = high_resolution_clock::now();
    pool_immediate.shutdown_immediate();
    auto end_immediate = high_resolution_clock::now();
    auto duration_immediate = duration_cast<milliseconds>(end_immediate - start_immediate).count();

    std::cout << "Graceful shutdown:  " << duration_graceful << "ms\n";
    std::cout << "Immediate shutdown: " << duration_immediate << "ms\n";
    std::cout << "Tasks completed (graceful):  " << counter_graceful.load() << '\n';
    std::cout << "Tasks completed (immediate): " << counter_immediate.load() << '\n';

    ASSERT_THAT(counter_immediate < counter_graceful);
END_TEST

/*------------------------------------------------------------------------------------------*/

// run make recheck
// for printing use TRACE(variable)
BEGIN_SUITE(thread_pool_tests)
    TEST(thread_pool_runs_all_tasks)
    TEST(thread_pool_shutdown_blocks_submission)
    TEST(thread_pool_runs_all_tasks_and_shutdown_cleanly)
    TEST(submit_tasks_to_thread_pool)

    TEST(thread_pool_shutdown_immediate_stops_new_tasks)

    TEST(many_tasks_tp_8_test)

    TEST(thread_pool_add_and_remove_workers)
    TEST(thread_pool_add_and_remove_immediate_workers)

    TEST(thread_pool_immediate_is_faster_than_graceful)

END_SUITE