#include <iostream>
#include <cmath>
#include <list>
#include <vector>

#include "mu_test.h"
#include "utils/algorithms.hpp"
#include "basic/rational.hpp"

BEGIN_TEST(test_fill_sequence)
    int arr[]{1, 2, 3, 4, 5, 6, 7};
    utils::fill_sequence(arr, arr + 5, 9);
    for(int i = 0; i < 5; ++i) {
        ASSERT_THAT(arr[i] == 9+i);
    }
END_TEST

int is_even(int a)
{
    return (a % 2 == 0);
}

BEGIN_TEST(test_map_unaryFunc)
    int arr[]{1, 2, 3, 4, 5, 6, 7};
    utils::map(arr, arr + 5, is_even);
    for(int i = 0; i < 5; ++i) {
        ASSERT_EQUAL(arr[i], ((i + 1) % 2 == 0));
    }
END_TEST

int is_even_binary(int a, int b)
{
    return !(a & 1) && !(b & 1);
}

BEGIN_TEST(test_map_binaryFunc)
    int arr1[]{1, 2, 3, 4, 5, 6, 8};
    int arr2[]{8, 9, 10, 11, 12, 13, 14};
    int arr3[7];
    utils::map(arr1, arr1 + 7, arr2, arr3, is_even_binary);

    for(int i = 0; i < 6; ++i) {
        ASSERT_EQUAL(arr3[i], 0);
    }
    ASSERT_EQUAL(arr3[6], 1);
END_TEST

BEGIN_TEST(test_partition_function)
    int arr[]{9, 3, 5, 8, 2, 6, 7, 1, 4};
    int pivot = 5;

    utils::partition(arr, arr + 7, pivot);
    // index of pivot after partition is 2
    for(int i = 0; i < 2; ++i) {
        ASSERT_THAT(arr[i] <= 5);
    }
    for(int i = 3; i < 7; ++i) {
        ASSERT_THAT(arr[i] >= 5);
    }
    ASSERT_EQUAL(arr[7], 1);
    ASSERT_EQUAL(arr[8], 4);
END_TEST

bool is_even_bool(int x) 
{
    return (x % 2) == 0;
}

BEGIN_TEST(test_partition_function_predicate_func)
    int arr[]{9, 3, 5, 8, 2, 6, 7, 11, 4};
    int expected_arr[]{8, 2, 6, 9, 3, 5, 7, 11, 4};

    utils::partition(arr, arr + 7, is_even_bool, 1);

    for(int i = 0; i < 9; ++i) {
        ASSERT_THAT(arr[i] == expected_arr[i]);
    }
END_TEST

BEGIN_TEST(test_print_range_vector)
    std::vector<int> primes{2, 3, 5, 7, 11, 13, 17};
    //utils::print(primes.begin() + 1, primes.end());
    std::ostringstream oss;
    utils::print(oss, primes.begin() + 1, primes.end());
    ASSERT_EQUAL(oss.str(), "[3, 5, 7, 11, 13, 17]\n");
END_TEST

BEGIN_TEST(test_print_list)
    std::list<int> lst{1, 2, 3, 4, 5, 6, 7};
    //utils::print(lst);
    std::ostringstream oss;
    utils::print(oss, lst);
    std::string expected = "[1, 2, 3, 4, 5, 6, 7]\n";
    ASSERT_EQUAL(oss.str(), expected);
END_TEST

BEGIN_TEST(test_find_first_list)
    std::list<int> lst{1, 3, 5, 6, 7, 8, 9};
    std::list<int>::iterator r = utils::find_first(lst.begin(), lst.end(), is_even);
    ASSERT_THAT(r != lst.end());
    ASSERT_EQUAL(*r, 6);
END_TEST

BEGIN_TEST(test_find_first_not_exists_list)
    std::list<int> lst{1, 3, 5, 7, 9};
    std::list<int>::iterator r = utils::find_first(lst.begin(), lst.end(), is_even);
    ASSERT_THAT(r == lst.end());
END_TEST

int raise_to_thord_power(int a) 
{
    return pow(a, 3);
}

BEGIN_TEST(test_map_using_vector)
    std::vector<int> arr{2, 3, 5, 7};
    int expected[]{8, 27, 125, 343};
    utils::map(arr.begin(), arr.end(), raise_to_thord_power);
    for(int i = 0; i < 4; ++i) {
        ASSERT_THAT(arr[i] == expected[i]);
    }
END_TEST

bool is_positive_bool(basic::Rational x) 
{
    return (x > 0);
}

BEGIN_TEST(test_partition_using_rational_vector_with_predicate_func)
    std::vector<basic::Rational> arr{{-9, 3}, -3, -5, {8, 2}, 2, {6, 3}, -7};
    basic::Rational expected_arr[]{{8, 2}, 2, {6, 3}, {-9, 3}, -3, -5, -7};
    utils::partition(arr.begin(), arr.end(), is_positive_bool, 1);
    for(int i = 0; i < 7; ++i) {
        ASSERT_THAT(arr[i] == expected_arr[i]);
    }
END_TEST

TEST_SUITE()
    TEST(test_fill_sequence)
    TEST(test_map_unaryFunc)
    TEST(test_map_binaryFunc)
    TEST(test_partition_function)
    TEST(test_partition_function_predicate_func)

    TEST(test_print_range_vector)
    TEST(test_print_list)
    TEST(test_find_first_list)
    TEST(test_find_first_not_exists_list)
    TEST(test_map_using_vector)
    TEST(test_partition_using_rational_vector_with_predicate_func)
END_SUITE