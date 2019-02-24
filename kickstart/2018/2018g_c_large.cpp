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
// ===== if using persional toolbox & enable debug log =====
// #define __TOOLBOX__
// ===== include persional toolbox =====
#ifdef __TOOLBOX__
#include "lib/graph.h"
#include "lib/hash.h"
#include "lib/show.h"
#include "lib/string.h"
using namespace contest;
#endif  // __TOOLBOX__
// for contest, it's okey to use namespace. =====
using namespace std;

// =============================================
// ============= CONTEST ENV BEGIN =============
// =============================================
typedef long long int LL;
typedef long long unsigned LLU;
#define G(_tuple, num) (get<num>(_tuple))
// =============================================
// =============== CONTEST BEGIN ===============
// =============================================

int x, y, v;
int T, N, M, E, SR, SC, TR, TC;
const int BLOCK = -100000;
const int N_MAX = 128, M_MAX = 128, TRAP_MAX = 16;
const unsigned MASK_MAX = 1 << TRAP_MAX;

int graph[N_MAX][M_MAX];
int trap_index[N_MAX][M_MAX];
bool seen[N_MAX][M_MAX];

typedef tuple<int, int> Point;
Point traps[TRAP_MAX];
unsigned n_traps, n_mask;

LL energy_left[MASK_MAX];
unsigned reachable_traps[MASK_MAX];
bool reachable_exit[MASK_MAX];

const LL MAX_ENERGY_UNSEEN = -2;
LL max_energy_dp[MASK_MAX];
void max_energy(unsigned mask) {
    if (max_energy_dp[mask] != MAX_ENERGY_UNSEEN) return;
    LL ret = -1;

    if (reachable_exit[mask]) ret = max(ret, energy_left[mask]);

    for (unsigned trap_i = 0; trap_i < n_traps; trap_i++) {
        unsigned mask_i = 1 << trap_i;
        tie(x, y) = traps[trap_i];
        if ((mask_i & reachable_traps[mask]) and
            graph[x][y] + energy_left[mask] >= 0) {
            unsigned next_mask = mask_i | mask;
            max_energy(next_mask);
            ret = max(ret, max_energy_dp[next_mask]);
        };
    }

    max_energy_dp[mask] = ret;
}

int main() {
#ifdef __LOCAL__  // define in build command.
    freopen("_kickstart.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        scanf("%d%d%d%d%d%d%d", &N, &M, &E, &SR, &SC, &TR, &TC);
        SR--, SC--, TR--, TC--;
        n_traps = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                scanf("%d", &v);
                graph[i][j] = v;
                if (v < 0 and v != BLOCK) {
                    trap_index[i][j] = n_traps;
                    traps[n_traps++] = make_tuple(i, j);
                }
            }
        }

        n_mask = 1 << n_traps;
        for (unsigned mask = 0; mask < n_mask; mask++) {
            for (int i = 0; i < N; i++) fill(seen[i], seen[i] + M, false);
            unsigned r_traps = 0;
            LL energy = E + graph[SR][SC];

            queue<Point> Q;
            Q.push({SR, SC});

            while (!Q.empty()) {
                tie(x, y) = Q.front();
                Q.pop();

                if (x < 0 or y < 0 or x >= N or y >= M or seen[x][y] or
                    graph[x][y] == BLOCK)
                    continue;
                seen[x][y] = true;

                bool taken = false;
                if (graph[x][y] >= 0) {
                    taken = true;
                } else {
                    unsigned this_mask = 1 << trap_index[x][y];
                    if (mask & this_mask)
                        taken = true;
                    else
                        r_traps |= this_mask;
                }
                if (taken) {
                    energy += graph[x][y];
                    Q.push({x + 1, y});
                    Q.push({x - 1, y});
                    Q.push({x, y + 1});
                    Q.push({x, y - 1});
                }
            }
            energy_left[mask] = energy;
            reachable_exit[mask] = seen[TR][TC];
            reachable_traps[mask] = r_traps;
        }

        fill(max_energy_dp, max_energy_dp + n_mask, MAX_ENERGY_UNSEEN);
        max_energy(0);

        // for (unsigned i = 0; i < n_mask; i++) {
        //     printf("mask: 0x%x, E: %lld, R: 0x%x, Exit: %d, dp: %lld\n", i,
        //            energy_left[i], reachable_traps[i], reachable_exit[i],
        //            max_energy_dp[i]);
        // }

        printf("Case #%d: %lld\n", t, max_energy_dp[0]);
    }
}
