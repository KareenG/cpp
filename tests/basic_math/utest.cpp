#include "basic_math.hpp"
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
bool is_sorted_correctly(const Ball* balls, int size) {
    int white_count = 0, red_count = 0, black_count = 0;
    for (int i = 0; i < size; ++i) {
        switch (balls[i].color) {
            case White: 
                if (red_count > 0 || black_count > 0) {
                    return false;
                } 
                white_count++; 
                break;
            case Red:   
                if (black_count > 0) {
                    return false; 
                }
                red_count++; 
                break;
            case Black: 
                black_count++; 
                break;
        }
    }
    return true;
}

/************* goldbach tests *************/
BEGIN_TEST(goldbach_less_than_or_equal5)
    int p1, p2, p3;
    ASSERT_THAT(goldbach(5, p1, p2, p3) == false);
END_TEST

BEGIN_TEST(goldbach_even_number)
    int p1, p2, p3;
    ASSERT_THAT(goldbach(10, p1, p2, p3) == false);
END_TEST

BEGIN_TEST(goldbach_invalid_input_negative)
    int p1, p2, p3;
    ASSERT_THAT(goldbach(-7, p1, p2, p3) == false);
END_TEST

BEGIN_TEST(goldbach_valid_input_27)
    int p1, p2, p3;
    ASSERT_THAT(goldbach(27, p1, p2, p3) == true);
    ASSERT_THAT(p1 + p2 + p3 == 27);
    ASSERT_THAT(is_prime(p1) && is_prime(p2) && is_prime(p3));
END_TEST

BEGIN_TEST(goldbach_valid_input_999)
    int p1, p2, p3;
    ASSERT_THAT(goldbach(999, p1, p2, p3) == true);
    ASSERT_THAT(p1 + p2 + p3 == 999);
    ASSERT_THAT(is_prime(p1) && is_prime(p2) && is_prime(p3));
END_TEST

/************* fibonacci tests *************/
BEGIN_TEST(fib_negative_number)
    ASSERT_EQUAL(fib(-10), negative_number_error);
END_TEST

BEGIN_TEST(fib_zero)
    ASSERT_EQUAL(fib(0), 0);
END_TEST

BEGIN_TEST(fib_one)
    ASSERT_EQUAL(fib(1), 1);
END_TEST

BEGIN_TEST(fib_valid_input)
    ASSERT_EQUAL(fib(10), 55);
END_TEST

// Testing the maximum known valid Fibonacci number under long long
BEGIN_TEST(fib_max_possible_number)
    ASSERT_EQUAL(fib(92), 7540113804746346429);
END_TEST

// Testing beyond the safe limit to check overflow handling
BEGIN_TEST(fib_overflow)
    ASSERT_EQUAL(fib(93), overflow_error);  // Assuming 93 is beyond the calculated safe limit for fib in long long
END_TEST

/************* factorial tests *************/
BEGIN_TEST(factorial_negative_number)
    ASSERT_EQUAL(factorial(-1), negative_number_error);
END_TEST

BEGIN_TEST(factorial_zero)
    ASSERT_EQUAL(factorial(0), 1);
END_TEST

BEGIN_TEST(factorial_small_number)
    ASSERT_EQUAL(factorial(5), 120);
END_TEST

BEGIN_TEST(factorial_larger_number)
    ASSERT_EQUAL(factorial(10), 3628800);
END_TEST

// Testing the largest factorial number possible without overflow in long long
BEGIN_TEST(factorial_largest_possible_number)
    ASSERT_EQUAL(factorial(20), 2432902008176640000);  // Factorial of 20
END_TEST

// Testing for overflow detection
BEGIN_TEST(factorial_overflow_number)
    ASSERT_EQUAL(factorial(21), overflow_error);  // Assuming 21! exceeds the range of long long
END_TEST

/************* sort_balls_by_color tests *************/
BEGIN_TEST(sort_balls_empty_array)
    std::vector<Ball> balls;  // Creates an empty vector of Ball
    ASSERT_THAT(sort_balls_by_color(balls.data(), balls.size()) == SORT_NULL_ARRAY);
END_TEST

BEGIN_TEST(sort_balls_array_negative_size)
    Ball balls[5] = {{Black, 5, true}, {White, 4, true}, {Red, 3, true}, {White, 2, true}, {Red, 1, true}};
    ASSERT_THAT(sort_balls_by_color(balls, - 10) == SORT_INVALID_SIZE);
END_TEST

BEGIN_TEST(sort_balls_single_ball)
    Ball balls[1] = {{White, 4, true}};
    ASSERT_THAT(sort_balls_by_color(balls, 1) == SORT_SUCCESS);
    ASSERT_THAT(balls[0].color == White);
END_TEST

BEGIN_TEST(sort_balls_unsorted)
    Ball balls[5] = {{Black, 5, true}, {White, 4, true}, {Red, 3, true}, {White, 2, true}, {Red, 1, true}};
    ASSERT_THAT(sort_balls_by_color(balls, 5) == SORT_SUCCESS);
    ASSERT_THAT(is_sorted_correctly(balls, 5));
END_TEST

BEGIN_TEST(sort_balls_already_sorted)
    Ball balls[4] = {{White, 4, true}, {Red, 3, true}, {Red, 2, true}, {Black, 1, true}};
    ASSERT_THAT(sort_balls_by_color(balls, 4) == SORT_SUCCESS);
    ASSERT_THAT(is_sorted_correctly(balls, 4));
END_TEST

BEGIN_TEST(sort_balls_mixed_order_like_example)
    Ball balls[10] = {
        {White, 5, true}, {Red, 5, true}, {White, 5, true},
        {Black, 5, true}, {Red, 5, true}, {Black, 5, true},
        {White, 5, true}, {Black, 5, true}, {Red, 5, true}, {Red, 5, true}
    };
    ASSERT_THAT(sort_balls_by_color(balls, 10) == SORT_SUCCESS);
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
    TEST(sort_balls_array_negative_size)
    TEST(sort_balls_single_ball)
    TEST(sort_balls_unsorted)
    TEST(sort_balls_already_sorted)
    TEST(sort_balls_mixed_order_like_example)

END_SUITE