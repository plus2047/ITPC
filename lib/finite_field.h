#ifndef __FINITE_FIELD_H__
#define __FINITE_FIELD_H__

#include <cassert>
#include <cstdio>

template <typename NUM>
void get_factorial_mod(NUM* factorial, size_t size, NUM prime) {
    // complexity: O(len(factorial))
    factorial[0] = factorial[1] = 1;
    for (size_t i = 2; i < size; i++) {
        factorial[i] = factorial[i - 1] * i % prime;
    }
}

template <typename NUM>
NUM power_mod(NUM base, NUM exp, NUM prime) {
    // return base ** exp % prime
    // complexity: O(log(exp))
    NUM res = 1;
    NUM cur = base;

    while (exp) {
        if (exp % 2) {
            res = (res * cur) % prime;
        }
        exp /= 2;
        cur = (cur * cur) % prime;
    }
    return res;
}

template <typename NUM>
NUM inv_mod(NUM n, NUM prime) {
    // inv_mod(n) * n % prime == 1
    // complexity: O(log(prime))
    return power_mod(n, prime - 2, prime);
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
    return (res * inv_mod(demon, prime)) % prime;
}


// read this for understand the next tow functions:
// https://stackoverflow.com/questions/10118137/fast-base-choose-exp-mod-prime-for-large-base
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
#endif