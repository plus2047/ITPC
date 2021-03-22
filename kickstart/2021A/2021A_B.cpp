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

// #undef __LOCAL__

template <typename ITER>
void print(const char* note, ITER begin, ITER end) {
#ifdef __LOCAL__
    std::cout << note;
    for (; begin != end; begin++) std::cout << *begin << ' ';
    cout << endl;
#endif  // __LOCAL__
}

void print(const char* fmt, ...) {
#ifdef __LOCAL__
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
#endif  // __LOCAL__
}

// ========== contest code ==========

inline lld countL(lld x, lld y) { return max(min(x, y / 2) - 1, 0LL); }

const int N_MAX = 2E5 + 8;
char S[N_MAX];
void solve(int _turn) {
    lld R, C;
    scanf("%lld%lld", &R, &C);
    int grid[R][C], left[R][C], right[R][C], up[R][C], down[R][C];
    rep(i, R) {
        rep(j, C) {
            scanf("%d", &grid[i][j]);
            left[i][j] = right[i][j] = up[i][j] = down[i][j] = 0;
        }
    }
    rep(i, R) {
        rep(j, C) {
            if (grid[i][j]) {
                left[i][j] = (j == 0 ? 0 : left[i][j - 1]) + 1;
            }
        }
        inv(j, C) {
            if (grid[i][j]) {
                right[i][j] = (j == C - 1 ? 0 : right[i][j + 1]) + 1;
            }
        }
    }
    rep(j, C) {
        rep(i, R) {
            if (grid[i][j]) {
                up[i][j] = (i == 0 ? 0 : up[i - 1][j]) + 1;
            }
        }
        inv(i, R) {
            if (grid[i][j]) {
                down[i][j] = (i == R - 1 ? 0 : down[i + 1][j]) + 1;
            }
        }
    }
    lld res = 0;
    rep(i, R) {
        rep(j, C) {
            res += countL(left[i][j], up[i][j]);
            res += countL(left[i][j], down[i][j]);
            res += countL(right[i][j], up[i][j]);
            res += countL(right[i][j], down[i][j]);
            res += countL(up[i][j], left[i][j]);
            res += countL(up[i][j], right[i][j]);
            res += countL(down[i][j], left[i][j]);
            res += countL(down[i][j], right[i][j]);
        }
    }
    printf("Case #%d: %lld\n", _turn + 1, res);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
