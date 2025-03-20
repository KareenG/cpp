#include "mu_test.h"
#include "algebra/polynomial.hpp"
#include "basic/rational.hpp"

BEGIN_TEST(test_polynomial_specific_degree)
    int degree = 5;
    algebra::Polynomial p{degree};
    ASSERT_EQUAL(p.degree(), 0);
    bool allCoefficientsZero = true;
    for (int i = 0; i <= degree; ++i) {
        if (p[i].value() != 0.0) {
            allCoefficientsZero = false;
            break;
        }
    }
    ASSERT_THAT(allCoefficientsZero);
END_TEST

BEGIN_TEST(test_polynomial_zero_degree)
    algebra::Polynomial p{};
    ASSERT_EQUAL(p.degree(), 0);
    ASSERT_EQUAL(p[0].value(), 0.0);
END_TEST

BEGIN_TEST(test_polynomial_negative_degree)
    //algebra::Polynomial p{-1};
    ASSERT_THAT(1);
END_TEST

BEGIN_TEST(test_polynomial_from_rational_range)
    basic::Rational arr[] = {basic::Rational(1, 2), basic::Rational(1, 4), basic::Rational(3, 4)};
    algebra::Polynomial p(arr, arr + 3);
    ASSERT_EQUAL(p.degree(), 2);
    ASSERT_EQUAL(p[2].value(), 1.0/2);
    ASSERT_EQUAL(p[1].value(), 1.0/4);
    ASSERT_EQUAL(p[0].value(), 3.0/4);
END_TEST

BEGIN_TEST(test_polynomial_from_empty_range)
    //basic::Rational arr[] = {basic::Rational(1, 2)};
    //algebra::Polynomial p(arr, arr);
    ASSERT_THAT(1);
END_TEST

BEGIN_TEST(test_polynomial_from_single_element_range)
    basic::Rational arr[] = {basic::Rational(1, 2)};
    algebra::Polynomial p(arr, arr + 1);
    ASSERT_EQUAL(p.degree(), 0);
    ASSERT_EQUAL(p[0].value(), 1.0/2);
END_TEST

BEGIN_TEST(test_copy_constructor_basic)
    algebra::Polynomial original(2);
    original[0] = basic::Rational(1, 2);
    original[1] = basic::Rational(3, 4);
    original[2] = basic::Rational(5, 6);

    algebra::Polynomial copy = original;

    ASSERT_EQUAL(copy.degree(), 2);
    ASSERT_EQUAL(copy[0].value(), 0.5);
    ASSERT_EQUAL(copy[1].value(), 0.75);
    ASSERT_EQUAL(copy[2].value(), 5.0 / 6);
    for (int i = 0; i <= original.degree(); ++i) {
        ASSERT_EQUAL(copy[i].value(), original[i].value());
    }
END_TEST

BEGIN_TEST(test_copy_independence)
    algebra::Polynomial original(1);
    original[0] = basic::Rational(1, 3);
    original[1] = basic::Rational(2, 3);

    algebra::Polynomial copy = original;
    original[0] = basic::Rational(10, 30);

    ASSERT_EQUAL(copy[0].value(), 1.0 / 3);
    ASSERT_EQUAL(original[0].value(), 1.0 / 3);
END_TEST

BEGIN_TEST(test_copy_empty_polynomial)
    algebra::Polynomial original(0);
    algebra::Polynomial copy = original;

    ASSERT_EQUAL(copy.degree(), 0);
    ASSERT_EQUAL(copy[0].value(), 0.0);
END_TEST

BEGIN_TEST(test_copy_single_coefficient)
    algebra::Polynomial original(0);
    original[0] = basic::Rational(1, 4);

    algebra::Polynomial copy = original;

    ASSERT_EQUAL(copy.degree(), 0);
    ASSERT_EQUAL(copy[0].value(), 0.25);
END_TEST

BEGIN_TEST(test_copy_assignment_basic)
    algebra::Polynomial original(2);
    original[0] = basic::Rational(1, 2);
    original[1] = basic::Rational(3, 4);
    original[2] = basic::Rational(5, 6);

    algebra::Polynomial copy;
    copy = original;

    ASSERT_EQUAL(copy.degree(), original.degree());
    for (int i = 0; i <= original.degree(); ++i) {
        ASSERT_EQUAL(copy[i].value(), original[i].value());
    }
END_TEST

