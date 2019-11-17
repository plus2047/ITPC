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
const int MAX_N = 1E5 + 8, MAX_R = 5E4 + 8;
int N, R, C, SR, SC;
char D[MAX_N];

typedef pair<int, int> Pos;

set<Pos> arrived;
map<Pos, Pos> jump[4];

void solve(int _turn) {
    scanf("%d%d%d%d%d", &N, &R, &C, &SR, &SC);
    scanf("%s", D);

    arrived.clear();
    rep(i, 4) { jump[i].clear(); }

    const int Delta[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    rep(i, N) {
        int d = D[i] == 'N' ? 0 : (D[i] == 'S' ? 1 : (D[i] == 'W' ? 2 : 3));
        arrived.insert({SR, SC});
        int _SR = SR, _SC = SC;
        while (arrived.count({SR, SC})) {
            if (jump[d].count({SR, SC})) {
                tie(SR, SC) = jump[d][{SR, SC}];
            } else {
                SC += Delta[d][0];
                SR += Delta[d][1];
            }
        }
        jump[d][{_SR, _SC}] = {SR + Delta[d][1], SC + Delta[d][0]};
    }

    printf("Case #%d: %d %d\n", _turn, SR, SC);
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
