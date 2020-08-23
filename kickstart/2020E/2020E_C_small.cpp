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
    vector<lld> E(N), R(N);
    rep(i, N) scanf("%lld%lld", &E[i], &R[i]);
    lld total = accumulate(allof(E), lld(0));

    int y = 0;
    lld z = 0;
    lld INF = INT64_MAX;

    unsigned M = 1 << N;
    for (unsigned m = 1; m < M; m++) {
        lld total = 0;
        int rm = N;
        for(int i = 0; i < N; i++) {
            if((1 << i) & m) {
                total += E[i];
                rm--;
            }
        }
        bool block = false;
        lld delta = 0;
        for(int i = 0; i < N; i++) {
            if((1 << i) & m) {
                if(total - E[i] < R[i]) {
                    if(total + delta >= z) {
                        y = total + delta == z ? min(y, rm) : rm;
                        z = total + delta;
                    }
                    block = true;
                    break;
                } else {
                    delta += E[i];
                }
            }
        }
        if(not block) {
            y = z == INF ? min(y, rm) : rm;
            z = INF;
        }
    }
    
    printf("Case #%d: %d", _turn + 1, y);
    if (z != INF) {
        printf(" %lld\n", z);
    } else {
        printf(" INDEFINITELY\n");
    }
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
