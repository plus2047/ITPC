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
#include "lib/segment_tree.h"
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
#define allof(container) (container).begin(), (container).end()
#define frontof(container, N) (container).begin(), (container).begin() + (N)
#define rep(i, N) for (int i = 0; i < int(N); i++)
#define range(i, begin, end) for (int i = int(begin); i < int(end); i++)
#define irep(i, N) for (int i = int(N) - 1; i >= 0; i--)
#define irange(i, begin, end) for (int i = int(end) - 1; i >= int(begin); i--)

// =============== CONTEST BEGIN ===============

// const ===
const int N_MAX = 5E5, M_MAX = 1E6;
typedef tuple<LL, LL> Point;

// turn var =====
LL M, N, A, B, C, D, E, F;

// turn data ====
vector<Point> points(N_MAX);
vector<LL> lu(N_MAX), ld(N_MAX), ru(N_MAX), rd(N_MAX);

// algorithm functions =====
void get_ud(vector<Point>& points, vector<LL>& U, vector<LL>& D) {
    // solve question:
    FenwickTree<LL> ft(M_MAX);
    int idx = 0, last = 0;
    while (idx < N) {
        while (idx < N and G(points[idx], 0) == G(points[last], 0)) {
            ft.add(G(points[idx], 1), 1);
            idx++;
        }
        last = idx;
        while (idx < N and G(points[idx], 0) == G(points[last], 0)) {
            int y = G(points[idx], 1);
            U[idx] = ft.prefix_sum(y - 1);
            D[idx] = ft.prefix_sum(M_MAX + 1) - ft.prefix_sum(y);
            idx++;
        }
        idx = last;
    }
}

void solve(int _turn) {
    // read & generate data:
    scanf("%lld%lld%lld", &N, &G(points[0], 0), &G(points[0], 1));
    scanf("%lld%lld%lld%lld%lld%lld%lld", &A, &B, &C, &D, &E, &F, &M);
    range(i, 1, N) {
        int x, y;
        tie(x, y) = points[i - 1];
        points[i] = {(A * x + B * y + C) % M, (D * x + E * y + F) % M};
    }
    // rep(i, N) echo("point: %lld, %lld\n", G(points[i], 0), G(points[i], 1));
    fill(allof(lu), 0), fill(allof(ld), 0);
    fill(allof(ru), 0), fill(allof(rd), 0);

    sort(frontof(points, N));
    get_ud(points, lu, ld);

    reverse(frontof(points, N));
    get_ud(points, ru, rd);
    reverse(frontof(ru, N));
    reverse(frontof(rd, N));

    LL res = N * (N - 1) * (N - 2) / 6;
    rep(i, N) { res -= lu[i] * rd[i] + ru[i] * ld[i]; }

    printf("Case #%d: %lld\n", _turn, res);
}

// kickstart turn template =====
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
