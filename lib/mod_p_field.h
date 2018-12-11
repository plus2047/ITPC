#ifndef __FINITE_FIELD_H__
#define __FINITE_FIELD_H__

#include "linear_algebra.h"

template <typename NUM>
void get_factorial_mod(NUM* factorial, int size, NUM mod) {
    // complexity: O(len(factorial))
    factorial[0] = factorial[1] = 1;
    for (int i = 2; i < size; i++) {
        factorial[i] = factorial[i - 1] * i % mod;
    }
}

template <typename NUM>
NUM power_mod(NUM base, NUM n, NUM mod) {
    // return base ** n % mod
    // complexity: O(log(n))
    NUM res = 1;
    NUM cur = base;

    while (n) {
        if (n % 2) {
            res = (res * cur) % mod;
        }
        n /= 2;
        cur = (cur * cur) % mod;
    }
    return res;
}

template <typename NUM>
NUM inv_mod_fermat(NUM n, NUM prime) {
    // inv_mod_fermat(n) * n % prime == 1
    // based on Fermat's little theorem.
    // complexity: O(log(prime))
    // assert(n < prime && prime * prime < MAX(NUM))
    assert(n < prime);
    return power_mod(n, prime - 2, prime);
}

template <typename num_t>
num_t _inv_mod_euclidean(num_t n, num_t p) {
    // euclidean algorithm.
    // if gcd(n, p) == 1 then n * x + p * y == 1
    // so (n * x + p * y) % p == n * x % p == 1
    // so x == inv(n)

    // this impliment is a little complex
    // because I try to use it to check matrix dot algorithm.
    // so use inv_mod_fermat instead.
    assert(n < p);
    int _p = p;

    int coef[4] = {1, 0, 0, 1};
    int trans[4] = {0, 1, 1, 0};
    int tmp[4];
    while (p) {
        // n, p = p, n - p * (n / p)
        trans[3] = -n / p;
        dot(coef, trans, tmp, 2, 2, 2);
        std::copy(tmp, tmp + 4, coef);

        num_t r = n % p;
        n = p;
        p = r;
    }
    if (n == 1) {
        return (coef[0] + _p) % _p;
    } else {
        return 0;
    }
}

template <typename NUM>
NUM combinations_mod(NUM n, NUM m, NUM prime, NUM* fact, NUM* inv_fact) {
    // get combinations, using calculated factorials & factorials ^ -1
    // assume m <= n && m >= 0 && n < prime
    // complexity: O(1)
    NUM res = fact[n];
    res = (res * inv_fact[m]) % prime;
    res = (res * inv_fact[n - m]) % prime;
    return res;
}

template <typename NUM>
NUM _combinations_mod(NUM n, NUM m, NUM prime) {
    // get combinations, without cached factorials & inv.
    // warning: this function maybe slow. (not recommand.)
    assert(n < prime && m <= n);
    NUM res = 1;
    for (NUM i = n; i > n - m; --i) {
        res = (res * i) % prime;
    }
    NUM demon = 1;
    for (NUM i = 1; i <= m; ++i) {
        demon = (demon * i) % prime;
    }
    return (res * inv_mod_fermat(demon, prime)) % prime;
}

// read this for understand the next tow functions:
// https://stackoverflow.com/questions/10118137/fast-base-choose-n-mod-prime-for-large-base
// those functions is just used for get nCr % p for n > p.
// warning: those two function is slow & complex. (not recommand.)
template <typename NUM>
NUM _rate_in_fact(NUM n, NUM prime) {
    // returns the rate with which prime is in n!
    // tool function for combinations_mod_
    NUM degree_num = 0;
    NUM u = prime;
    NUM temp = n;

    while (u <= temp) {
        degree_num += temp / u;
        u *= prime;
    }
    return degree_num;
}

template <typename NUM>
NUM _combinations_mod_checked(NUM n, NUM m, NUM prime) {
    // handle n > prime
    // return comb(n, m) % prime
    NUM num_degree = _rate_in_fact(n, prime) - _rate_in_fact(n - m, prime);
    NUM den_degree = _rate_in_fact(m, prime);

    if (num_degree > den_degree) {
        return 0;
    }
    NUM res = 1;
    for (NUM i = n; i > n - m; --i) {
        NUM ti = i;
        while (ti % prime == 0) {
            ti /= prime;
        }
        res = (res * ti) % prime;
    }
    for (NUM i = 1; i <= m; ++i) {
        NUM ti = i;
        while (ti % prime == 0) {
            ti /= prime;
        }
        res = (res * power_mod(ti, prime - 2, prime)) % prime;
    }
    return res;
}

void _test_inv() {
    int n, p = 2179;
    for (int i = 0; i < 10; i++) {
        n = rand() % p;
        int rf = inv_mod_fermat(n, p);
        int re = _inv_mod_euclidean(n, p);
        printf("n: %d; p: %d; inv_f(n): %d; chk: %d\n", n, p, rf, rf * n % p);
        printf("n: %d; p: %d; inv_e(n): %d; chk: %d\n", n, p, re, re * n % p);
    }
}
#endif