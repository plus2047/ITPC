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

void solve(int _turn) {
    lld N, M;
    scanf("%lld%lld", &N, &M);

    vector<lld> fact(N + 1);
    fact[0] = fact[1] = 1;
    for (int i = 2; i <= N; i++) {
        fact[i] = fact[i - 1] * i % M;
    }

    vector<lld> c1(N + 1);
    c1[1] = 1;
    for (int i = 2; i <= N; i++) {
        c1[i] = fact[i];
        for (int j = 1; j < i; j++) {
            c1[i] = (c1[i] - c1[j] * fact[i - j] % M + M) % M;
        }
    }

    vector<vector<lld> > dp(N + 1, vector<lld>(3));
    dp[1] = {1, 1, 1};
    for (int i = 2; i <= N; i++) {
        dp[i] = {c1[i], c1[i], c1[i]};
        for (int j = 1; j < i; j++) {
            lld c = c1[j] % M;
            int k = i - j;
            dp[i][0] = (dp[i][0] + c * dp[k][0] % M) % M;
            dp[i][1] = (dp[i][1] + c * ((dp[k][1] + dp[k][0]) % M) % M) % M;
            dp[i][2] = (dp[i][2] + c * ((dp[k][2] + dp[k][0]) % M + 2 * dp[k][1] % M) % M) % M;
        }
    }

    printf("Case #%d: %lld\n", _turn + 1, dp[N][2] % M);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
