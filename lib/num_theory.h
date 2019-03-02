#pragma once

#include <cmath>
#include <forward_list>
#include <initializer_list>
#include <vector>

namespace contest {

std::vector<int> get_primes(int less_than) {
    if (less_than <= 2) return {};
    std::vector<char> flag(less_than, true);  // vector<char> is faster
    std::vector<int> mod = {2};
    for (int num = 3; num < less_than; num += 2) {
        if (!flag[num])
            continue;
        else {
            mod.push_back(num);
            for (int i = 2; i * num < less_than; i++) flag[i * num] = false;
        }
    }
    return mod;
}

template <typename NUM = int>
std::vector<NUM> prime_fact(NUM num) {  // worst complexity: O(num ^ 0.5)
    std::vector<NUM> res;

    while (num % 2 == 0) {
        num /= 2;
        res.push_back(2);
    }

    for (int p = 3; p * p <= num; p += 2) {
        if (num % p == 0) {
            while (num % p == 0) {
                res.push_back(p);
                num /= p;
            }
        }
    }

    if (num > 1) res.push_back(num);

    return res;
}

template <typename NUM>
NUM totient(NUM num) {  // Euler's totient function
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

template <typename NUM>
struct ModNCalculator {
    const NUM MAX_NUM, MOD;
    NUM PHI;                          // Euler's totient function
    std::vector<NUM> fact, inv_fact;  // factorial & it's inverse

    inline NUM multiply(std::initializer_list<NUM> nums) {
        NUM res = 1;
        for (auto p = nums.begin(); p != nums.end(); p++) {
            res = res * (*p) % MOD;
        }
        return res;
    }

    inline NUM pow(NUM base, NUM n) {  // base ** n % MOD
        NUM res = 1, cur = base;
        while (n) {
            if (n % 2) res = (res * cur) % MOD;
            cur = (cur * cur) % MOD;
            n /= 2;
        }
        return res;
    }

    inline NUM inv(NUM num) {  // inv(n) * n % mod == 1
        // based on Fermat's little theorem.
        assert(num < MOD);
        return power(num, PHI - 1);
    }

    inline NUM comb(NUM N, NUM k) {
        // N chooce k mod MOD
        assert(k <= N and k >= 0 and N < MOD);
        NUM res = fact[N];
        res = (res * inv_fact[k]) % MOD;
        res = (res * inv_fact[N - k]) % MOD;
        return res;
    }

    ModNCalculator(NUM max_num, NUM mod, bool is_prime)
        : MAX_NUM(max_num), MOD(mod), fact(max_num + 1), inv_fact(max_num + 1) {
        assert(1.0 * MOD * MOD < 1.0 * std::numeric_limits<NUM>::max());
        PHI = is_prime ? mod - 1 : totient(mod);
        if (max_num < 1) return;
        // init the calculator's pre-calculated factorial & inv
        // if donot need to use fact & comb, just set max_num = 0.
        fact[0] = fact[1] = 1;
        inv_fact[0] = inv_fact[1] = 1;
        for (int i = 2; i <= MAX_NUM; i++) {
            fact[i] = fact[i - 1] * i % MOD;
            inv_fact[i] = inv(fact[i]);
        }
    }
};
}  // namespace contest