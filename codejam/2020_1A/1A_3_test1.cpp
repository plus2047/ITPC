// ===== programing contest template ======
// ===== using standrod: C++ 11 =====

// #undef __LOCAL__

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
int R, C;
mat<int> G, M;

pair<int, bool> step(mat<int>& G) {
    int total = 0;
    for (auto& v : G) {
        for (int n : v) {
            total += n;
        }
    }
    rep(i, R) rep(j, C) {
        if (G[i][j] == 0) {
            M[i][j] = false;
            continue;
        }
        int n_total = 0, n_cnt = 0;
        const static int D[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (int d = 0; d < 4; d++) {
            for (int _i = i + D[d][0], _j = j + D[d][1];
                 _i >= 0 and _i < R and _j >= 0 and _j < C;
                 _i += D[d][0], _j += D[d][1]) {
                if (G[_i][_j] != 0) {
                    n_total += G[_i][_j];
                    n_cnt++;
                    break;
                }
            }
        }
        M[i][j] = ((n_cnt != 0) and G[i][j] * n_cnt < n_total);
    }

    bool change = false;
    rep(i, R) rep(j, C) {
        if (M[i][j]) {
            change = true;
            G[i][j] = 0;
        }
    }
    return make_pair(total, change);
}

// ========== contest code ==========
void solve(int _turn) {
    // KEEP CALM AND CARRY ON!
    scanf("%d%d", &R, &C);

    G = make_mat(R, C, 0);
    M = make_mat(R, C, 0);

    rep(i, R) rep(j, C) { scanf("%d", &G[i][j]); }
    lld total = 0;
    bool change = true;
    while (change) {
        int score;
        tie(score, change) = step(G);
        total += score;
    }
    printf("Case #%d: %lld\n", _turn + 1, total);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
