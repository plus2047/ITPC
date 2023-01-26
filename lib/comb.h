#pragma once

#include <vector>
#include <cmath>

namespace contest {

template <typename NUM>
inline NUM pow_mod(NUM base, NUM n, NUM mod) {  // base ** n % mod
    NUM res = 1;
    while (n) {
        if (n % 2) res = (res * base) % mod;
        base = (base * base) % mod;
        n /= 2;
    }
    return res % mod;  // handle n == 0
}

// inv(n) * n % mod == 1
// based on Fermat's little theorem, a ^ (p - 1) % p = 1
// PHI = (MOD is prime ? MOD - 1 : totient(MOD))
// ONLY works when gcd(n, mod) == 1
// assert(num < MOD);
template <typename NUM>
inline NUM inv_mod(NUM num, NUM PHI, NUM MOD) {
    return pow_mod(num, PHI - 1, MOD);
}

// N chooce k mod MOD
// pre-calculated: fact[i] = i!, ifact[i] = inv(fact[i])
// assert(k <= N and k >= 0 and N < MOD);
template <typename NUM>
inline NUM comb_mod(std::vector<NUM>& fact, std::vector<NUM>& ifact, NUM N,
                    NUM k, NUM MOD) {
    NUM res = fact[N];
    res = (res * ifact[k]) % MOD;
    res = (res * ifact[N - k]) % MOD;
    return res;
}

template <typename NUM>
inline void init_fact_mod(std::vector<NUM>& fact, std::vector<NUM>& ifact, NUM N) {
    fact[0] = fact[1] = ifact[0] = ifact[1] = 1;
    for (NUM i = 2; i < N; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
        ifact[i] = inv_mod(fact[i], MOD - 1, MOD);
    }
}

inline void init_fact_log(std::vector<double>& fact, int N) {
    fact[0] = fact[1] = 0;
    for (int i = 2; i < N; i++) {
        fact[i] = fact[i - 1] + log2(double(i));
    }
}

inline double comb_log(std::vector<double>& fact, int n, int k) {
    return fact[n] - fact[k] - fact[n - k];
}

}  // namespace contest