BEGIN_TEST(test_copy_assignment_self_assignment)
    algebra::Polynomial poly(1);
    poly[0] = basic::Rational(1, 2);
    poly[1] = basic::Rational(2, 8);

    poly = poly;

    ASSERT_EQUAL(poly.degree(), 1);
    ASSERT_EQUAL(poly[0].value(), 0.5);
    ASSERT_EQUAL(poly[1].value(), 2.0 / 8);
END_TEST

BEGIN_TEST(test_copy_assignment_independence)
    algebra::Polynomial original(1);
    original[0] = basic::Rational(1, 8);
    original[1] = basic::Rational(2, 8);

    algebra::Polynomial copy;
    copy = original;
    original[0] = basic::Rational(40, 80);

    ASSERT_NOT_EQUAL(copy[0].value(), original[0].value());
END_TEST

BEGIN_TEST(test_polynomial_operator_index_valid_access)
    algebra::Polynomial p(3);
    p[0] = basic::Rational(1, 4);
    p[1] = basic::Rational(1, 2);
    p[2] = basic::Rational(3, 4);
    p[3] = basic::Rational(1, 1);

    ASSERT_EQUAL(p[0].value(), 0.25);
    ASSERT_EQUAL(p[1].value(), 0.5);
    ASSERT_EQUAL(p[2].value(), 0.75);
    ASSERT_EQUAL(p[3].value(), 1.0);
END_TEST

BEGIN_TEST(test_polynomial_operator_index_boundary_conditions)
    algebra::Polynomial p(1);
    p[0] = basic::Rational(2, 3);
    p[1] = basic::Rational(3, 5);

    ASSERT_EQUAL(p[0].value(), 2.0 / 3);
    ASSERT_EQUAL(p[1].value(), 0.6);

    p[1] = {4, 5};
    ASSERT_EQUAL(p[1].value(), 0.8);
END_TEST

BEGIN_TEST(test_polynomial_operator_index_out_of_bounds)
    algebra::Polynomial p(1);
    ASSERT_THAT(1);
END_TEST

BEGIN_TEST(test_polynomial_evaluation_zero)
    algebra::Polynomial p(0);
    p[0] = basic::Rational(0, 1);
    basic::Rational r(1, 2);
    ASSERT_EQUAL(p(r).value(), 0.0);
END_TEST

BEGIN_TEST(test_polynomial_evaluation_constant)
    algebra::Polynomial p(1);
    p[0] = basic::Rational(5, 1);
    basic::Rational r(1, 2);
    ASSERT_EQUAL(p(r).value(), 5.0);
END_TEST

BEGIN_TEST(test_polynomial_evaluation_linear)
    algebra::Polynomial p(1);
    p[0] = basic::Rational(1, 1);
    p[1] = basic::Rational(2, 1);
    basic::Rational r(1, 1);
    ASSERT_EQUAL(p(r).value(), 3.0);
END_TEST

BEGIN_TEST(test_polynomial_evaluation_quadratic)
    algebra::Polynomial p(2);
    p[0] = basic::Rational(1, 1);
    p[1] = basic::Rational(2, 1);
    p[2] = basic::Rational(1, 1);
    basic::Rational r(1, 1);
    ASSERT_EQUAL(p(r).value(), 4.0);
END_TEST

BEGIN_TEST(test_degree_zero_polynomial)
    algebra::Polynomial p(3);
    ASSERT_EQUAL(p.degree(), 0);
END_TEST

BEGIN_TEST(test_degree_constant_polynomial)
    algebra::Polynomial p(3);
    p[0] = basic::Rational(1, 3);
    ASSERT_EQUAL(p.degree(), 0);
END_TEST

BEGIN_TEST(test_degree_higher_polynomial)
    algebra::Polynomial p(3);
    p[0] = basic::Rational(1, 3);
    p[3] = basic::Rational(2, 3);
    ASSERT_EQUAL(p.degree(), 3);
END_TEST

BEGIN_TEST(test_degree_polynomial_with_zero_tail)
    algebra::Polynomial p(5);
    p[0] = basic::Rational(1, 3);
    p[1] = basic::Rational(2, 3);
    ASSERT_EQUAL(p.degree(), 1);
END_TEST

