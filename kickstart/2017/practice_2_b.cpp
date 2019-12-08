// ===== programing contest template ======
// ===== using standrod: C++ 11 =====

#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>

#include <array>
#include <bitset>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// ===== personal contest env =====

typedef long long int LL;
#define G(_tuple, num) (get<num>(_tuple))
#define len(container) int((container).size())
#define allof(c) (c).begin(), (c).end()
#define frontof(c, k) (c).begin(), (c).begin() + (k)
#define rep(i, N) for (int i = 0; i < int(N); i++)
#define repr(i, begin, end) for (int i = int(begin); i < int(end); i++)
#define repi(i, N) for (int i = int(N) - 1; i >= 0; i--)
#define asmax(m, update) \
    if (m < update) m = update;
#define asmin(m, update) \
    if (m > update) m = update;
#define vec2d(type, name, m, n, v) \
    vector<vector<type>> name = vector<vector<type>>(m, vector<type>(n, v))

template <int group = 20, typename ITER>
void show(const char* note, ITER begin, ITER end) {
#ifdef __LOCAL__
    cout << note;
    for (int i = 1; begin != end; i++) {
        std::cout << *(begin++) << ' ';
        if (i % group == 0 or begin == end) std::cout << std::endl;
    }
#endif  // __LOCAL__
}

#ifdef __LOCAL__
std::clock_t _t0 = 0;
void timer_begin() { _t0 = clock(); }
void timer_end(const char* note) {
    double delta = double(clock() - _t0) / CLOCKS_PER_SEC;
    printf("%s cost: %lf sec.\n", note, delta);
}
#else
#define timer_begin() (void(0))
#define timer_end(note) (void(0))
#endif  // __LOCAL__

// ===== personal contest template =====

// ========== contest code ==========
const int N_MAX = 3000 + 8;
int R, C, K;
int G[N_MAX][N_MAX];
int dp[N_MAX][N_MAX];

void solve(int _turn) {
    scanf("%d%d%d", &R, &C, &K);
    rep(i, R) rep(j, C) { G[i][j] = 0; }
    rep(i, K) {
        int x, y;
        scanf("%d%d", &x, &y);
        G[x][y] = 1;
    }
    rep(i, R) { dp[i][0] = G[i][0] == 1 ? 0 : 1; }
    rep(j, C) { dp[0][j] = G[0][j] == 1 ? 0 : 1; }
    repr(i, 1, R) repr(j, 1, C) {
        if (G[i][j] == 1) {
            dp[i][j] = 0;
        } else {
            int L = min(dp[i - 1][j], dp[i][j - 1]);
            dp[i][j] = L + (G[i - L][j - L] == 1 ? 0 : 1);
        }
    }
    LL total = 0;
    rep(i, R) rep(j, C) { total += dp[i][j]; }
    printf("Case #%d: %lld\n", _turn, total);
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
