#include "mu_test.h"
#include "basic/quadratic.hpp"

BEGIN_TEST(test_find_roots_two_real)
    basic::Quadratic q(1, -5, 6);
    basic::Roots roots;
    int num_roots = q.find_roots(roots);
    ASSERT_THAT(num_roots == 2);
    ASSERT_THAT((roots.first == 3 && roots.second == 2) || (roots.first == 2 && roots.second == 3));
END_TEST

BEGIN_TEST(test_find_roots_one_real)
    basic::Quadratic q(1, -2, 1);  
    basic::Roots roots;
    int num_roots = q.find_roots(roots);
    ASSERT_EQUAL(num_roots, 1);
    ASSERT_EQUAL(roots.first, 1);
END_TEST

BEGIN_TEST(test_find_roots_no_real)
    basic::Quadratic q(1, 1, 1);
    basic::Roots roots;
    int num_roots = q.find_roots(roots);
    ASSERT_EQUAL(num_roots, 0);
END_TEST

BEGIN_TEST(test_quadratic_with_a_zero)
    basic::Quadratic q(0, -4, 12);
    basic::Roots roots;
    int num_roots = q.find_roots(roots);
    ASSERT_EQUAL(num_roots, 0);
    ASSERT_THAT(roots.first == -1 && roots.second == -1);
END_TEST

BEGIN_TEST(test_value_at_x)
    basic::Quadratic q(1, -2, 1);
    double value = q.value(1);
    ASSERT_EQUAL(value, 0);
END_TEST

BEGIN_TEST(test_value_at_different_x)
    basic::Quadratic q(2, -4, 2);
    double value = q.value(3);
    ASSERT_EQUAL(value, 8);
END_TEST

BEGIN_TEST(test_addition_quadratics)
    basic::Quadratic q1(1, 2, 3);
    basic::Quadratic q2(1, -2, -3);
    basic::Quadratic result = q1.add(q2);
    ASSERT_EQUAL(result.a, 2);
    ASSERT_EQUAL(result.b, 0);
    ASSERT_EQUAL(result.c, 0);
END_TEST

BEGIN_TEST(test_subtraction_quadratics)
    basic::Quadratic q1(3, 3, 3);
    basic::Quadratic q2(1, 1, 1);
    basic::Quadratic result = q1.subtract(q2);
    ASSERT_EQUAL(result.a, 2);
    ASSERT_EQUAL(result.b, 2);
    ASSERT_EQUAL(result.c, 2);
END_TEST

BEGIN_TEST(test_multiplication_by_scalar)
    basic::Quadratic q(1, -1, 1);
    basic::Quadratic result = q.multiply_by_scalar(2);
    ASSERT_EQUAL(result.a, 2);
    ASSERT_EQUAL(result.b, -2);
    ASSERT_EQUAL(result.c, 2);
END_TEST

TEST_SUITE()
    // Root finding tests
    TEST(test_find_roots_two_real)
    TEST(test_find_roots_one_real)
    TEST(test_find_roots_no_real)
    TEST(test_quadratic_with_a_zero)
    
    // Polynomial value computation tests
    TEST(test_value_at_x)
    TEST(test_value_at_different_x)

    // add operation tests
    TEST(test_addition_quadratics)

    // subtract operation tests
    TEST(test_subtraction_quadratics)

    // Scalar multiplication test
    TEST(test_multiplication_by_scalar)
END_SUITE
