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
int N, M, K;
const int N_MAX = 128;
char G[N_MAX][N_MAX];
int dp[N_MAX][N_MAX][N_MAX];
int depth[N_MAX][N_MAX];

void solve(int _turn) {
    scanf("%d%d%d", &N, &M, &K);
    rep(i, N) { scanf("%s", G[i]); }

    rep(i, M) { depth[N][i] = 0; }
    repi(i, N) {
        rep(j, M) {
            if (G[i][j] == '.') {
                depth[i][j] = 0;
            } else if (j == 0 or j == M - 1 or depth[i + 1][j] == 0) {
                depth[i][j] = 1;
            } else {
                depth[i][j] = min(depth[i + 1][j - 1], depth[i + 1][j + 1]) + 1;
            }
        }
    }
    // rep(i, N) {
    //     rep(j, M) { printf("%d ", depth[i][j]); }
    //     printf("\n");
    // }

    const int INVALID = -1E6;
    rep(i, N + 1) rep(j, M) { dp[i][j][0] = 0; }
    repr(k, 1, K + 1) rep(j, M) { dp[N][j][j] = INVALID; }

    repr(k, 1, K + 1) rep(i, N + 1) rep(j, M) {
        int& r = dp[i][j][k];
        r = INVALID;
        repr(d, 1, depth[i][j] + 1) {
            int thisCnt = d * d;
            for (int _j = j - d + 1; _j <= j + d - 1; _j++) {
                int cnt = thisCnt + dp[i + d][_j][k - 1];
                asmax(r, cnt);
            }
        }
    }

    int res = 0;
    rep(i, N) rep(j, M) { asmax(res, dp[i][j][K]); }

    printf("Case #%d: %d\n", _turn, res > 0 ? res : 0);
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
