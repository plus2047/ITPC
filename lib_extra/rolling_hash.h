#pragma once
#include <vector>
#include <array>

// https://www.geeksforgeeks.org/string-hashing-using-polynomial-rolling-hash-function/

namespace contest {

struct Rolling {
    const static int hash_size = 2;
    typedef array<int, hash_size> Hash;

    // mod * mod < INT64_MAX
    const static int mod = 1e9 + 7;
    constexpr static Hash primes = {19, 23};
    constexpr static Hash zeros = {0, 0};
    constexpr static Hash ones = {1, 1};
    inline static std::vector<Hash> inv = {};

    int size = 0;
    std::vector<Hash> hash;

    Rolling(const std::string& s): size(s.size()), hash(s.size()) {
        if(size > 0) {
            init(s);
        }
    }

    void init(const std::string& s) {
        size = s.size();
        hash.resize(size);
        Hash h = zeros, p_pow = ones;
        for (int i = 0; i < size; i++) {
            for(int j = 0; j < hash_size; j++) {
                h[j] = (h[j] + 1LL * s[i] * p_pow[j]) % mod;
                p_pow[j] = (1LL * p_pow[j] * primes[j]) % mod;
            }
            hash[i] = h;
        }

        if(int(inv.size()) < size) {
            int prev_size = inv.size();
            inv.resize(size);

            for(int j = 0; j < hash_size; j++) {
                inv[size - 1][j] = power(primes[j], mod - size, mod);
            }

            for (int i = size - 2; i >= prev_size; i--) {
                for(int j = 0; j < hash_size; j++) {
                    inv[i][j] = (1LL * inv[i + 1][j] * primes[j]) % mod;
                }
            }
        }
    }

    Hash substr(const int l, const int r) {
        if (l == 0) {
            return hash[r];
        }
        Hash h;
        for(int i = 0; i < hash_size; i++) {
            h[i] = hash[r][i] - hash[l - 1][i];
            h[i] += h[i] < 0 ? mod : 0;
            h[i] = (1LL * h[i] * this->inv[l][i]) % mod;
        }
        return h;
    }

    static long long power(long long x, long long y, long long p) {
        long long result = 1;
        for (; y; y >>= 1, x = x * x % p) {
            if (y & 1) {
                result = result * x % p;
            }
        }
        return result;
    }

    static long long inverse(long long x, long long p) {
        return power(x, p - 2, p);
    }
};

}  // namespace contest
