#pragma once
#include <vector>
#include <array>

// https://www.geeksforgeeks.org/string-hashing-using-polynomial-rolling-hash-function/

namespace contest {

// Rolling Hash is used to get hash for any substring with O(1) speed
// Rolling60 combines two 30-bit hash functions
// for each one of them,
// hash(s) = sum(s[i] * pow(p, i) for i in range(len(s))) % mod
// where p and mod are primes
struct Rolling60 {
    const static long long p0 = 19, p1 = 23, mod = 1e9 + 7;
    std::vector<int> h0, h1, inv0, inv1;

    // h0[i] = sum(s[x] * pow(p0, x) for x in range(i))
    // inv0[i] * pow(p0, i) % mod == 1
    // using Fermat's little theorem to get inv0, etc.
    Rolling60(const std::string& s):
        h0(s.size()), h1(s.size()), inv0(s.size()), inv1(s.size()) {
        int n = s.size();
        long long h[2] = {0, 0}, p_pow[2] = {1, 1};
        for (int i = 0; i < n; i++) {
            h0[i] = h[0] = (h[0] + s[i] * p_pow[0]) % mod;
            h1[i] = h[1] = (h[1] + s[i] * p_pow[1]) % mod;
            p_pow[0] = p_pow[0] * p0 % mod;
            p_pow[1] = p_pow[1] * p1 % mod;
        }
        inv0[n - 1] = pow(p0, mod - n), inv1[n - 1] = pow(p1, mod - n);
        for(int i = n - 2; i >= 0; i--) {
            inv0[i] = inv0[i + 1] * p0 % mod;
            inv1[i] = inv1[i + 1] * p1 % mod;
        }
    }

    // hash0(l, r) = sum(s[x] * pow(p0, x - left) for x in [left, right]) % mod
    // = sum(s[x] * pow(p0, x)) * inv0[left] % mod
    long long substr(int l, int r) {
        if(l == 0) return ((long long)h0[r] << 32) + h1[r];
        long long x = (long long)(h0[r] - h0[l - 1] + mod) * inv0[l] % mod;
        long long y = (long long)(h1[r] - h1[l - 1] + mod) * inv1[l] % mod;
        return (x << 32) + y;
    }

    static long long pow(long long x, long long y) {
        long long result = 1;
        for (; y; y >>= 1, x = x * x % mod) {
            if (y & 1) result = result * x % mod;
        }
        return result;
    }
};

struct Rolling120 {
    const static long long p0 = 19, p1 = 23, p2 = 29, p3 = 31, mod = 1e9 + 7;
    std::vector<int> h0, h1, h2, h3, inv0, inv1, inv2, inv3;

    Rolling120(const std::string& s):
        h0(s.size()), h1(s.size()), h2(s.size()), h3(s.size()),
        inv0(s.size()), inv1(s.size()), inv2(s.size()), inv3(s.size()) {
        int n = s.size();
        long long h[4] = {0, 0, 0, 0}, p_pow[4] = {1, 1, 1, 1};
        for (int i = 0; i < n; i++) {
            h0[i] = h[0] = (h[0] + s[i] * p_pow[0]) % mod;
            h1[i] = h[1] = (h[1] + s[i] * p_pow[1]) % mod;
            h2[i] = h[2] = (h[2] + s[i] * p_pow[2]) % mod;
            h3[i] = h[3] = (h[3] + s[i] * p_pow[3]) % mod;
            p_pow[0] = p_pow[0] * p0 % mod;
            p_pow[1] = p_pow[1] * p1 % mod;
            p_pow[2] = p_pow[2] * p2 % mod;
            p_pow[3] = p_pow[3] * p3 % mod;
        }
        inv0[n - 1] = pow(p0, mod - n);
        inv1[n - 1] = pow(p1, mod - n);
        inv2[n - 1] = pow(p2, mod - n);
        inv3[n - 1] = pow(p3, mod - n);
        for(int i = n - 2; i >= 0; i--) {
            inv0[i] = inv0[i + 1] * p0 % mod;
            inv1[i] = inv1[i + 1] * p1 % mod;
            inv2[i] = inv2[i + 1] * p2 % mod;
            inv3[i] = inv3[i + 1] * p3 % mod;
        }
    }

    pair<long long, long long> substr(int l, int r) {
        if(l == 0) return {
            ((long long)h0[r] << 32) + h1[r], 
            ((long long)h2[r] << 32) + h3[r]
        };
        long long x = (long long)(h0[r] - h0[l - 1] + mod) * inv0[l] % mod;
        long long y = (long long)(h1[r] - h1[l - 1] + mod) * inv1[l] % mod;
        long long a = (long long)(h2[r] - h2[l - 1] + mod) * inv2[l] % mod;
        long long b = (long long)(h3[r] - h3[l - 1] + mod) * inv3[l] % mod;
        return {(x << 32) + y, (a << 32) + b};
    }

    static long long pow(long long x, long long y) {
        long long result = 1;
        for (; y; y >>= 1, x = x * x % mod) {
            if (y & 1) result = result * x % mod;
        }
        return result;
    }
};

template<>
struct std::hash<pair<long long, long long>>
{
    std::size_t operator()(const pair<long long, long long>& h) const noexcept {
        return h.first ^ (h.second << 1); // or use boost::hash_combine
    }
};

}  // namespace contest
