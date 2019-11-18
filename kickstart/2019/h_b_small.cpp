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
inline int id1(int x, int y) {  // [0, 2 * N - 2]
    return x + y;
}
inline int id2(int x, int y) {  // [2 * N + 1, 4 * N - 1]
    return x - y + 3 * N;
}
const int N_MAX = 128;
char grid[N_MAX][N_MAX];

inline int pop_count(int x) {
    int res = 0;
    rep(i, 31) {
        if (x & (1 << i)) res++;
    }
    return res;
}
inline void change_char(char& c) { c = '#' == c ? '.' : '#'; }
inline void change(int mask) {
    rep(i, N) rep(j, N) {
        if (((1 << (i + j))) & mask) change_char(grid[i][j]);
    }
}

inline int count() {
    int cnt = 0;
    for (int delta = -(N - 1); delta <= (N - 1); delta++) {
        bool a = false, b = false;
        rep(i, N) {
            int j = i - delta;
            if (j < 0 or j >= N) continue;

            if (grid[i][j] == '.') {
                a = true;
            } else {
                b = true;
            }
        }
        if (a != b) {
            if (a == true) {
                cnt++;
            }
        } else {
            return N * 4;
        }
    }
    return cnt;
}

void solve(int _turn) {
    scanf("%d", &N);
    rep(i, N) scanf("%s", grid[i]);

    int max_mask = 1 << (2 * N - 1);
    int min_move = INT_MAX;

    rep(m, max_mask) {
        int move = pop_count(m);
        change(m);

        move += count();
        asmin(min_move, move);

        change(m);
    }
    printf("Case #%d: %d\n", _turn, min_move);
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