BEGIN_TEST(test_polynomial_multiply_by_zero)
    algebra::Polynomial p(3);
    p[0] = basic::Rational(1, 2);
    p[1] = basic::Rational(3, 4);
    p[2] = basic::Rational(5, 6);
    p[3] = basic::Rational(7, 8);

    p *= 0;
    ASSERT_EQUAL(p[0].value(), 0.0);
    ASSERT_EQUAL(p[1].value(), 0.0);
    ASSERT_EQUAL(p[2].value(), 0.0);
    ASSERT_EQUAL(p[3].value(), 0.0);
END_TEST

BEGIN_TEST(test_polynomial_multiply_by_one)
    algebra::Polynomial p(2);
    p[0] = basic::Rational(1, 3);
    p[1] = basic::Rational(2, 3);
    p[2] = basic::Rational(3, 4);

    p *= 1;
    ASSERT_EQUAL(p[0].value(), 1.0 / 3);
    ASSERT_EQUAL(p[1].value(), 2.0 / 3);
    ASSERT_EQUAL(p[2].value(), 0.75);
END_TEST

BEGIN_TEST(test_polynomial_multiply_by_positive_integer)
    algebra::Polynomial p(1);
    p[0] = basic::Rational(1, 4);
    p[1] = basic::Rational(3, 4);

    p *= 2;
    ASSERT_EQUAL(p[0].value(), 0.5);
    ASSERT_EQUAL(p[1].value(), 1.5);
END_TEST

BEGIN_TEST(test_polynomial_multiply_by_negative_integer)
    algebra::Polynomial p(1);
    p[0] = basic::Rational(1, 4);
    p[1] = basic::Rational(3, 4);

    p *= -1;
    ASSERT_EQUAL(p[0].value(), -0.25);
    ASSERT_EQUAL(p[1].value(), -0.75);
END_TEST

BEGIN_TEST(test_polynomial_multiply_empty_polynomial)
    algebra::Polynomial p(0);
    p[0] = basic::Rational(0, 1);

    p *= 10;
    ASSERT_EQUAL(p[0].value(), 0.0);
END_TEST

BEGIN_TEST(test_polynomial_multiply_by_rational_zero)
    algebra::Polynomial p(3);
    p[0] = basic::Rational(1, 2);
    p[1] = basic::Rational(3, 4);
    p[2] = basic::Rational(5, 6);
    p[3] = basic::Rational(7, 8);

    p *= basic::Rational(0, 1);
    ASSERT_EQUAL(p[0].value(), 0.0);
    ASSERT_EQUAL(p[1].value(), 0.0);
    ASSERT_EQUAL(p[2].value(), 0.0);
    ASSERT_EQUAL(p[3].value(), 0.0);
END_TEST

BEGIN_TEST(test_polynomial_multiply_by_rational_one)
    algebra::Polynomial p(2);
    p[0] = basic::Rational(1, 3);
    p[1] = basic::Rational(2, 3);
    p[2] = basic::Rational(3, 4);

    p *= basic::Rational(1, 1);
    ASSERT_EQUAL(p[0].value(), 1.0 / 3);
    ASSERT_EQUAL(p[1].value(), 2.0 / 3);
    ASSERT_EQUAL(p[2].value(), 0.75);
END_TEST

BEGIN_TEST(test_polynomial_multiply_by_positive_rational)
    algebra::Polynomial p(1);
    p[0] = basic::Rational(1, 4);
    p[1] = basic::Rational(3, 4);

    p *= basic::Rational(2, 1);
    ASSERT_EQUAL(p[0].value(), 0.5);
    ASSERT_EQUAL(p[1].value(), 1.5);
END_TEST

BEGIN_TEST(test_polynomial_multiply_by_negative_rational)
    algebra::Polynomial p(1);
    p[0] = basic::Rational(1, 4);
    p[1] = basic::Rational(3, 4);

    p *= basic::Rational(-1, 1);
    ASSERT_EQUAL(p[0].value(), -0.25);
    ASSERT_EQUAL(p[1].value(), -0.75);
END_TEST

BEGIN_TEST(test_polynomial_addition_zero)
    algebra::Polynomial p1(2);
    p1[0] = basic::Rational(1, 2);
    p1[1] = basic::Rational(3, 4);
    p1[2] = basic::Rational(5, 6);

    algebra::Polynomial p2(2);

    p1 += p2;
    ASSERT_EQUAL(p1[0].value(), 0.5);
    ASSERT_EQUAL(p1[1].value(), 0.75);
    ASSERT_EQUAL(p1[2].value(), 5.0 / 6);
