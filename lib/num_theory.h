#pragma once

#include <vector>

namespace contest {

// this function can get primes less than 1E9 in 4 seconds.
// all flags should be init as true
// assert flags.size() >= 2
void prime_flags(std::vector<bool>& flags) {
    int lim = int(flags.size());
    flags[0] = flags[1] = false;
    for (int n = 4; n < lim; n += 2) {
        flags[n] = false;
    }
    for (int n = 3; n * n <= lim; n += 2) {
        if (flags[n]) {
            for (int t = n * 3; t < lim; t += n << 1) {
                flags[t] = false;
            }
        }
    }
}

// worst complexity: O(num ^ 0.5)
template <typename NUM = int>
std::vector<NUM> prime_fact(NUM num) {
    std::vector<NUM> res;
    while (num % 2 == 0) {
        num /= 2;
        res.push_back(2);
    }
    for (int p = 3; p * p <= num; p += 2) {
        while (num % p == 0) {
            res.push_back(p);
            num /= p;
        }
    }
    if (num > 1) res.push_back(num);
    return res;
}

template <typename NUM>
inline NUM pow_mod(NUM base, NUM n, NUM MOD) {  // base ** n % MOD
    NUM res = 1, cur = base;
    while (n) {
        if (n % 2) res = (res * cur) % MOD;
        cur = (cur * cur) % MOD;
        n /= 2;
    }
    return res;
}

// inv(n) * n % mod == 1
// based on Fermat's little theorem.
// if PHI = MOD is prime ? MOD - 1 : totient(MOD)
// assert(num < MOD);
template <typename NUM>
inline NUM inv_mod(NUM num, NUM PHI, NUM MOD) {
    return pow_mod(num, PHI - 1, MOD);
}

// N chooce k mod MOD
// pre-calculated: fact[i] = i!, ifact[i] = inv(fact[i])
// assert(k <= N and k >= 0 and N < MOD);
template <typename NUM>
NUM comb_mod(std::vector<NUM>& fact, std::vector<NUM>& ifact, NUM N, NUM k,
             NUM MOD) {
    NUM res = fact[N];
    res = (res * ifact[k]) % MOD;
    res = (res * ifact[N - k]) % MOD;
    return res;
}

// Euler's totient function
template <typename NUM>
NUM totient(NUM num) {
    std::vector<NUM> facts = prime_fact(num);
    facts.push_back(-1);
    NUM res = 1, p = facts[0];
    int cnt = 0;
    for (NUM f : facts) {
        if (f != p) {
            while (--cnt) res *= p;
            res *= p - 1;
            p = f;
            cnt = 1;
        } else {
            cnt++;
        }
    }
    return res;
}

}  // namespace contest