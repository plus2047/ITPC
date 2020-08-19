#pragma once

#include <vector>

namespace contest {

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