#ifndef BASIC_MATH_H
#define BASIC_MATH_H
#include <climits>  // For LLONG_MAX
int const overflow_error = -1;
int const negative_number_error = -2;

enum Color { Red, Black, White };
struct Ball {
      Color color;
      int radius;
      bool is_solid;
};
typedef enum sort_result {
    SORT_SUCCESS = 0,
    SORT_NULL_ARRAY,
    SORT_INVALID_SIZE
}sort_result;

/**
 * Finds three prime numbers that sum up to a given odd number greater than 5.
 * This function implements Goldbach's weak conjecture.
 * 
 * @param n The odd integer greater than 5 to be expressed as a sum of three primes.
 * @param p1 Reference to store the first prime number.
 * @param p2 Reference to store the second prime number.
 * @param p3 Reference to store the third prime number.
 * @return True if three primes are found, false otherwise (should not happen if the conjecture holds).
 */
bool goldbach(int n, int& p1, int& p2, int& p3);

/**
 * Computes the Fibonacci number for a given integer using memoization.
 * 
 * This function calculates the Fibonacci sequence using a lookup table to store 
 * previously computed values, improving performance. It supports both positive 
 * and negative indices, following the Fibonacci identity:  
 *     F(-n) = (-1)^(n+1) * F(n).
 * 
 * @param n The index of the Fibonacci sequence to compute.
 * @return The Fibonacci number corresponding to index `n`.
 */
long long fib(int n);

/**
 * Computes the factorial of a given non-negative integer.
 * 
 * This function calculates the factorial using a recursive helper function.
 * If a negative number is provided, it returns an error value.
 * 
 * @param n The non-negative integer whose factorial is to be computed.
 * @return The factorial of `n`, or an error code if `n` is negative.
 */
long long factorial(int n);


sort_result sort_balls_by_color(Ball balls_arr[], int size);

#endif // BASIC_MATH_H