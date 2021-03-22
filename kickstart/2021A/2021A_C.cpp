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
void solve(int _turn) {
    lld R, C;
    scanf("%lld%lld", &R, &C);
    lld grid[R][C];
    rep(i, R) {
        rep(j, C) { scanf("%lld", &grid[i][j]); }
    }
    priority_queue<tuple<lld, lld, lld> > pq;
    bool seen[R][C];
    rep(i, R) rep(j, C) {
        pq.push({grid[i][j], i, j});
        seen[i][j] = true;
    }
    lld res = 0;
    while (pq.size()) {
        lld h, i, j;
        tie(h, i, j) = pq.top();
        pq.pop();
        seen[i][j] = false;
        lld neighbor =
            max({i == 0 ? 0 : grid[i - 1][j], i == R - 1 ? 0 : grid[i + 1][j],
                 j == 0 ? 0 : grid[i][j - 1], j == C - 1 ? 0 : grid[i][j + 1]});
        if (neighbor > h + 1) {
            // printf("n: %lld, h: %lld, i: %lld, j: %lld\n", neighbor, h, i, j);
            res += neighbor - (h + 1);
            grid[i][j] = neighbor - 1;
            if (i != 0 and not seen[i - 1][j]){
                pq.push({grid[i - 1][j], i - 1, j});
                seen[i - 1][j] = true;
            }
            if (i != R - 1 and not seen[i + 1][j]){
                pq.push({grid[i + 1][j], i + 1, j});
                seen[i + 1][j] = true;
            }
            if (j != 0 and not seen[i][j - 1]){
                pq.push({grid[i][j - 1], i, j - 1});
                seen[i][j - 1] = true;
            }
            if (j != C - 1 and not seen[i][j + 1]){
                pq.push({grid[i][j + 1], i, j + 1});
                seen[i][j + 1] = true;
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
