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
const int N_MAX = 1024, A_MAX = 1024;
int N, K, P[N_MAX], A[N_MAX];
vec2d(int, pos, A_MAX, N_MAX, 0);
vec2d(int, dp0, A_MAX, N_MAX, 0);
vec2d(int, dp1, A_MAX, N_MAX, 0);

void solve(int _turn) {
    scanf("%d%d", &N, &K);
    rep(i, N) scanf("%d", &P[i]);
    rep(i, N) scanf("%d", &A[i]);

    rep(i, A_MAX) pos[i].clear();
    rep(i, N) pos[A[i]].push_back(P[i]);

    int a_num = 0;
    rep(i, A_MAX) {
        if (pos[i].size()) {
            sort(allof(pos[i]));
            swap(pos[i], pos[a_num++]);
        }
    }

    const int INF = INT_MAX / 2;
    rep(i, a_num) {
        if (i == 0) {
            rep(n, len(pos[0])) {
                dp0[i][n + 1] = pos[i][n] * 2;
                dp1[i][n + 1] = pos[i][n];
            }
            repr(n, len(pos[0]), K + 1) { dp0[i][n + 1] = dp1[i][n + 1] = INF; }
        } else {
            rep(j, K + 1) {
                dp0[i][j] = dp0[i - 1][j];
                dp1[i][j] = dp1[i - 1][j];
                for (int n = 0; n < len(pos[i]) and n < j; n++) {
                    asmin(dp0[i][j], dp0[i - 1][j - n - 1] + pos[i][n] * 2);
                    asmin(dp1[i][j], dp1[i - 1][j - n - 1] + pos[i][n] * 2);
                    asmin(dp1[i][j], dp0[i - 1][j - n - 1] + pos[i][n]);
                }
            }
        }
    }

    printf("Case #%d: %d\n", _turn, dp1[a_num - 1][K]);
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
