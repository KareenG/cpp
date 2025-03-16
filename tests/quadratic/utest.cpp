#include "mu_test.h"
#include "basic/quadratic.hpp"

BEGIN_TEST(test_find_roots_two_real)
    basic::Quadratic q(1, -5, 6);  // Roots should be (3, 2)
    basic::Roots roots;
    int num_roots = basic::find_roots(q, roots);
    ASSERT_THAT(num_roots == 2);
    ASSERT_THAT((roots.first == 3 && roots.second == 2) || (roots.first == 2 && roots.second == 3));
END_TEST

BEGIN_TEST(test_find_roots_one_real)
    basic::Quadratic q(1, -2, 1);  // Root should be (1)
    basic::Roots roots;
    int num_roots = basic::find_roots(q, roots);
    ASSERT_EQUAL(num_roots, 1);
    ASSERT_EQUAL(roots.first, 1);
END_TEST

BEGIN_TEST(test_find_roots_no_real)
    basic::Quadratic q(1, 1, 1);  // No real roots
    basic::Roots roots;
    int num_roots = basic::find_roots(q, roots);
    ASSERT_EQUAL(num_roots, 0);
END_TEST

BEGIN_TEST(test_quadratic_with_a_zero)
    basic::Quadratic q(0, -4, 12);
    basic::Roots roots;
    int num_roots = basic::find_roots(q, roots);
    ASSERT_EQUAL(num_roots, 0);
    ASSERT_THAT(roots.first == -1 && roots.second == -1);
END_TEST


BEGIN_TEST(test_value_at_x)
    basic::Quadratic q(1, -2, 1);  // (x-1)^2
    double value = basic::value(q, 1);  // Should be 0
    ASSERT_EQUAL(value, 0);
END_TEST

BEGIN_TEST(test_value_at_different_x)
    basic::Quadratic q(2, -4, 2);  // 2(x-1)^2
    double value = basic::value(q, 3);  // Should be 8
    ASSERT_EQUAL(value, 8);
END_TEST

// BEGIN_TEST(test_print_quadratic)
//     basic::Quadratic q(3.4, -4.1, 12.3);
//     std::stringstream ss;
//     std::streambuf* originalBuf = std::cout.rdbuf();
//     std::cout.rdbuf(ss.rdbuf());  // Redirect std::cout to stringstream for capturing output.
//     basic::print(q);//.print();
//     std::cout.rdbuf(originalBuf);  // Reset std::cout to its original state.
//     ASSERT_EQUAL(ss.str(), "3.40 X^2 - 4.10 X + 12.30\n");  // Assume you have std::fixed << std::setprecision(2) in your print function
// END_TEST

BEGIN_TEST(test_addition_quadratics)
    basic::Quadratic q1(1, 2, 3);
    basic::Quadratic q2(1, -2, -3);
    q1 += q2;
    ASSERT_EQUAL(q1.a, 2);
    ASSERT_EQUAL(q1.b, 0);
    ASSERT_EQUAL(q1.c, 0);
END_TEST

BEGIN_TEST(test_subtraction_quadratics)
    basic::Quadratic q1(3, 3, 3);
    basic::Quadratic q2(1, 1, 1);
    q1 -= q2;
    ASSERT_EQUAL(q1.a, 2);
    ASSERT_EQUAL(q1.b, 2);
    ASSERT_EQUAL(q1.c, 2);
END_TEST

BEGIN_TEST(test_multiplication_by_scalar)
    basic::Quadratic q(1, -1, 1);
    q = basic::multiply_by_scalar(q, 2);
    ASSERT_EQUAL(q.a, 2);
    ASSERT_EQUAL(q.b, -2);
    ASSERT_EQUAL(q.c, 2);
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

    // Arithmetic operations tests
    TEST(test_addition_quadratics)
    TEST(test_subtraction_quadratics)

    // Scalar multiplication test
    TEST(test_multiplication_by_scalar)

    // // Printing functionality test
    // TEST(test_print_quadratic)

END_SUITE
