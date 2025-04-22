#pragma once

#include <algorithm>
#include <numeric>

#include "mt/algorithm.hpp"

namespace mt
{

class WorkerThreads {
public:
    explicit WorkerThreads(size_t num, const std::function<void(size_t)>& work)
    {
        threads_.reserve(num);
        for (size_t i = 0; i < num; ++i) {
            threads_.emplace_back([=]() { work(i); });
        }
    }

    void join()
    {
        for (auto& t : threads_) {
            if (t.joinable()) t.join();
        }
    }

    ~WorkerThreads()
    {
        join();
    }

private:
    std::vector<std::thread> threads_;
};
    
struct Range {
    size_t begin;
    size_t end;
};
    
template<typename T>
T find_max_using_thrds(const std::vector<T>& vec, size_t num_thrd)
{
    if (vec.empty()) {
        throw std::invalid_argument("Input vector is empty");
    }

    if (num_thrd == 0) {
        throw std::invalid_argument("Number of threads must be greater than zero");
    }

    num_thrd = std::min(num_thrd, vec.size());

    std::vector<T> sub_max_vec(num_thrd);
    size_t chunk_size = vec.size() / num_thrd;

    // Prepare chunk ranges
    size_t begin{};
    std::vector<Range> ranges(num_thrd);
    for (size_t i = 0; i < num_thrd; ++i) {
        size_t end = (i == num_thrd - 1) ? vec.size() : begin + chunk_size;
        ranges[i] = {begin, end};
        begin += chunk_size;
    }

    // Main thread handles chunk 0
    sub_max_vec[0] = *std::max_element(&vec[ranges[0].begin], &vec[ranges[0].end]);

    // Worker function
    auto work = [&](size_t i) {
        const Range& r = ranges[i + 1]; // because main thread did chunk 0
        sub_max_vec[i + 1] = *std::max_element(&vec[r.begin], &vec[r.end]);
    };

    WorkerThreads ws(num_thrd - 1, work);
    ws.join();

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
