#pragma once

#include <initializer_list>
#include <vector>

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

std::vector<int> get_prime_list(int less_than) {
    std::vector<bool> flag((size_t)less_than, true);
    std::vector<int> prime;
    for (int num = 2; num < less_than; num++) {
        if (!flag[num])
            continue;
        else {
            prime.push_back(num);
            for (int i = 2; i * num < less_than; i++) flag[i * num] = false;
        }
    }
    return prime;
}
}  // namespace contest