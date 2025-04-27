#include "mu_test.h"

#include <thread>
#include <vector>

#include "mt/queue.hpp"

BEGIN_TEST(test_constructor)
    mt::BlockingBoundedQueue<int> q{7};
    ASSERT_EQUAL(q.size(), 0);
    ASSERT_EQUAL(q.capacity(), 7);
END_TEST

BEGIN_TEST(test_enqueue_lvalue)
    mt::BlockingBoundedQueue<int> q{3};
    int val = 42;
    q.enqueue(val);
    ASSERT_EQUAL(q.size(), 1);
    ASSERT_EQUAL(q.full(), false);
END_TEST

BEGIN_TEST(test_enqueue_rvalue)
    mt::BlockingBoundedQueue<int> q{2};
    q.enqueue(99); // move
    ASSERT_EQUAL(q.size(), 1);
    q.enqueue(100);
    ASSERT_EQUAL(q.size(), 2);
    ASSERT_EQUAL(q.full(), true);
END_TEST

BEGIN_TEST(test_dequeue)
    mt::BlockingBoundedQueue<int> q{5};
    q.enqueue(123);
    q.enqueue(456);

    int val = 0;
    q.dequeue(val);
    ASSERT_EQUAL(val, 123);

    ASSERT_EQUAL(q.size(), 1);
    ASSERT_EQUAL(q.full(), false);
END_TEST

BEGIN_TEST(test_empty)
    mt::BlockingBoundedQueue<int> q{4};
    ASSERT_THAT(q.empty());

    q.enqueue(1);
    ASSERT_THAT(!q.empty());

    int val = 0;
    q.dequeue(val);
    ASSERT_THAT(q.empty());
END_TEST

BEGIN_TEST(test_full)
    mt::BlockingBoundedQueue<int> q{2};
    ASSERT_THAT(!q.full());

    q.enqueue(10);
    ASSERT_THAT(!q.full());

    q.enqueue(20);
    ASSERT_THAT(q.full());
END_TEST

BEGIN_TEST(test_size_and_capacity)
    mt::BlockingBoundedQueue<int> q{5};
    ASSERT_EQUAL(q.capacity(), 5);
    ASSERT_EQUAL(q.size(), 0);

    q.enqueue(11);
    q.enqueue(22);

    ASSERT_EQUAL(q.size(), 2);
    ASSERT_EQUAL(q.capacity(), 5);
END_TEST

/*------------------------------------------------------------------------------------------*/

static const std::size_t NUM_ITEMS = 1'000'000; // 1 million

BEGIN_TEST(fifo_single_thread)
    mt::BlockingBoundedQueue<std::size_t> q{NUM_ITEMS};

    for (std::size_t i = 0; i < NUM_ITEMS; ++i) {
        q.enqueue(i);
    }

    for (std::size_t i = 0; i < NUM_ITEMS; ++i) {
        std::size_t value;
        q.dequeue(value);
        ASSERT_EQUAL(value, i); // Check strict FIFO order
    }

    ASSERT_THAT(q.empty());
END_TEST

BEGIN_TEST(fifo_single_producer_single_consumer)
    mt::BlockingBoundedQueue<std::size_t> q{NUM_ITEMS};
    std::vector<std::size_t> consumed;
    consumed.reserve(NUM_ITEMS);

    std::thread producer([&q] {
        for (std::size_t i = 0; i < NUM_ITEMS; ++i) {
            q.enqueue(i);
        }
    });

    std::thread consumer([&q, &consumed] {
        for (std::size_t i = 0; i < NUM_ITEMS; ++i) {
            std::size_t value;
            q.dequeue(value);
            consumed.push_back(value);
        }
    });

    producer.join();
    consumer.join();

    ASSERT_EQUAL(consumed.size(), NUM_ITEMS);
    for (std::size_t i = 0; i < NUM_ITEMS; ++i) {
        ASSERT_EQUAL(consumed[i], i);
    }
END_TEST

