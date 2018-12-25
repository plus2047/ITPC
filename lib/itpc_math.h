#ifndef __ITPC_MATH_H__
#define __ITPC_MATH_H__

// for get define of size_t
#include <cstdio>

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
inline num_t fast_power(num_t base, int n) {
    num_t res = 1;
    while (n) {
        if (n % 2 == 1) res *= base;
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
}  // namespace contest
#endif  // define __ITPC_MATH_H__