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

}  // namespace contest