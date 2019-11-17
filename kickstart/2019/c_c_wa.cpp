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
const LL N_MAX = 1024, A_MAX = 1024;
int N, K, P[N_MAX], A[N_MAX];

struct Pos {
    int count, cost, color;
    Pos(int count, int cost, int color)
        : count(count), cost(cost), color(color) {}
};
bool operator<(const Pos& a, const Pos& b) {
    return a.cost * b.count < b.cost * a.count;
}

vector<Pos> pos;
vector<vector<int>> colors = vector<vector<int>>(A_MAX);
vector<int> current = vector<int>(A_MAX);

void solve(int _turn) {
    scanf("%d%d", &N, &K);
    rep(i, N) { scanf("%d", P + i); }
    rep(i, N) { scanf("%d", A + i); }

    rep(i, A_MAX) { colors[i].clear(); }
    rep(i, N) { colors[A[i]].push_back(P[i]); }
    rep(i, A_MAX) { sort(allof(colors[A[i]])); }

    pos.clear();
    rep(i, A_MAX) {
        rep(j, len(colors[i])) {
            pos.push_back(Pos(j + 1, colors[i][j] * 2, i));
        }
    }

    int minCost = INT_MAX;
    rep(i, A_MAX) {
        if (colors[i].empty()) {
            continue;
        }
        for (Pos& p : pos) {
            if (p.color == i) {
                p.cost /= 2;
            }
        }
        sort(allof(pos));
        fill(allof(current), -1);

        int cost = 0, taken = 0;
        for (int p = 0; p < N and taken < K; p++) {
            int c = current[pos[p].color];
            if (c != -1 and pos[c].count > pos[p].count) {
                continue;
            }
            int _taken = pos[p].count - (c == -1 ? 0 : pos[c].count);
            if (_taken + taken > K) {
                continue;
            }
            taken += _taken;
            cost += pos[p].cost - (c == -1 ? 0 : pos[c].cost);
            current[pos[p].color] = p;
        }
        asmin(minCost, cost);

        for (Pos& p : pos) {
            if (p.color == i) {
                p.cost *= 2;
            }
        }
    }

    printf("Case #%d: %d\n", _turn, minCost);
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
