#include "mu_test.h"

#include <cstddef>
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <thread>
#include <chrono>
#include <limits>

#include "mt/algorithm.hpp" // must include template definitions

constexpr size_t size = 10'000'000;

template<typename T>
void initialize_vector(std::vector<T>& vec)
{
    size_t i = 0;
    std::for_each(vec.begin(), vec.end(), [&](T& v) {
        v = i++;
    });

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(vec.begin(), vec.end(), gen);
}

template<typename T, typename Func>
void calc_time(std::vector<T> const& vec, double& time_run, size_t thrds_num, Func func)
{
    auto start = std::chrono::high_resolution_clock::now();

    func(vec, thrds_num); // executes find_max or calc_sum

    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::milli> duration_ms = end - start;
    time_run = duration_ms.count();
    std::cout << "Execution time with " << thrds_num << " threads: " << time_run << " ms\n";
}

BEGIN_TEST(test_find_max)
    std::vector<int> big_vec(size);
    initialize_vector(big_vec);

    double opt_time = std::numeric_limits<double>::max();
    size_t opt_thrds_num = 1;

    for (size_t i = 1; i <= 100; ++i) {
        double current_time{};
        calc_time(big_vec, current_time, i, mt::find_max_using_thrds<int>);
        if (current_time < opt_time) {
            opt_time = current_time;
            opt_thrds_num = i;
        }
    }

    std::cout << "\nBest Execution time: " << opt_time << " ms with " << opt_thrds_num << " threads\n";
    ASSERT_PASS();
END_TEST

BEGIN_TEST(test_calc_sum)
    std::vector<int> big_vec(size);
    initialize_vector(big_vec);

    double opt_time = std::numeric_limits<double>::max();
    size_t opt_thrds_num = 1;

    for (size_t i = 1; i <= 100; ++i) {
        double current_time{};
        calc_time(big_vec, current_time, i, mt::calc_sum_using_thrds<int>);
        if (current_time < opt_time) {
            opt_time = current_time;
            opt_thrds_num = i;
        }
    }

    std::cout << "\nBest Execution time: " << opt_time << " ms with " << opt_thrds_num << " threads\n";
    ASSERT_PASS();
END_TEST

BEGIN_TEST(test_find_max_throws_on_empty_or_zero_threads)
    std::vector<int> empty_vec;
    bool caught = false;

    try {
        mt::find_max_using_thrds<int>(empty_vec, 1);
    } catch (const std::invalid_argument&) {
        caught = true;
    }
    ASSERT_THAT(caught);

    caught = false;
    try {
        mt::find_max_using_thrds<int>({1, 2, 3}, 0);
    } catch (const std::invalid_argument&) {
        caught = true;
    }
    ASSERT_THAT(caught);
END_TEST

BEGIN_TEST(test_calc_sum_throws_on_empty_or_zero_threads)
    std::vector<int> empty_vec;
    bool caught = false;

    try {
        mt::calc_sum_using_thrds<int>(empty_vec, 1);
    } catch (const std::invalid_argument&) {
        caught = true;
    }
    ASSERT_THAT(caught);

    caught = false;
    try {
        mt::calc_sum_using_thrds<int>({1, 2, 3}, 0);
    } catch (const std::invalid_argument&) {
        caught = true;
    }
    ASSERT_THAT(caught);
END_TEST


TEST_SUITE(thread_tests)
    TEST(test_find_max)
    TEST(test_calc_sum)
    TEST(test_find_max_throws_on_empty_or_zero_threads)
    TEST(test_calc_sum_throws_on_empty_or_zero_threads)
END_SUITE
