// ===== include all posible stl headers =====
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
#include "lib/graph.h"

using namespace std;
using namespace contest;


// ===== LEETCODE ENV BEGIN =====
// ===== tools function & macro =====
typedef long long int LL;
typedef long long unsigned LLU;
#define G(_tuple, num) (get<num>(_tuple))
#define REP(i, n) for (LL i = 0, i##_len = (n); i < i##_len; ++i)
#define EACH(i, c)                                                   \
    for (__typeof((c).begin()) i = (c).begin(), i##_end = (c).end(); \
         i != i##_end; ++i)
template <class T>
inline void amin(T &min_val, const T &update) {
    if (update < min_val) min_val = update;
}
template <class T>
inline void amax(T &max_val, const T &update) {
    if (max_val < update) max_val = update;
}
// ===== CONTEST BEGIN =====
// =========================

int main() {
#ifdef __LOCAL__  // define in build command.
    freopen("_kickstart.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
    LL T;
    scanf("%lld", &T);
    for (LL t = 1; t <= T; t++) {
        LL N, M, E, SR, SC, TR, TC;
        scanf("%lld%lld%lld%lld%lld%lld%lld", &N, &M, &E, &SR, &SC, &TR, &TC);
        vector<vector<LL>> graph(N, vector<LL>(M));
        REP(i, N) REP(j, M) { scanf("%lld", &graph[i][j]); }

#define ID(i, j) ((i)*M + (j))
#define INF (-100000)

        ShortestPath<LL, LL> sp(N * M);
        int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        REP(i, N) REP(j, M) REP(d, 4) {
            LL _i = i + DIR[d][0], _j = j + DIR[d][1];
            if (_i >= 0 and _i < N and _j >= 0 and _j < M and
                graph[_i][_j] != INF) {
                sp.add_edge(ID(i, j), ID(_i, _j), -graph[_i][_j]);
            }
        }

        LL from = ID(SR - 1, SC - 1), to = ID(TR - 1, TC - 1);
        sp.bellmen_ford(from);

        LL w = sp.path_weight[to];
        printf("Case #%lld: %lld\n", t, w <= E ? E - w : -1);
    }
}
