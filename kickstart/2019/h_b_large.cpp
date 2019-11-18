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
const int N_MAX = 128;
char grid[N_MAX][N_MAX], _grid[N_MAX][N_MAX];

inline bool valid(int x, int y) {
    return x >= 0 and y >= 0 and x < N and y < N;
}

inline void flip(char& c) { c = c == '.' ? '#' : '.'; }

inline void flip(char G[N_MAX][N_MAX], int i, int j, int di, int dj) {
    for (int x = i, y = j; valid(x, y); x += di, y += dj) {
        flip(G[x][y]);
    }
    for (int x = i - di, y = j - dj; valid(x, y); x -= di, y -= dj) {
        flip(G[x][y]);
    }
}

void copy(char source[N_MAX][N_MAX], char target[N_MAX][N_MAX]) {
    rep(i, N) rep(j, N) target[i][j] = source[i][j];
}

int count() {
    copy(grid, _grid);
    int cnt = 0;
    rep(i, N) {
        if (_grid[i][i] == '.') {
            cnt++;
            flip(_grid, i, i, 1, -1);
        }
    }
    rep(i, N - 1) {
        if (_grid[i][i + 1] == '.') {
            cnt++;
            flip(_grid, i, i + 1, 1, -1);
        }
    }
    vector<char> black(2 * N, false);
    vector<char> white(2 * N, false);

    rep(i, N) rep(j, N) {
        int id = i - j + N;
        if (_grid[i][j] == '.') {
            white[id] = true;
        } else {
            black[id] = true;
        }
    }

    rep(i, 2 * N) {
        if (white[i] and black[i]) {
            return INT_MAX / 2;
        } else if (white[i]) {
            cnt++;
        }
    }

    return cnt;
}

void solve(int _turn) {
    scanf("%d", &N);
    rep(i, N) scanf("%s", grid[i]);

    int minCnt = INT_MAX;

    minCnt = min(minCnt, count());

    flip(grid, 0, 1, 1, 1);
    minCnt = min(minCnt, count() + 1);

    flip(grid, 0, 0, 1, 1);
    minCnt = min(minCnt, count() + 2);

    flip(grid, 0, 1, 1, 1);
    minCnt = min(minCnt, count() + 1);

    printf("Case #%d: %d\n", _turn, minCnt);
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
