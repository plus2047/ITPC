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
    NUM res = 1, cur = base;
    while (n) {
        if (n & 1) res = (res * cur) % mod;
        cur = (cur * cur) % mod;
        n /= 2;
    }
    return res;
}

const lld MOD = 1E9 + 7;

void solve(int _turn) {
    lld A, B, N, K;
    scanf("%lld%lld%lld%lld", &A, &B, &N, &K);

    lld res = 0;
    for(lld i = 1; i <= N; i++) {
        for(lld j = 1; j <= N; j++) {
            if(i != j) {
                lld ei = pow_mod(i, A, K);
                lld ej = pow_mod(j, B, K);
                res += (ei + ej) % K == 0;
            }
        }
    }

    printf("Case #%d: %lld\n", _turn + 1, res);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
