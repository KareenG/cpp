#include "mu_test.h"
#include "basic/rational.hpp"
#include <cassert>
#include <iostream>

BEGIN_TEST(test_rational_default_constructor)
    basic::Rational r{};
    ASSERT_EQUAL(r[0], 0);
    ASSERT_EQUAL(r[1], 1);
END_TEST

BEGIN_TEST(test_rational_parameterized_constructor)
    basic::Rational r(4, 3);
    ASSERT_EQUAL(r[0], 4);
    ASSERT_EQUAL(r[1], 3);
END_TEST

BEGIN_TEST(test_rational_inverse)
    basic::Rational r(4, 3);
    basic::Rational inv = r.inverse();
    ASSERT_EQUAL(inv[0], 3);
    ASSERT_EQUAL(inv[1], 4);
END_TEST

BEGIN_TEST(test_rational_addition)
    basic::Rational r1(3, 7);
    basic::Rational r2(1, 2);
    basic::Rational result = r1 + r2;
    ASSERT_EQUAL(result[0], 13);
    ASSERT_EQUAL(result[1], 14);
END_TEST

BEGIN_TEST(test_rational_subtraction)
    basic::Rational r1(3, 7);
    basic::Rational r2(1, 2);
    basic::Rational result = r1 - r2;
    ASSERT_EQUAL(result[0], -1);
    ASSERT_EQUAL(result[1], 14);
END_TEST

BEGIN_TEST(test_rational_multiplication)
    basic::Rational r1(1, 2);
    basic::Rational r2(2, 3);
    basic::Rational result = r1 * r2;
    ASSERT_EQUAL(result[0], 2);
    ASSERT_EQUAL(result[1], 6);
END_TEST

BEGIN_TEST(test_rational_division)
    basic::Rational r1(1, 2);
    basic::Rational r2(2, -3);
    basic::Rational result = r1 / r2;
    ASSERT_EQUAL(result[0], -3);
    ASSERT_EQUAL(result[1], 4);
END_TEST

BEGIN_TEST(test_rational_reduce)
    basic::Rational r(100, 200);
    r.reduce();
    ASSERT_EQUAL(r[0], 1);
    ASSERT_EQUAL(r[1], 2);
END_TEST

BEGIN_TEST(test_rational_value)
    basic::Rational r(3, -4);
    double val = static_cast<double>(r);
    ASSERT_THAT(val == -0.75);
END_TEST

BEGIN_TEST(test_rational_comparisons)
    basic::Rational r1(1, 2);
    basic::Rational r2(2, 4);
    ASSERT_THAT(r1 == r2);
END_TEST

BEGIN_TEST(test_rational_assignment_operations)
    basic::Rational r1(1, 3);
    basic::Rational r2(3, 7);
    r1 = r2;
    ASSERT_THAT(r1 == r2);
END_TEST

BEGIN_TEST(test_rational_inverse_and_value_check)
    basic::Rational r(4, 3);
    ASSERT_THAT(r.inverse().value() == (1 / r.value()));
END_TEST

BEGIN_TEST(test_rational_output_stream)
    basic::Rational r(3, 7);
    std::ostringstream os;
    os << r;
    ASSERT_EQUAL(os.str(), "3/7\n");
END_TEST

BEGIN_TEST(test_rational_comparison_operators)
    basic::Rational g(3, 7);
    basic::Rational f(1, 2);
    ASSERT_THAT((g <= f));
END_TEST


TEST_SUITE()
    TEST(test_rational_default_constructor)
    TEST(test_rational_parameterized_constructor)
    TEST(test_rational_inverse)
    TEST(test_rational_addition)
    TEST(test_rational_subtraction)
    TEST(test_rational_multiplication)
    TEST(test_rational_division)
    TEST(test_rational_reduce)
    TEST(test_rational_value)
    TEST(test_rational_comparisons)
    TEST(test_rational_assignment_operations)
    TEST(test_rational_inverse_and_value_check)
    TEST(test_rational_output_stream)
    TEST(test_rational_comparison_operators)
END_SUITE
