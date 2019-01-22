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
#include "lib/hash.h"
#include "lib/show.h"
#include "lib/string.h"
using namespace contest;
#endif  // __TOOLBOX__

// for contest, it's okey to use namespace. =====
using namespace std;

// ============= CONTEST ENV BEGIN =============

typedef long long int LL;
typedef long long unsigned LLU;
#define G(_tuple, num) (get<num>(_tuple))
#define rep(i, begin, end) for (auto i = begin; i < end; i++)
#define aord(a) ((a) - 'a')
#define achr(a) ((a) + 'a')
#define fillc(c, v) (fill((c).begin(), (c).end(), v))

// =============== CONTEST BEGIN ===============

typedef tuple<LL, LL> Point;
vector<Point> points;

bool valid(int i, int j, int k) {
    LL x[3][2], idx[3];
    tie(idx[0], idx[1], idx[2]) = tie(i, j, k);
    rep(n, 0, 3) tie(x[n][0], x[n][1]) = points[idx[n]];

    LL min_[2], max_[2];
    rep(n, 0, 2){
        min_[n] = min({x[0][n], x[1][n], x[2][n]});
        max_[n] = max({x[0][n], x[1][n], x[2][n]});
    }

    // if 3 points in one line
    if (min_[0] == max_[0] or min_[1] == max_[1]) return true;

    // if any points not in any line.
    rep(n, 0, 3) {
        bool on_line = false;
        rep(m, 0, 2) {
            if (x[n][m] == min_[m] or x[n][m] == max_[m]) on_line = true;
        }
        if(!on_line) return false;
    }

    LL diff_[2];
    rep(n, 0, 2) diff_[n] = max_[n] - min_[n];

    if (diff_[0] == diff_[1]) {
        return true;
    } else {
        // which axis the long edge parallel with:
        int l_idx = diff_[0] > diff_[1] ? 0 : 1;
        int w_idx = 1 - l_idx;

        bool min_ext = true, max_ext = true;
        rep(m, 0, 3) {
            if (x[m][l_idx] > min_[l_idx] and x[m][l_idx] < max_[l_idx]) {
                if (x[m][w_idx] == min_[w_idx]) min_ext = false;
                if (x[m][w_idx] == max_[w_idx]) max_ext = false;
            }
        }
        return min_ext or max_ext;
    }
}

int main() {
#ifdef __LOCAL__  // define in build command.
    freopen("_kickstart.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        LL N, V1, H1, A, B, C, D, E, F, M;
        scanf("%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld", &N, &V1, &H1, &A, &B,
              &C, &D, &E, &F, &M);
        points.resize(N);
        points[0] = {V1, H1};
        for (int i = 1; i < N; i++) {
            points[i] = {
                (A * G(points[i - 1], 0) + B * G(points[i - 1], 1) + C) % M,
                (D * G(points[i - 1], 0) + E * G(points[i - 1], 1) + F) % M};
            // printf("point: %lld %lld\n", G(points[i], 0), G(points[i], 1));
        }
        // sort(points.begin(), points.end());

        LL cnt = 0;
        rep(i, 0, N) rep(j, i + 1, N) rep(k, j + 1, N) {
            if (valid(i, j, k)) {
                // echo("%d %d %d\n", i, j, k);
                cnt++;
            }
        }
        echo("Case #%d: %lld\n", t, cnt);
    }
}
