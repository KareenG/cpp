#include <iostream>

#include "mu_test.h"
#include "utils/utility.hpp"
#include "basic/rational.hpp"

BEGIN_TEST(clamp_int)
    int min_val = 0;
    int max_val = 100;
    int intTest1 = utils::clamp(min_val, max_val, -10);
    ASSERT_EQUAL(intTest1, 0);
    int intTest2 = utils::clamp(min_val, max_val, 50);
    ASSERT_EQUAL(intTest2, 50);
    int intTest3 = utils::clamp(min_val, max_val, 150);
    ASSERT_EQUAL(intTest3, 100);
END_TEST

BEGIN_TEST(clamp_double)
    double min_val = 0.0;
    double max_val = 100.0;
    double intTest1 = utils::clamp(min_val, max_val, -10.55);
    ASSERT_EQUAL(intTest1, 0.0);
    double intTest2 = utils::clamp(min_val, max_val, 50.75);
    ASSERT_EQUAL(intTest2, 50.75);
    double intTest3 = utils::clamp(min_val, max_val, 150.2);
    ASSERT_EQUAL(intTest3, 100.0);
END_TEST

BEGIN_TEST(clamp_rational)
    std::vector<basic::Rational> arr{{-9, 3}, -3, -5, {8, 2}, 2, {6, 3}, -7, {1, 3}};
    basic::Rational min_val = 0;
    basic::Rational max_val = 6;
    basic::Rational expected_arr[]{0, 0, 0, 4, 2, 2, 0, {1, 3}};
    for(int i = 0; i < 7; ++i) {
        ASSERT_THAT(utils::clamp(min_val, max_val, arr[i]) == expected_arr[i]);
    }
END_TEST

TEST_SUITE()
    TEST(clamp_int)
    TEST(clamp_double)
    TEST(clamp_rational)
END_SUITE