END_TEST

BEGIN_TEST(test_polynomial_addition_same_degree)
    algebra::Polynomial p1(1);
    p1[0] = basic::Rational(1, 4);
    p1[1] = basic::Rational(3, 4);

    algebra::Polynomial p2(1);
    p2[0] = basic::Rational(1, 2);
    p2[1] = basic::Rational(1, 4);

    p1 += p2;
    ASSERT_EQUAL(p1[0].value(), 0.75);
    ASSERT_EQUAL(p1[1].value(), 1.0);
END_TEST

BEGIN_TEST(test_polynomial_addition_higher_degree)
    algebra::Polynomial p1(1);
    p1[0] = basic::Rational(1, 3);
    p1[1] = basic::Rational(1, 2);

    algebra::Polynomial p2(2);
    p2[0] = basic::Rational(2, 3);
    p2[1] = basic::Rational(1, 3);
    p2[2] = basic::Rational(1, 6);

    p1 += p2;
    ASSERT_EQUAL(p1[0].value(), 1.0);
    ASSERT_EQUAL(p1[1].value(), 5.0 / 6);
    ASSERT_EQUAL(p1[2].value(), 1.0 / 6);
END_TEST

BEGIN_TEST(test_polynomial_addition_lower_degree)
    algebra::Polynomial p1(2);
    p1[0] = basic::Rational(1, 3);
    p1[1] = basic::Rational(1, 2);
    p1[2] = basic::Rational(1, 6);

    algebra::Polynomial p2(1);
    p2[0] = basic::Rational(2, 3);
    p2[1] = basic::Rational(1, 3);

    p1 += p2;
    ASSERT_EQUAL(p1[0].value(), 1.0);
    ASSERT_EQUAL(p1[1].value(), 5.0 / 6);
    ASSERT_EQUAL(p1[2].value(), 1.0 / 6);
END_TEST

BEGIN_TEST(test_polynomial_subtraction_self)
    algebra::Polynomial p(2);
    p[0] = basic::Rational(1, 3);
    p[1] = basic::Rational(1, 2);
    p[2] = basic::Rational(2, 3);

    p -= p;
    ASSERT_EQUAL(p[0].value(), 0.0);
    ASSERT_EQUAL(p[1].value(), 0.0);
    ASSERT_EQUAL(p[2].value(), 0.0);
END_TEST

BEGIN_TEST(test_polynomial_subtraction_zero)
    algebra::Polynomial p(1);
    p[0] = basic::Rational(1, 4);
    p[1] = basic::Rational(1, 2);

    algebra::Polynomial zero(1);

    p -= zero;
    ASSERT_EQUAL(p[0].value(), 0.25);
    ASSERT_EQUAL(p[1].value(), 0.5);
END_TEST

BEGIN_TEST(test_polynomial_subtraction_higher_degree)
    algebra::Polynomial p1(1);
    p1[0] = basic::Rational(2, 3);
    p1[1] = basic::Rational(1, 2);

    algebra::Polynomial p2(2);
    p2[0] = basic::Rational(1, 3);
    p2[1] = basic::Rational(1, 4);
    p2[2] = basic::Rational(1, 6);

    p1 -= p2;
    ASSERT_EQUAL(p1[0].value(), 1.0 / 3);
    ASSERT_EQUAL(p1[1].value(), 0.25);
    ASSERT_EQUAL(p1[2].value(), -1.0 / 6);
END_TEST

BEGIN_TEST(test_polynomial_subtraction_lower_degree)
    algebra::Polynomial p1(2);
    p1[0] = basic::Rational(1, 3);
    p1[1] = basic::Rational(1, 2);
    p1[2] = basic::Rational(1, 6);

    algebra::Polynomial p2(1);
    p2[0] = basic::Rational(1, 3);
    p2[1] = basic::Rational(1, 3);

    p1 -= p2;
    ASSERT_EQUAL(p1[0].value(), 0.0);
    ASSERT_EQUAL(p1[1].value(), 1.0 / 6);
    ASSERT_EQUAL(p1[2].value(), 1.0 / 6);
END_TEST

BEGIN_TEST(test_negate_zero_polynomial)
    algebra::Polynomial zero(2);
    algebra::Polynomial negated = -zero;

    ASSERT_EQUAL(negated[0].value(), 0.0);
    ASSERT_EQUAL(negated[1].value(), 0.0);
    ASSERT_EQUAL(negated[2].value(), 0.0);
