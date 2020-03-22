// ===== programing contest template ======
// ===== using standrod: C++ 11 =====

// #undef __LOCAL__

#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <map>
#include <queue>
#include <set>
#include <stack>
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

// ===== personal contest env =====

typedef long long int lld;

#define frontof(c, k) (c).begin(), (c).begin() + (k)
#define allof(c) (c).begin(), (c).end()
#define len(container) int((container).size())
#define asmin(var, val) var = min(var, val)
#define asmax(var, val) var = max(var, val)

#define iter(i, begin, end) \
    for (int i = begin, d = begin < end ? 1 : -1; i != end; i += d)
#define each(i, first, last) \
    for (int i = first, d = first < last ? 1 : -1; i != last + d; i += d)

#define rep(i, N) for (int i = 0; i < int(N); ++i)
#define inv(i, N) for (int i = int(N) - 1; i >= 0; --i)

#if __cplusplus >= 201103L
template <typename num>
using mat = vector<vector<num> >;

template <typename num>
inline mat<num> make_mat(int s1, int s2, num val) {
    return mat<num>(s1, vector<num>(s2, val));
}

template <typename num>
inline void fill(mat<num>& m, num val) {
    for (auto& v : m)
        for (auto& n : v) n = val;
}

template <typename num>
void show(mat<num> m) {
    for (const auto& v : m) {
        for (const auto& n : v) cout << n << ' ';
        cout << endl;
    }
}
#endif  // C++11

template <typename ITER>
void show(const char* note, ITER begin, ITER end) {
#ifdef __LOCAL__
    std::cout << note;
    for (; begin != end; begin++) std::cout << *begin << ' ';
    cout << endl;
#endif  // __LOCAL__
}

void echo(const char* fmt, ...) {
#ifdef __LOCAL__
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
#endif  // __LOCAL__
}

// ===== personal contest template =====

// ========== contest code ==========
int N, K, P;
mat<int> score;  // N * K

// N * P, dp[n][p] is the max score if you pick p plates from [0:n + 1]
// dp[n][p] = max_i dp[n - 1][p - i] + sum_{0 <= j < i} score[n][j]
mat<int> dp;
const int INF = 1E7;

void solve(int _turn) {
    scanf("%d%d%d", &N, &K, &P);
    score = make_mat(N, K, 0);
    rep(i, N) rep(j, K) { scanf("%d", &score[i][j]); }

    dp = make_mat(N, K * N + 1, -INF);
    rep(i, N) { dp[i][0] = 0; }
    rep(i, K) { dp[0][i + 1] = score[0][i] + dp[0][i]; }
    iter(n, 1, N) each(p, 1, K * N) {
        int& r = dp[n][p];
        int pre = 0;
        rep(curr, p + 1) {
            r = max(r, dp[n - 1][p - curr] + pre);
            if(curr >= K) break;
            pre += score[n][curr];
        }
    }
    
    printf("Case #%d: %d\n", _turn, dp[N - 1][P]);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
