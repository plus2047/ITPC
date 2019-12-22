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
const int N_MAX = 2048;
LL N, TS, TF;
LL S[N_MAX], F[N_MAX], D[N_MAX];
LL cost[N_MAX][N_MAX];

// cost[i][j] means the earliest time to arrive city i while takes j citis
// before. cost[i][j] = min(
//     arrive_next(i - 1, cost[i - 1][j]),
//     arrive_next(i - 1, cost[i - 1][j - 1] + TS)
// )
// while arrive_next(city, time) is the time arrive next city if begin waiting
// at time in city.

inline LL arrive_next(int city, LL time) {
    // first t = S_i + F_i * n, s.t. t > time.
    // S_i + F_i * n > time
    // F_i * n > time - S_i
    // n > (time - S_i) / F_i
    if (time < S[city]) {
        return S[city] + D[city];
    }
    LL t = time - S[city];
    LL n = t % F[city] == 0 ? t / F[city] : t / F[city] + 1;
    return S[city] + F[city] * n + D[city];
}

inline void dp() {
    cost[0][0] = 0;
    const LL INF = 1E10;
    repr(i, 1, N) { cost[0][i] = INF; }
    repr(i, 1, N) {
        rep(j, N) {
            cost[i][j] = arrive_next(i - 1, cost[i - 1][j]);
            if (j != 0) {
                cost[i][j] = min(cost[i][j],
                                 arrive_next(i - 1, cost[i - 1][j - 1] + TS));
            }
        }
    }
}

void solve(int _turn) {
    scanf("%lld%lld%lld", &N, &TS, &TF);
    rep(i, N - 1) { scanf("%lld%lld%lld", &S[i], &F[i], &D[i]); }

    dp();
    // rep(i, N) { show("dp: ", cost[i], cost[i] + N); }

    int max_score = -1;
    for (; max_score < N - 1; max_score++) {
        if (cost[N - 1][max_score + 1] > TF) break;
    }
    if (max_score != -1) {
        printf("Case #%d: %d\n", _turn, max_score);
    } else {
        printf("Case #%d: IMPOSSIBLE\n", _turn);
    }
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
