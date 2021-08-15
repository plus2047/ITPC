#pragma once
#include <array>
#include <cstdint>
#include <vector>

namespace contest {

// it's eary to be modified this string hash to calculate hash for each prefix.
// if need to get hash for each substr with length == n
// just reduce str[i - n] * (33 ** n), donot worry about negative.
inline unsigned hash_str(unsigned char* str) {
    // hash * 33 + c, ancient magic.
    unsigned hash = 5381;
    while (*str) hash = ((hash << 5) + hash) + *(str++);
    return hash;
}

// hash function for unsigned 32
// also can be used to other integer type.
inline unsigned hash_u32(unsigned x, unsigned size) { return x * 2654435761 % size; }

// // TODO this not finished, many small bugs
// template <int N>
// struct RollingHash {
//     typedef array<uint32_t, N> Arr;
//     Arr base, mod;
//     vector<Arr> exp;
//     vector<Arr> vec;
//     RollingHash(Arr base, Arr mod) : base(base), mod(mod), exp(1, 1) {}
//     void push_back(NUM val) {
//         for (int i = 0; i < N; i++) {
//             exp.push_back(uint32_t(1LL * exp.back() * base[i] % mod[i]));
//             vec.push_back(uint32_t((1LL * vec.back() * base[i] % mod[i] + val) % mod));
//         }
//     }
//     Arr get(int left, int right) {
//         Arr res;
//         for (int i = 0; i < N; i++) {
//             res[i] = (1LL * vec[right][i] - 1LL * vec[left][i] * exp[left][i] % mod + mod) % mod;
//         }
//         return res;
//     }
// };

}  // namespace contest