#pragma once

#include <cmath>
#include <vector>

namespace contest {

struct log2Calculater {
    typedef double num;
    std::vector<num> fact;
    log2Calculater(int lim) : fact(lim) {
        fact[0] = fact[1] = 0;
        for (int i = 2; i < lim; i++) {
            fact[i] = fact[i - 1] + log2(num(i));
        }
    }
    inline num comb(int N, int k) { return fact[N] - fact[k] - fact[N - k]; }
};

}  // namespace contest