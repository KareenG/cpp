#include "basic/math.hpp"
#include "mu_test.h"
#include <vector>

static bool is_prime(int n)
{
    if(n <= 1) {
        return false;
    }
    if(n <= 3) {
        return true;
    }
    if(n % 2 == 0 || n % 3 == 0) {
        return false;
    }
    // All prime numbers greater than 3 are of the form 6k ± 1.
    for(int i = 5; i * i <= n; i += 6) {
        if(n % i == 0) {
            return false;
        }
    }
    return true;
}

// Helper function to check order
bool is_sorted_correctly(const basic::Ball* balls, int size) {
    int white_count = 0, red_count = 0, black_count = 0;
    for (int i = 0; i < size; ++i) {
        switch (balls[i].color) {
            case basic::Color::White: 
                if (red_count > 0 || black_count > 0) {
                    return false;
                } 
                white_count++; 
                break;
            case basic::Color::Red:   
                if (black_count > 0) {
                    return false; 
                }
                red_count++; 
                break;
            case basic::Color::Black: 
                black_count++; 
                break;
        }
    }
    return true;
}

/************* goldbach tests *************/
BEGIN_TEST(goldbach_less_than_or_equal5)
    basic::Goldbach g = {-1, -1, -1};
    ASSERT_THAT(basic::goldbach(5, g) == false);
END_TEST

BEGIN_TEST(goldbach_even_number)
    basic::Goldbach g = {-1, -1, -1};
    ASSERT_THAT(basic::goldbach(10, g) == false);
END_TEST

BEGIN_TEST(goldbach_invalid_input_negative)
    basic::Goldbach g = {-1, -1, -1};
    ASSERT_THAT(basic::goldbach(-7, g) == false);
END_TEST

BEGIN_TEST(goldbach_valid_input_27)
    basic::Goldbach g = {-1, -1, -1};
    ASSERT_THAT(basic::goldbach(27, g) == true);
    ASSERT_THAT(g.first + g.second + g.third == 27);
    ASSERT_THAT(is_prime(g.first) && is_prime(g.second) && is_prime(g.third));
END_TEST

BEGIN_TEST(goldbach_valid_input_999)
    basic::Goldbach g = {-1, -1, -1};
    ASSERT_THAT(basic::goldbach(999, g) == true);
    ASSERT_THAT(g.first + g.second + g.third == 999);
    ASSERT_THAT(is_prime(g.first) && is_prime(g.second) && is_prime(g.third));
END_TEST

/************* fibonacci tests *************/
BEGIN_TEST(fib_negative_number)
    ASSERT_EQUAL(basic::fib(-10), -1);
END_TEST

BEGIN_TEST(fib_zero)
    ASSERT_EQUAL(basic::fib(0), 0);
END_TEST

BEGIN_TEST(fib_one)
    ASSERT_EQUAL(basic::fib(1), 1);
END_TEST

BEGIN_TEST(fib_valid_input)
    ASSERT_EQUAL(basic::fib(10), 55);
END_TEST

// Testing the maximum known valid Fibonacci number under long long
BEGIN_TEST(fib_max_possible_number)
    ASSERT_EQUAL(basic::fib(92), 7540113804746346429);
END_TEST

// Testing beyond the safe limit to check overflow handling
BEGIN_TEST(fib_overflow)
    ASSERT_EQUAL(basic::fib(93), -1);  // Assuming 93 is beyond the calculated safe limit for fib in long long
END_TEST

/************* factorial tests *************/
BEGIN_TEST(factorial_negative_number)
    ASSERT_EQUAL(basic::factorial(-1), -1);
END_TEST

BEGIN_TEST(factorial_zero)
    ASSERT_EQUAL(basic::factorial(0), 1);
END_TEST

BEGIN_TEST(factorial_small_number)
    ASSERT_EQUAL(basic::factorial(5), 120);
END_TEST

BEGIN_TEST(factorial_larger_number)
    ASSERT_EQUAL(basic::factorial(10), 3628800);
END_TEST

// Testing the largest factorial number possible without overflow in long long
BEGIN_TEST(factorial_largest_possible_number)
    ASSERT_EQUAL(basic::factorial(20), 2432902008176640000);  // Factorial of 20
END_TEST

// Testing for overflow detection
BEGIN_TEST(factorial_overflow_number)
    ASSERT_EQUAL(basic::factorial(21), -1);  // Assuming 21! exceeds the range of long long
END_TEST

/************* sort_balls_by_color tests *************/
BEGIN_TEST(sort_balls_empty_array)
    std::vector<basic::Ball> balls;  // Creates an empty vector of Ball
    ASSERT_THAT(sort_balls_by_color(balls.data(), balls.size()) == false);
END_TEST

BEGIN_TEST(sort_balls_single_ball)
    basic::Ball balls[1] = {{basic::Color::White, 4, true}};
    ASSERT_THAT(basic::sort_balls_by_color(balls, 1) == true);
    ASSERT_THAT(balls[0].color == basic::Color::White);
END_TEST

BEGIN_TEST(sort_balls_unsorted)
    basic::Ball balls[5] = {{basic::Color::Black, 5, true}, {basic::Color::White, 4, true}, {basic::Color::Red, 3, true}, {basic::Color::White, 2, true}, {basic::Color::Red, 1, true}};
    ASSERT_THAT(basic::sort_balls_by_color(balls, 5) == true);
    ASSERT_THAT(is_sorted_correctly(balls, 5));
END_TEST

BEGIN_TEST(sort_balls_already_sorted)
    basic::Ball balls[4] = {{basic::Color::White, 4, true}, {basic::Color::Red, 3, true}, {basic::Color::Red, 2, true}, {basic::Color::Black, 1, true}};
    ASSERT_THAT(basic::sort_balls_by_color(balls, 4) == true);
    ASSERT_THAT(is_sorted_correctly(balls, 4));
END_TEST

BEGIN_TEST(sort_balls_mixed_order_like_example)
    basic::Ball balls[10] = {
        {basic::Color::White, 5, true}, {basic::Color::Red, 5, true}, {basic::Color::White, 5, true},
        {basic::Color::Black, 5, true}, {basic::Color::Red, 5, true}, {basic::Color::Black, 5, true},
        {basic::Color::White, 5, true}, {basic::Color::Black, 5, true}, {basic::Color::Red, 5, true}, {basic::Color::Red, 5, true}
    };
    ASSERT_THAT(basic::sort_balls_by_color(balls, 10) == true);
    ASSERT_THAT(is_sorted_correctly(balls, 10));
END_TEST


TEST_SUITE()
    /* goldbach tests */
    TEST(goldbach_less_than_or_equal5)
    TEST(goldbach_even_number)
    TEST(goldbach_invalid_input_negative)
    TEST(goldbach_valid_input_27)
    TEST(goldbach_valid_input_999)

    /* fib tests */
    TEST(fib_negative_number)
    TEST(fib_zero)
    TEST(fib_one)
    TEST(fib_valid_input)
    TEST(fib_max_possible_number)
    TEST(fib_overflow)

    /* factorial tests */
    TEST(factorial_negative_number)
    TEST(factorial_zero)
    TEST(factorial_small_number)
    TEST(factorial_larger_number)
    TEST(factorial_largest_possible_number)
    TEST(factorial_overflow_number)

    /* sort_balls_by_color tests */
    TEST(sort_balls_empty_array)
    TEST(sort_balls_single_ball)
    TEST(sort_balls_unsorted)
    TEST(sort_balls_already_sorted)
    TEST(sort_balls_mixed_order_like_example)

END_SUITE