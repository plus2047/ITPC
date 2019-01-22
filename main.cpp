// ===== programing contest template =========
// ===== using standrod: C++ 14 ==============

#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// ===== if using persional toolbox =====
#define __TOOLBOX__

// ===== include persional toolbox ======
#ifdef __TOOLBOX__
#include "lib/graph.h"
#include "lib/iotools.h"
#include "lib/math.h"
#include "lib/structure.h"
using namespace contest;
#endif  // __TOOLBOX__

// for contest, it's okey to use namespace. =====
using namespace std;

// ============= CONTEST ENV BEGIN =============

typedef long long int LL;
typedef long long unsigned LLU;
typedef long double LD;
#define G(_tuple, num) (get<num>(_tuple))
#define popcount(x) __builtin_popcount(x)
#define popcountll(x) __builtin_popcountll(x)
#define len(c) int((c).size())
#define allof(container) container.begin(), container.end()
#define iallof(container) container.rbegin(), container.rend()
#define rep(i, N) for (int i = 0; i < int(N); i++)
#define range(i, begin, end) for (int i = int(begin); i < int(end); i++)
#define irep(i, N) for (int i = int(N) - 1; i >= 0; i--)
#define irange(i, begin, end) for (int i = int(end) - 1; i >= int(begin); i--)

// =============== CONTEST BEGIN ===============

// const ===
const int N_MAX = 5E5, M_MAX = 1E6;

// turn var =====
LL M, N, A, B, C, D, E, F, cnt;

// turn data ====
typedef tuple<LL, LL> Point;
vector<Point> points(N_MAX);

// init turn data & var:
void init_turn() { cnt = 0; }

// algorithm functions =====
bool valid(int i, int j, int k) {
    LL x[3][2], idx[3];
    tie(idx[0], idx[1], idx[2]) = tie(i, j, k);
    rep(n, 3) tie(x[n][0], x[n][1]) = points[idx[n]];

    LL min_[2], max_[2];
    rep(n, 2) {
        min_[n] = min({x[0][n], x[1][n], x[2][n]});
        max_[n] = max({x[0][n], x[1][n], x[2][n]});
    }

    // if any points not in any line.
    rep(n, 3) {
        bool on_line = false;
        rep(m, 2) {
            if (x[n][m] == min_[m] or x[n][m] == max_[m]) on_line = true;
        }
        if (!on_line) return false;
    }
    return true;
}

// kickstart turn template =====
void solve(int _turn) {
    init_turn();

    // read & generate data:
    scanf("%lld%lld%lld", &N, &G(points[0], 0), &G(points[0], 1));
    scanf("%lld%lld%lld%lld%lld%lld%lld", &A, &B, &C, &D, &E, &F, &M);
    range(i, 1, N) {
        int x, y;
        tie(x, y) = points[i - 1];
        points[i] = {(A * x + B * y + C) % M, (D * x + E * y + F) % M};
    }
    // rep(i, N) echo("point: %d, %d\n", G(points[i], 0), G(points[i], 1));

    // solve question:
    rep(i, N) range(j, i + 1, N) range(k, j + 1, N) {
        if (valid(i, j, k)) cnt++;
    }
    echo("Case #%d: %lld\n", _turn, cnt);
}

int main() {
#ifdef __LOCAL__  // define in build command.
    freopen("_kickstart.in", "r", stdin);
    // freopen("_debug.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
