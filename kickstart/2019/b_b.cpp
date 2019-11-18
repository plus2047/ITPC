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
int N;
const int N_MAX = 128, E_MAX = 1E5 + 8;
struct Stone {
    int S, E, L;
};
vector<Stone> stones;

void solve(int _turn) {
    scanf("%d", &N);
    stones.resize(N);
    rep(i, N) {
        Stone& s = stones[i];
        scanf("%d%d%d", &s.S, &s.E, &s.L);
    }

    sort(allof(stones),
         [](const Stone& a, const Stone& b) { return a.L * b.S > b.L * a.S; });

    int total_S = 0;
    rep(i, N) { total_S += stones[i].S; }

    int time_max = total_S + 1;
    vec2d(int, dp, N + 1, time_max, 0);

    rep(index, N) {
        Stone& s = stones[index];

        rep(time, time_max) {
            dp[index + 1][time] = dp[index][time];
            int this_gain = s.E - (time - s.S) * s.L;
            if (time >= s.S and this_gain > 0) {
                int t = dp[index][time - s.S] + this_gain;
                asmax(dp[index + 1][time], t);
            }
        }
    }

    int gain_max = 0;
    rep(i, total_S + 1) { asmax(gain_max, dp[N][i]); }

    printf("Case #%d: %d\n", _turn, gain_max);
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
