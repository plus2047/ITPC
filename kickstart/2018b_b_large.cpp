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
#include "lib/bit_algorithm.h"
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
int N, K;
LD P;
const int N_MAX = 100, K_MAX = 100;
const int PRE_L = 15;
const int PRE_N = 1 << (PRE_L + 1);

LD cnt[N_MAX + 1][PRE_N];

typedef tuple<int, int> Con;  // Constraint
const int _left = 0, _num = 1;

vector<vector<Con>> cons(N_MAX + 1);

void init_turn() {
    rep(i, N_MAX + 1) {
        fill(cnt[i], cnt[i] + PRE_N, -1);
        cons[i].clear();
    }
}

LD get_cnt(int n, int pre) {
    if (cnt[n][pre] != -1) return cnt[n][pre];
    for (Con c : cons[n]) {
        int left, num1;
        tie(left, num1) = c;
        int clen = n - left;
        if (popcount(pre >> (PRE_L - clen)) != num1) {
            return cnt[n][pre] = 0;
        }
    }
    if (n == N) {
        return cnt[n][pre] = 1;
    } else {
        int _pre0 = pre >> 1, _pre1 = (pre >> 1) + (1 << PRE_L);
        return cnt[n][pre] = get_cnt(n + 1, _pre0) + get_cnt(n + 1, _pre1);
    }
}

void solve(int _turn) {
    scanf("%d%d%Lf", &N, &K, &P);
    init_turn();
    rep(i, K) {
        int A, B, C;
        scanf("%d%d%d", &A, &B, &C);
        cons[B].push_back({A, C});
    }

    string res;
    int pre = 0;
    rep(i, N) {
        LD cnti = get_cnt(i + 1, pre >> 1);
        if (cnti >= P) {
            res += '0';
            pre >>= 1;
        } else {
            res += '1';
            pre = (pre >> 1) + (1 << PRE_L);
            P -= cnti;
        }
    }
    echo("Case #%d: %s\n", _turn, res.c_str());
}

int main() {
#ifdef __LOCAL__  // define in build command.
    freopen("_kickstart.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
