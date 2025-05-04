#include "mu_test.h"

#include <iostream>
#include <chrono>

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
    pool.submit([&counter] { ++counter; }); // Should be ignored
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

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
    mt::ThreadPool<Task> pool(2); // יוצרים ThreadPool עם שני threads
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

/*------------------------------------------------------------------------------------------*/

BEGIN_SUITE(thread_pool_tests)
    TEST(thread_pool_runs_all_tasks)
    TEST(thread_pool_shutdown_blocks_submission)
    TEST(thread_pool_runs_all_tasks_and_shutdown_cleanly)
    TEST(submit_tasks_to_thread_pool)
END_SUITE