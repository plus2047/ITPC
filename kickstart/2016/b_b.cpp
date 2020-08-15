// ===== programing contest template ======

#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <bitset>
#include <functional>
#include <random>
#include <unordered_map>
#include <unordered_set>
#endif  // C++11

using namespace std;

typedef long long int lld;
#define frontof(c, k) (c).begin(), (c).begin() + (k)
#define allof(c) (c).begin(), (c).end()
#define len(container) int((container).size())
#define asmin(var, val) var = min(var, val)
#define asmax(var, val) var = max(var, val)
#define rep(i, N) for (int i = 0; i < int(N); ++i)
#define inv(i, N) for (int i = int(N) - 1; i >= 0; --i)

// ========== contest code ==========
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

const lld MOD = 1E9 + 7;

void solve(int _turn) {
    lld A, B, N, K;
    scanf("%lld%lld%lld%lld", &A, &B, &N, &K);

    vector<lld> cA(K), cB(K);
    lld loop = N / K % MOD, rem = N % K, block = 0;
    for(lld i = 1; i <= K; i++) {
        lld ei = pow_mod(i, A, K);
        lld ej = pow_mod(i, B, K);
        lld delta = loop + (i <= rem ? 1 : 0);
        cA[ei] += delta;
        cB[ej] += delta;
        cA[ei] %= MOD;
        cB[ej] %= MOD;
        if((ei + ej) % K == 0) {
            block += delta;
            block %= MOD;
        }
    }

    lld res = 0;
    for(int i = 0; i < K; i++) {
        res += cA[i] * cB[i == 0 ? 0 : K - i];
        res %= MOD;
    }
    res = (res - block + MOD) % MOD;

    printf("Case #%d: %lld\n", _turn + 1, res);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
