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
    int N;
    scanf("%d", &N);
    vector<int> A(N);
    rep(i, N) { scanf("%d", &A[i]); }

    int MS = N * 100;
    vector<int> can;
    for (int i = 0;; i++) {
        int ii = i * i;
        if (ii > MS) break;
        can.push_back(ii);
    }

    vector<int> cnt(MS * 2 + 1);
    lld pre = 0, res = 0;
    cnt[0 + MS] = 1;
    rep(i, N) {
        pre += A[i];
        for (int s : can) {
            int t = pre - s;
            if (t > MS or t < -MS) continue;
            res += lld(cnt[t + MS]);
        }
        cnt[pre + MS]++;
    }

    printf("Case #%d: %lld\n", _turn + 1, res);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