BEGIN_TEST(fifo_two_producers_one_consumer)
    mt::BlockingBoundedQueue<std::size_t> q{NUM_ITEMS};

    std::thread producer1([&q] {
        for (std::size_t i = 0; i < NUM_ITEMS / 2; ++i) {
            q.enqueue(i);
        }
    });

    std::thread producer2([&q] {
        for (std::size_t i = NUM_ITEMS / 2; i < NUM_ITEMS; ++i) {
            q.enqueue(i);
        }
    });

    std::vector<std::size_t> result;
    result.reserve(NUM_ITEMS);

    std::thread consumer([&q, &result] {
        for (std::size_t i = 0; i < NUM_ITEMS; ++i) {
            std::size_t value;
            q.dequeue(value);
            result.push_back(value);
        }
    });

    producer1.join();
    producer2.join();
    consumer.join();

    ASSERT_EQUAL(result.size(), NUM_ITEMS);
END_TEST

BEGIN_TEST(fifo_one_producer_two_consumers)
    mt::BlockingBoundedQueue<std::size_t> q{NUM_ITEMS};

    std::thread producer([&q] {
        for (std::size_t i = 0; i < NUM_ITEMS; ++i) {
            q.enqueue(i);
        }
    });

    std::vector<std::size_t> consumer1_result;
    std::vector<std::size_t> consumer2_result;
    consumer1_result.reserve(NUM_ITEMS / 2 + 10);
    consumer2_result.reserve(NUM_ITEMS / 2 + 10);

    std::thread consumer1([&q, &consumer1_result] {
        for (std::size_t i = 0; i < NUM_ITEMS / 2; ++i) {
            std::size_t value;
            q.dequeue(value);
            consumer1_result.push_back(value);
        }
    });

    std::thread consumer2([&q, &consumer2_result] {
        for (std::size_t i = 0; i < NUM_ITEMS / 2; ++i) {
            std::size_t value;
            q.dequeue(value);
            consumer2_result.push_back(value);
        }
    });

    producer.join();
    consumer1.join();
    consumer2.join();

    ASSERT_EQUAL(consumer1_result.size() + consumer2_result.size(), NUM_ITEMS);
END_TEST

BEGIN_TEST(fifo_four_producers_four_consumers)

    mt::BlockingBoundedQueue<int> queue(50);
    std::vector<int> results;
    std::mutex results_mutex;

    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;
    const int items_per_producer = 250'000; // for 1'000'000 we get into infinite loop??!!
    const int items_per_consumer = 250'000;
    const int total_items = 4 * items_per_producer;
    


    for (int p = 0; p < 4; ++p) {
        producers.emplace_back([&queue, p]() {
            int start = p * items_per_producer;
            int end = start + items_per_producer;
            for (int i = start; i < end; ++i) {
                queue.enqueue(i);
            }
        });
    }

    for (int c = 0; c < 4; ++c) {
        consumers.emplace_back([&queue, &results, &results_mutex]() {
            for (int i = 0; i < items_per_consumer; ++i) {
                int item;
                queue.dequeue(item);

                {
                    std::lock_guard<std::mutex> lock(results_mutex);
                    results.push_back(item);
                }
            }
        });
    }

    for (auto& consumer : consumers) {
        consumer.join();
    }

    for (auto& producer : producers) {
        producer.join();
    }

    ASSERT_EQUAL(results.size(), total_items);

END_TEST

/*------------------------------------------------------------------------------------------*/

BEGIN_SUITE(blocking_bounded_queue_tests)
    // Basic Tests
    TEST(test_constructor)
    TEST(test_enqueue_lvalue)
    TEST(test_enqueue_rvalue)
    TEST(test_dequeue)
    TEST(test_empty)
    TEST(test_full)
    TEST(test_size_and_capacity)

    // Intensive Tests
    TEST(fifo_single_thread)
    TEST(fifo_single_producer_single_consumer)
    TEST(fifo_two_producers_one_consumer)
    TEST(fifo_one_producer_two_consumers)
    TEST(fifo_four_producers_four_consumers)
END_SUITE