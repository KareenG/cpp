#include <vector>
#include <unordered_set>
#include "../inc/basic_math.hpp"
#include <climits>
#include <algorithm>
#include <stdexcept>

int const min_prime = 2;
int const lookup_table_size = 1024;

static bool is_prime(int n);
static long long wrapper_fib_rec(int n, long long lookup_table[], int lookup_table_size);
static long long wrapper_factorial_rec(int n, long long result = 1);

typedef int (*sort_counting_action)(Ball ball);
static int priority_of_color(Ball ball);
static sort_result balls_sort(Ball arr[], int size, int min, int max, sort_counting_action action_count);

bool goldbach(int n, int& p1, int& p2, int& p3)
{
    if(n <= 5 || n % 2 == 0) {
        return false;
    }
    std::unordered_set<int> primes;
    std::vector<int> primes_arr;
    for (int i = 2; i <= n; ++i) {
        if(is_prime(i))
        {
            primes.insert(i);
            primes_arr.push_back(i);
        }
    }
    int p1_candidate, p2_candidate, p3_candidate;
    int size = primes_arr.size();
    for (int i = 0; i < size; ++i) {
        p1_candidate = primes_arr[i];
        for (int j = i; j < size; ++j) {
            p2_candidate = primes_arr[j];
            p3_candidate = n - p1_candidate - p2_candidate;
            if(p3_candidate >= min_prime && primes.count(p3_candidate))
            {
                p1 = p1_candidate;
                p2 = p2_candidate;
                p3 = p3_candidate;
                return true;
            }
        }
    }
    return false;
}

long long fib(int n) {
    static long long lookup_table[lookup_table_size] = {0};
    if(n < 0) {
        return negative_number_error;
    }
    if(n <= 1) {
        return n;
    }
    if(n < lookup_table_size && lookup_table[n]) {
        return lookup_table[n];
    }
    return wrapper_fib_rec(n, lookup_table, lookup_table_size);
}


long long factorial(int n) {
    if(n < 0)
    {
        return negative_number_error;
    }
    if(n == 0)
    {
        return 1;
    }
    return wrapper_factorial_rec(n);
}

sort_result sort_balls_by_color(Ball balls_arr[], int size)
{
    return balls_sort(balls_arr, size, 0, 2, priority_of_color);
}


/*-------------------------------HELPER FUNCTIONS-------------------------------*/
static bool is_prime(int n)
{
    if(n <= 1) {
        return false;
    }
    if(n <= 3) { // 2 or 3
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

static long long wrapper_fib_rec(int n, long long lookup_table[], int lookup_table_size) {
    if(n <= 1) {
        return n;
    }
    if(n < lookup_table_size && lookup_table[n]) {
        return lookup_table[n];
    }
    long long prev = (n - 1 < lookup_table_size && lookup_table[n - 1]) ? lookup_table[n - 1] : wrapper_fib_rec(n - 1, lookup_table, lookup_table_size);
    long long prev2 = (n - 2 < lookup_table_size && lookup_table[n - 2]) ? lookup_table[n - 2] : wrapper_fib_rec(n - 2, lookup_table, lookup_table_size);
    if (prev == overflow_error || prev2 == overflow_error) {
        return overflow_error;
    }
    if (LLONG_MAX - prev2 < prev) {
        return overflow_error;
    }
    long long fib_result = prev + prev2;
    if(n < lookup_table_size) {
        lookup_table[n] = fib_result;
    }
    return fib_result;
}

// tail recursion optimization
static long long __attribute__((optimize("O3"))) wrapper_factorial_rec(int n, long long result) {
    if(n <= 1)
    {
        return result;
    }
    if (LLONG_MAX / n < result) {
        return overflow_error;
    }
    return wrapper_factorial_rec(n - 1, n * result);
}


static sort_result balls_sort(Ball arr[], int size, int min, int max, sort_counting_action action_count) {
    if (!arr) {
        return SORT_NULL_ARRAY;
    }
    if (size <= 0) {
        return SORT_INVALID_SIZE;
    }
    if (size == 1) {
        return SORT_SUCCESS;
    }

    int range = max - min + 1;
    std::vector<int> arrC(range, 0);
    std::vector<Ball> arrB(size);

    for (int j = 0; j < size; ++j) {
        int index = action_count(arr[j]) - min;
        arrC[index]++;
    }

    for (int i = 1; i < range; ++i) {
        arrC[i] += arrC[i - 1];
    }

    for (int j = size - 1; j >= 0; --j) {
        int index = action_count(arr[j]) - min;
        arrB[arrC[index] - 1] = arr[j];
        arrC[index]--;
    }

    std::copy(arrB.begin(), arrB.end(), arr);
    return SORT_SUCCESS;
}

static int priority_of_color(Ball ball)
{
    switch (ball.color) {
        case White:   
            return 0;
        case Red: 
            return 1;
        case Black: 
            return 2;
        default:    
            return -1;
    }
}