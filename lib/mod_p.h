#pragma once

#include <initializer_list>
#include "linear_algebra.h"

namespace contest {

template <typename NUM>
struct ModPCalculator {
    const NUM MAX_NUM, PRIME;
    std::vector<NUM> fact, inv_fact;  // factorial & it's inverse

    inline NUM multiply(std::initializer_list<NUM> nums) {
        NUM res = 1;
        for (auto p = nums.begin(); p != nums.end(); p++) {
            res = res * (*p) % PRIME;
        }
        return res;
    }

    inline NUM power(NUM base, NUM n) {  // base ** n % PRIME
        NUM res = 1, cur = base;
        while (n) {
            if (n % 2) res = (res * cur) % PRIME;
            cur = (cur * cur) % PRIME;
            n /= 2;
        }
        return res;
    }

    inline NUM inv(NUM num) {  // inv(n) * n % prime == 1
        // based on Fermat's little theorem.
        assert(num < PRIME);
        return power(num, PRIME - 2);
    }

    inline NUM comb(NUM N, NUM k) {
        // N chooce k mod PRIME
        assert(k <= N and k >= 0 and N < PRIME);
        NUM res = fact[N];
        res = (res * inv_fact[k]) % PRIME;
        res = (res * inv_fact[N - k]) % PRIME;
        return res;
    }

    ModPCalculator(NUM max_num, NUM prime)
        : MAX_NUM(max_num),
          PRIME(prime),
          fact(max_num + 1),
          inv_fact(max_num + 1) {
        // init the calculator's pre-calculated factorial & inv
        // if donot need to use fact & comb, just set max_num = 0.
        assert(1.0 * PRIME * PRIME < 1.0 * std::numeric_limits<NUM>::max());
        if (max_num < 1) return;
        fact[0] = fact[1] = 1;
        inv_fact[0] = inv_fact[1] = 1;
        for (int i = 2; i <= MAX_NUM; i++) {
            fact[i] = fact[i - 1] * i % PRIME;
            inv_fact[i] = inv(fact[i]);
        }
    }
};

template <typename num_t>
num_t _inv_mod_euclidean(num_t n, num_t p) {
    // euclidean algorithm.
    // if gcd(n, p) == 1 then n * x + p * y == 1
    // so (n * x + p * y) % p == n * x % p == 1
    // so x == inv(n)

    // this impliment is a little complex
    // so use inv_mod instead.

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
}  // namespace contest