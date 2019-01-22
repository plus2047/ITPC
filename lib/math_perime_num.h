#pragma once
// get_prime_algorithm.
#include <vector>

namespace contest {
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

// not recommand because it's slower.
std::vector<int> _get_prime_list_division(int less_than) {
    std::vector<int> prime(1, 2);
    for (int num = 3; num < less_than; num++) {
        bool is_prime = true;
        for (int i = 0; i < prime.size(); i++) {
            if (num % prime[i] == 0) {
                is_prime = false;
                break;
            } else if (prime[i] * prime[i] > num) {
                break;
            }
        }
        if (is_prime) prime.push_back(num);
    }
    return prime;
}
}  // namespace contest
