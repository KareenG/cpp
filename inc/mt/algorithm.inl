#pragma once

#include <algorithm>
#include <numeric>

#include "mt/algorithm.hpp"

namespace mt
{

template<typename T>
T find_max_using_thrds(const std::vector<T>& vec, size_t num_thrd)
{
    if (vec.empty()) {
        throw std::invalid_argument("Input vector is empty");
    }

    if (num_thrd == 0) {
        throw std::invalid_argument("Number of threads must be greater than zero");
    }

    // for num_thrd = vec.size() each thread will return the single value he got
    num_thrd = std::min(num_thrd, vec.size());

    std::vector<std::thread> threads;
    threads.reserve(num_thrd);
    
    std::vector<T> sub_max_vec;
    sub_max_vec.reserve(num_thrd);

    size_t size = vec.size();
    size_t chunk_size = size / num_thrd;

    size_t current_begin = 0;
    for(size_t i = 0; i < num_thrd; ++i) {
        size_t current_end = (i == num_thrd - 1) ? size : current_begin + chunk_size;
        threads.emplace_back([&, i, current_begin, current_end]() {
            sub_max_vec[i] = *std::max_element(&vec[current_begin], &vec[current_end]);
        });
        current_begin += chunk_size;
    }

    for(auto& t : threads) {
        t.join();
    }
    
    return *std::max_element(sub_max_vec.begin(), sub_max_vec.end());
}

template<typename T>
size_t calc_sum_using_thrds(const std::vector<T>& vec, size_t num_thrd)
{
    if (vec.empty()) {
        throw std::invalid_argument("Input vector is empty");
    }

    if (num_thrd == 0) {
        throw std::invalid_argument("Number of threads must be greater than zero");
    }

    num_thrd = std::min(num_thrd, vec.size());

    std::vector<std::thread> threads;
    threads.reserve(num_thrd);

    std::vector<T> partial_sums(num_thrd, T{});

    size_t size = vec.size();
    size_t chunk_size = size / num_thrd;

    size_t current_begin = 0;
    for(size_t i = 0; i < num_thrd; ++i) {
        size_t current_end = (i == num_thrd - 1) ? size : current_begin + chunk_size;
        threads.emplace_back([&, i, current_begin, current_end](){
            partial_sums[i] = std::accumulate(&vec[current_begin], &vec[current_end], T{});
        });
        current_begin += chunk_size;
    }

    for(auto& t : threads) {
        t.join();
    }
    
    return std::accumulate(partial_sums.begin(), partial_sums.end(), T{});
}

} // namespace mt
