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
    int K;
    scanf("%d", &K);
    vector<int> A(K);
    rep(i, K) { scanf("%d", &A[i]); }
    vector<int> delta;
    int prev = 0, cnt = 0;
    rep(i, K - 1) {
        if(A[i + 1] == A[i]) continue;
        int d = A[i + 1] - A[i] > 0 ? 1 : -1;
        if(i == 0) {
            prev = d;
            cnt = 1;
        } else {
            if(d == prev) {
                cnt++;
            } else {
                delta.push_back(cnt);
                prev = d;
                cnt = 1;
            }
        }
    }
    delta.push_back(cnt);

    lld res = 0;
    for(int n: delta) {
        res += n / 4;
    }
    printf("Case #%d: %lld\n", _turn + 1, res);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
