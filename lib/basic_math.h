#pragma once

namespace contest {

// Greatest Common Divisor. For this implement,
// gcd(0, n) == gcd(n, 0) == n
// gcd(1, n) == gcd(n, 1) == 1
// gcd(0, 0) == 0
template <typename num_t>
num_t greatest_common_divisor(num_t a, num_t b) {
    while (b) {
        tie(a, b) = make_pair(b, a % b);
    }
    return a;
}

// \sum_{k = 1}^{n} n^1
template <typename num_t>
inline num_t sum_range_power1(num_t n) {
    return n * (n + 1) / 2;
}

// \sum_{k = 1}^{n} n^2
template <typename num_t>
inline num_t sum_range_power2(num_t n) {
    return n * (n + 1) * (2 * n + 1) / 6;
}

// \sum_{k = 1}^{n} n^3
template <typename num_t>
inline num_t sum_range_power3(num_t n) {
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

}  // namespace contest
