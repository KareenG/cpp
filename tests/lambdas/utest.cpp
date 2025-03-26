#include <iostream>
#include <algorithm>
#include <cmath>
#include <list>
#include <vector>

#include "mu_test.h"
#include "utils/algorithms.hpp"
#include "basic/rational.hpp"

BEGIN_TEST(test_minimal_average)
    //int n = 6;
    std::vector<int> numbers{16 ,2 ,4, 6, 2, 12};
    std::list<float> averages{};
    std::vector<int>::iterator min_element;
    std::vector<int>::iterator max_element;
    float result;
    float min_avg{INFINITY};
    ASSERT_THAT(numbers.size() % 2 == 0);
    while (!numbers.empty()) {     //for(int i = 0; i < n / 2; ++i) {
        min_element = std::min_element(numbers.begin(), numbers.end());
        max_element = std::max_element(numbers.begin(), numbers.end());
        result = (float(*min_element) + *max_element) / 2.0f;
        // Erase in correct order to avoid invalidating the other iterator
        if (min_element > max_element) {
            numbers.erase(min_element);
            numbers.erase(max_element);
        } else {
            numbers.erase(max_element);
            numbers.erase(min_element);
        }
        averages.push_back(result);
        if(min_avg > result) {
            min_avg = result;
        }
    }
    ASSERT_EQUAL(min_avg, 5);
END_TEST




TEST_SUITE()
    TEST(test_minimal_average)
END_SUITE