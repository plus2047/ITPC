#pragma once
#include <limits>
#include <random>

namespace contest {

template <typename num_t>
inline num_t sum_range_power1(num_t n) {
    // \sum_{k = 1}^{n} n^1
    return n * (n + 1) / 2;
}

template <typename num_t>
inline num_t sum_range_power2(num_t n) {
    // \sum_{k = 1}^{n} n^2
    return n * (n + 1) * (2 * n + 1) / 6;
}

template <typename num_t>
inline num_t sum_range_power3(num_t n) {
    // \sum_{k = 1}^{n} n^3
    num_t s2 = n * (n + 1) / 2;
    return s2 * s2;
}

template <typename num_t>
num_t quick_pow(num_t base, int n) {
    num_t res = 1;
    while (n) {
        if (n & 1) res *= base;
        base *= base;
        n /= 2;
    }
    return res;
}

template <typename num_t>
num_t gcd(num_t a, num_t b) {
    // Greatest Common Divisor
    // gcd(0, n) == gcd(n, 0) == n
    // gcd(1, n) == gcd(n, 1) == 1
    // (for this implement) gcd(0, 0) == 0
    while (b) {
        num_t r = a % b;
        a = b;
        b = r;
    }
    return a;
}

template <typename num>
struct RandNum {
    std::mt19937 gen;
    std::uniform_int_distribution<num> dist;

    RandNum(num left, num right, unsigned seed = 0)
        : gen(seed), dist(left, right) {}

    num operator()() { return dist(gen); }
};

RandNum<int> randInt = RandNum<int>(0, std::numeric_limits<int>::max());

// float calculate.
// always using double. if necessary, using long double.

const double DELTA = 1E-9;

inline int sign(double x) { return (x > DELTA) - (x < -DELTA); }

// return 1 if x > y; 0 if abs(x - y) < DELTA; -1 if x < y
inline int compare(double x1, double x2) { return sign(x1 - x2); }

}  // namespace contest