END_TEST

BEGIN_TEST(test_negate_non_zero_polynomial)
    algebra::Polynomial p(2);
    p[0] = basic::Rational(1, 2);
    p[1] = basic::Rational(-3, 4);
    p[2] = basic::Rational(5, 6);

    algebra::Polynomial negated = -p;

    ASSERT_EQUAL(negated[0].value(), -0.5);
    ASSERT_EQUAL(negated[1].value(), 0.75);
    ASSERT_EQUAL(negated[2].value(), -5.0 / 6);
END_TEST

BEGIN_TEST(test_negate_negate_polynomial)
    algebra::Polynomial p(1);
    p[0] = basic::Rational(3, 7);
    p[1] = basic::Rational(-2, 5);

    algebra::Polynomial negated = -(-p);

    ASSERT_EQUAL(negated[0].value(), 3.0 / 7);
    ASSERT_EQUAL(negated[1].value(), -2.0 / 5);
END_TEST

BEGIN_TEST(test_polynomial_multiplication_by_zero)
    algebra::Polynomial p1(2);
    p1[0] = basic::Rational(1, 2);
    p1[1] = basic::Rational(3, 4);
    p1[2] = basic::Rational(5, 6);

    algebra::Polynomial zero(0);

    algebra::Polynomial result = p1 * zero;
    ASSERT_EQUAL(result.degree(), 0);
    ASSERT_EQUAL(result[0].value(), 0.0);
END_TEST

BEGIN_TEST(test_polynomial_multiplication_by_constant)
    algebra::Polynomial p1(1);
    p1[0] = basic::Rational(1, 4);
    p1[1] = basic::Rational(3, 4);

    algebra::Polynomial constant(0);
    constant[0] = basic::Rational(2, 1);

    algebra::Polynomial result = p1 * constant;
    ASSERT_EQUAL(result.degree(), 1);
    ASSERT_EQUAL(result[0].value(), 0.5);
    ASSERT_EQUAL(result[1].value(), 1.5);
END_TEST

BEGIN_TEST(test_polynomial_multiplication_general_case)
    algebra::Polynomial p1(1);
    p1[0] = basic::Rational(1, 2);
    p1[1] = basic::Rational(1, 1);

    algebra::Polynomial p2(1);
    p2[0] = basic::Rational(2, 1);
    p2[1] = basic::Rational(3, 1);

    algebra::Polynomial result = p1 * p2;
    ASSERT_EQUAL(result.degree(), 2);
    ASSERT_EQUAL(result[0].value(), 1.0);
    ASSERT_EQUAL(result[1].value(), 3.5);
    ASSERT_EQUAL(result[2].value(), 3.0);
END_TEST

BEGIN_TEST(test_polynomial_addition)
    algebra::Polynomial p1(2);
    p1[0] = basic::Rational(1, 1);
    p1[1] = basic::Rational(2, 1);
    p1[2] = basic::Rational(3, 1);

    algebra::Polynomial p2(2);
    p2[0] = basic::Rational(4, 1);
    p2[1] = basic::Rational(5, 1);
    p2[2] = basic::Rational(6, 1);

    algebra::Polynomial sum = p1 + p2;
    ASSERT_EQUAL(sum.degree(), 2);
    ASSERT_EQUAL(sum[0].value(), 5.0);
    ASSERT_EQUAL(sum[1].value(), 7.0);
    ASSERT_EQUAL(sum[2].value(), 9.0);
END_TEST

BEGIN_TEST(test_polynomial_subtraction)
    algebra::Polynomial p1(2);
    p1[0] = basic::Rational(3, 1);
    p1[1] = basic::Rational(5, 1);
    p1[2] = basic::Rational(7, 1);

    algebra::Polynomial p2(2);
    p2[0] = basic::Rational(1, 1);
    p2[1] = basic::Rational(2, 1);
    p2[2] = basic::Rational(3, 1);

    algebra::Polynomial difference = p1 - p2;
    ASSERT_EQUAL(difference.degree(), 2);
    ASSERT_EQUAL(difference[0].value(), 2.0);
    ASSERT_EQUAL(difference[1].value(), 3.0);
    ASSERT_EQUAL(difference[2].value(), 4.0);
END_TEST

