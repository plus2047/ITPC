#pragma once

#include <vector>

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

}  // namespace contest