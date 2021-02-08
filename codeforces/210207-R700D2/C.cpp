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
    lld n = 0;
    scanf("%lld", &n);
    lld nq = 98;

    lld left = 1, right = n;
    while (right - left + 1 > nq) {
        lld m1 = (left + right) / 2;
        lld m2 = m1 + 1;
        lld v1, v2;
        printf("? %lld\n", m1);
        fflush(stdout);
        printf("? %lld\n", m2);
        fflush(stdout);
        scanf("%lld", &v1);
        scanf("%lld", &v2);
        if (v1 < v2) {
            right = m1;
        } else {
            left = m2;
        }
        nq -= 2;
    }

    lld x = n + 1, y = n + 1, z = 0;
    for (lld i = left; i <= right; i++) {
        printf("? %lld\n", i);
        fflush(stdout);
        scanf("%lld", &z);
        if (y < x and y < z) {
            printf("! %lld\n", i - 1);
            fflush(stdout);
            return;
        }
        x = y;
        y = z;
    }
    printf("! %lld\n", right);
    fflush(stdout);
}

int main() {
    int T = 1;
    rep(t, T) { solve(t); }
}
