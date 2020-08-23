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

void print1(int N) {
    for (int i = 0; i < N; i++) {
        printf(" 1");
    }
}

void solve(int _turn) {
    int N, A, B, C;
    scanf("%d%d%d%d", &N, &A, &B, &C);
    int a = A - C, b = B - C;
    if (a + b + C > N or (a == 0 and b == 0 and C == 1 and N != 1)) {
        printf("Case #%d: IMPOSSIBLE\n", _turn + 1);
    } else {
        printf("Case #%d:", _turn + 1);
        for (int i = 1; i <= a; i++) {
            printf(" %d", N - a + i - 1);
        }
        if (a != 0) {
            print1(N - a - b - C);
        }
        for (int i = 1; i <= C; i++) {
            printf(" %d", N);
            if (a == 0 and i == 1 and C != 1) {
                print1(N - a - b - C);
            }
        }
        if (a == 0 and C == 1) {
            print1(N - a - b - C);
        }
        for (int i = 1; i <= b; i++) {
            printf(" %d", N - i);
        }
        printf("\n");
    }
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