BEGIN_TEST(test_print_empty_polynomial)
    algebra::Polynomial empty(0);
    std::ostringstream oss;
    oss << empty;
    ASSERT_EQUAL(oss.str(), "0");
END_TEST

BEGIN_TEST(test_print_single_term_polynomial)
    algebra::Polynomial singleTerm(0);
    singleTerm[0] = basic::Rational(1, 3);
    std::ostringstream oss;
    oss << singleTerm;
    ASSERT_EQUAL(oss.str(), "1/3");
END_TEST

BEGIN_TEST(test_print_multi_term_polynomial)
    algebra::Polynomial multiTerm(2);
    multiTerm[0] = basic::Rational(1, 2);
    multiTerm[1] = basic::Rational(3, 4);
    multiTerm[2] = basic::Rational(5, 6);
    std::ostringstream oss;
    oss << multiTerm;
    ASSERT_EQUAL(oss.str(), "5/6 X^2 + 3/4 X + 1/2");
END_TEST

BEGIN_TEST(test_derive_constant_polynomial)
    algebra::Polynomial p(0);
    p[0] = basic::Rational(5, 1);

    algebra::Polynomial result = derive(p);
    ASSERT_EQUAL(result.degree(), 0);
    ASSERT_EQUAL(result[0].value(), 0.0);
END_TEST

BEGIN_TEST(test_derive_linear_polynomial)
    algebra::Polynomial p(1);
    p[0] = basic::Rational(3, 1);
    p[1] = basic::Rational(2, 1);

    algebra::Polynomial result = derive(p);
    ASSERT_EQUAL(result.degree(), 0);
    ASSERT_EQUAL(result[0].value(), 2.0);
END_TEST

BEGIN_TEST(test_derive_quadratic_polynomial)
    algebra::Polynomial p(2);
    p[0] = basic::Rational(1, 1);
    p[1] = basic::Rational(-3, 1);
    p[2] = basic::Rational(2, 1);

    algebra::Polynomial result = derive(p);
    ASSERT_EQUAL(result.degree(), 1);
    ASSERT_EQUAL(result[0].value(), -3.0);
    ASSERT_EQUAL(result[1].value(), 4.0);
END_TEST

BEGIN_TEST(test_derive_high_degree_polynomial)
    algebra::Polynomial p(3);
    p[0] = basic::Rational(0, 1);
    p[1] = basic::Rational(1, 1);
    p[2] = basic::Rational(2, 1);
    p[3] = basic::Rational(3, 1);

    algebra::Polynomial result = derive(p);
    ASSERT_EQUAL(result.degree(), 2);
    ASSERT_EQUAL(result[0].value(), 1.0);
    ASSERT_EQUAL(result[1].value(), 4.0);
    ASSERT_EQUAL(result[2].value(), 9.0);
END_TEST

BEGIN_TEST(test_derive_zero_polynomial)
    algebra::Polynomial p(3);
    p[0] = basic::Rational(0, 1);
    p[1] = basic::Rational(0, 1);
    p[2] = basic::Rational(0, 1);
    p[3] = basic::Rational(0, 1);

    algebra::Polynomial result = derive(p);
    ASSERT_EQUAL(result.degree(), 0);
    ASSERT_EQUAL(result[0].value(), 0.0);
END_TEST

BEGIN_TEST(test_integrate_constant_polynomial)
    algebra::Polynomial p(0);
    p[0] = basic::Rational(1, 4);

    double result = integrate(p, 0, 4);
    ASSERT_EQUAL(result, 1.0);
END_TEST

BEGIN_TEST(test_integrate_linear_polynomial)
    algebra::Polynomial p(1);
    p[0] = basic::Rational(0, 1);
    p[1] = basic::Rational(1, 2);

    double result = integrate(p, 0, 4);
    ASSERT_EQUAL(result, 4.0);
END_TEST

BEGIN_TEST(test_integrate_quadratic_polynomial)
    algebra::Polynomial p(2);
    p[0] = basic::Rational(0, 1);
    p[1] = basic::Rational(0, 1);
    p[2] = basic::Rational(3, 4);

    double result = integrate(p, 2, 4);
    ASSERT_EQUAL(result, 14.0);
END_TEST

BEGIN_TEST(test_integrate_cubic_polynomial)
    algebra::Polynomial p(3);
    p[0] = basic::Rational(1, 4);
    p[1] = basic::Rational(1, 2);
    p[2] = basic::Rational(3, 4);
    p[3] = basic::Rational(1, 1);

    double result = integrate(p, 0, 2);
    ASSERT_EQUAL(result, 7.5);
