#pragma once

namespace basic {

int const overflow_error = -1;

struct Goldbach{
    int first;
    int second;
    int third;
};

enum Color { Red, Black, White };
struct Ball {
    Color color;
    int radius;
    bool is_solid;
};

/**
 * Applies Goldbach's weak conjecture to find three prime numbers that sum up to an odd number greater than 5.
 *
 * @param n The odd integer greater than 5 to be expressed as the sum of three primes.
 * @param g A Goldbach struct instance to store the three prime numbers if found.
 * @return True if three prime numbers are found that sum to 'n', otherwise false.
 */
bool goldbach(unsigned int n, Goldbach& g);//int& p1, int& p2, int& p3);

/**
 * Computes the Fibonacci number at a given index using memoization to improve performance.
 *
 * @param n The index in the Fibonacci sequence.
 * @return The Fibonacci number at index 'n'. overflow_error(-1) in case of overflow.
 */
long long fib(unsigned int n);

/**
 * Calculates the factorial of a non-negative integer using tail recursion.
 *
 * @param n The integer whose factorial is to be computed.
 * @return The factorial of 'n'.
 */
long long factorial(unsigned int n);

/**
 * Sorts an array of Balls by their color in the order of White, Red, and Black.
 *
 * @param balls_arr Pointer to the array of Ball objects.
 * @param size Number of elements in the balls_arr.
 * @return True if the array was successfully sorted, otherwise false.
 */
bool sort_balls_by_color(Ball balls_arr[], unsigned int size);

/**
* Helper function to calculate the greatest common divisor of two integers.
* @param a The first integer.
* @param b The second integer.
* @return The greatest common divisor of a and b.
*/
int gcd(int a, int b);

} // namespace basic