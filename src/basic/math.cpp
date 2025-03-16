#include "basic/math.hpp" //../inc/
#include <cstdlib>
#include <climits>  // For LLONG_MAX


static void check_is_prime(int n, bool* is_prime_arr);
static int get_primes(int n, bool* is_prime_arr, int* primes);
static bool find_three_primes_sums_to_n(int n, bool* is_prime_arr, int* primes, int prime_count, basic::Goldbach& g);

static unsigned long long wrapper_fib_rec(unsigned int n, long long lookup_table[]);

static long long wrapper_factorial_rec(unsigned int n, long long result); //result = 1

static void swap_balls(basic::Ball& a, basic::Ball& b);
static bool balls_sort(basic::Ball arr[], unsigned int size);

bool basic::goldbach(unsigned int n, basic::Goldbach& g)//int& p1, int& p2, int& p3)
{
    if(n <= 5 || n % 2 == 0) {
        return false;
    }
    bool* is_prime_arr = (bool*)malloc((n + 1) * sizeof(bool));
    int* primes = (int*)malloc((n + 1) * sizeof(int));
    if(is_prime_arr == NULL)
    {
        return false;
    }
    if(primes == NULL)
    {
        free(is_prime_arr);
        return false;
    }
    check_is_prime(n, is_prime_arr);
    int num_primes = get_primes(n, is_prime_arr, primes);

    return find_three_primes_sums_to_n(n, is_prime_arr, primes, num_primes, g);
}

unsigned long long basic::fib(unsigned int n) {
    if(n == 0) {
        return 0;
    }
    if(n == 1 || n == 2) {
        return 1;
    }
    unsigned int const lookup_table_size = 1024;
    if(n >= lookup_table_size) {
        return -1;
    }
    static long long lookup_table[lookup_table_size] = {0, 1, 1};
    if(n < lookup_table_size && lookup_table[n]) {
        return lookup_table[n];
    }
    return wrapper_fib_rec(n, lookup_table);
}


long long basic::factorial(unsigned int n) {
    if(n == 0)
    {
        return 1;
    }
    return wrapper_factorial_rec(n, 1);
}

bool basic::sort_balls_by_color(basic::Ball balls_arr[], unsigned int size)
{
    return balls_sort(balls_arr, size);
}

/*-------------------------------HELPER FUNCTIONS-------------------------------*/

static void check_is_prime(int n, bool* is_prime_arr) 
{
    for (int i = 0; i <= n; ++i) {
        is_prime_arr[i] = true;
    }
    // 0 and 1 are not primes
    is_prime_arr[0] = false; 
    is_prime_arr[1] = false;
    for (int p = 2; p * p <= n; ++p) {
        if (is_prime_arr[p]) {
            for (int i = p * p; i <= n; i += p) {
                is_prime_arr[i] = false;
            }
        }
    }
}

static int get_primes(int n, bool* is_prime_arr, int* primes) 
{
    int count = 0;
    for (int i = 2; i <= n; ++i) {
        if (is_prime_arr[i]) {
            primes[count++] = i;
        }
    }
    return count;
}

static bool find_three_primes_sums_to_n(int n, bool* is_prime_arr, int* primes, int prime_count, basic::Goldbach& g) 
{
    for (int i = 0; i < prime_count; ++i) {
        for (int j = i; j < prime_count; ++j) {
            int p1_candidate = primes[i];
            int p2_candidate = primes[j];
            int p3_candidate = n - p1_candidate - p2_candidate;
            if (p3_candidate >= p2_candidate && p3_candidate <= n && is_prime_arr[p3_candidate]) {
                g.first = p1_candidate;
                g.second = p2_candidate;
                g.third = p3_candidate;
                free(is_prime_arr);
                free(primes);
                return true;
            }
        }
    }
    g.first = -1;
    g.second = -1;
    g.third = -1;
    free(is_prime_arr);
    free(primes);
    return false; // No solution found
}

static unsigned long long wrapper_fib_rec(unsigned int n, long long lookup_table[]) {
    if(n <= 1) {
        return n;
    }
    if(lookup_table[n]) {
        return lookup_table[n];
    }
    long long prev = (lookup_table[n - 1]) ? lookup_table[n - 1] : wrapper_fib_rec(n - 1, lookup_table);
    long long prev2 = (lookup_table[n - 2]) ? lookup_table[n - 2] : wrapper_fib_rec(n - 2, lookup_table);
    if (prev == basic::overflow_error || prev2 == basic::overflow_error) {
        return basic::overflow_error;
    }
    if (LLONG_MAX - prev2 < prev) {
        return basic::overflow_error;
    }
    long long fib_result = prev + prev2;
    lookup_table[n] = prev + prev2;

    return fib_result;
}

// tail recursion optimization
static long long wrapper_factorial_rec(unsigned int n, long long result) { //__attribute__((optimize("O3")))
    if(n <= 1)
    {
        return result;
    }
    if (LLONG_MAX / n < result) {
        return basic::overflow_error;
    }
    return wrapper_factorial_rec(n - 1, n * result);
}

static void swap_balls(basic::Ball& a, basic::Ball& b) 
{
    basic::Ball temp = a;
    a = b;
    b = temp;
}

static bool balls_sort(basic::Ball arr[], unsigned int size)
{
    if (arr == nullptr) {
        return false;
    }
    int low = 0, mid = 0, high = size - 1;

    while (mid <= high) {
        switch (arr[mid].color) {
            case basic::Color::White:
                swap_balls(arr[low], arr[mid]);
                ++low;
                ++mid;
                break;
            case basic::Color::Red:
                ++mid;
                break;
            case basic::Color::Black:
                swap_balls(arr[mid], arr[high]);
                --high;
                break;
        }
    }
    return true;
}