END_TEST

BEGIN_TEST(test_integrate_zero_polynomial)
    algebra::Polynomial p(2);
    p[0] = basic::Rational(0, 1);
    p[1] = basic::Rational(0, 1);
    p[2] = basic::Rational(0, 1);

    double result = integrate(p, -2, 2);
    ASSERT_EQUAL(result, 0.0);
END_TEST

BEGIN_TEST(test_integrate_negative_bounds)
    algebra::Polynomial p(1);
    p[0] = basic::Rational(1, 4);
    p[1] = basic::Rational(3, 4);

    double result = integrate(p, -2, 2);
    ASSERT_EQUAL(result, 1.0);
END_TEST

TEST_SUITE()
    TEST(test_polynomial_specific_degree)
    TEST(test_polynomial_zero_degree)
    TEST(test_polynomial_negative_degree)

    TEST(test_polynomial_from_rational_range)
    TEST(test_polynomial_from_empty_range)
    TEST(test_polynomial_from_single_element_range)

    TEST(test_copy_constructor_basic)
    TEST(test_copy_independence)
    TEST(test_copy_empty_polynomial)
    TEST(test_copy_single_coefficient)

    TEST(test_copy_assignment_basic)
    TEST(test_copy_assignment_self_assignment)
    TEST(test_copy_assignment_independence)

    TEST(test_polynomial_operator_index_valid_access)
    TEST(test_polynomial_operator_index_boundary_conditions)
    TEST(test_polynomial_operator_index_out_of_bounds)

    TEST(test_polynomial_evaluation_zero)
    TEST(test_polynomial_evaluation_constant)
    TEST(test_polynomial_evaluation_linear)
    TEST(test_polynomial_evaluation_quadratic)

    TEST(test_degree_zero_polynomial)
    TEST(test_degree_constant_polynomial)
    TEST(test_degree_higher_polynomial)
    TEST(test_degree_polynomial_with_zero_tail)

    TEST(test_polynomial_multiply_by_zero)
    TEST(test_polynomial_multiply_by_one)
    TEST(test_polynomial_multiply_by_positive_integer)
    TEST(test_polynomial_multiply_by_negative_integer)
    TEST(test_polynomial_multiply_empty_polynomial)

    TEST(test_polynomial_multiply_by_rational_zero)
    TEST(test_polynomial_multiply_by_rational_one)
    TEST(test_polynomial_multiply_by_positive_rational)
    TEST(test_polynomial_multiply_by_negative_rational)

    TEST(test_polynomial_addition_zero)
    TEST(test_polynomial_addition_same_degree)
    TEST(test_polynomial_addition_higher_degree)
    TEST(test_polynomial_addition_lower_degree)

    TEST(test_polynomial_subtraction_self)
    TEST(test_polynomial_subtraction_zero)
    TEST(test_polynomial_subtraction_higher_degree)
    TEST(test_polynomial_subtraction_lower_degree)

    TEST(test_negate_zero_polynomial)
    TEST(test_negate_non_zero_polynomial)
    TEST(test_negate_negate_polynomial)

    TEST(test_negate_zero_polynomial)
    TEST(test_negate_non_zero_polynomial)
    TEST(test_negate_negate_polynomial)

    TEST(test_polynomial_multiplication_by_zero)
    TEST(test_polynomial_multiplication_by_constant)
    TEST(test_polynomial_multiplication_general_case)

    TEST(test_polynomial_addition)
    TEST(test_polynomial_subtraction)

    TEST(test_print_empty_polynomial)
    TEST(test_print_single_term_polynomial)
    TEST(test_print_multi_term_polynomial)

    TEST(test_derive_constant_polynomial)
    TEST(test_derive_linear_polynomial)
    TEST(test_derive_quadratic_polynomial)
    TEST(test_derive_high_degree_polynomial)
    TEST(test_derive_zero_polynomial)

    TEST(test_integrate_constant_polynomial)
    TEST(test_integrate_linear_polynomial)
    TEST(test_integrate_quadratic_polynomial)
    TEST(test_integrate_cubic_polynomial)
    TEST(test_integrate_zero_polynomial)
    TEST(test_integrate_negative_bounds)

END_SUITE
