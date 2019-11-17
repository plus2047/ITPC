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
const int MAXRC = 308;
int R, C, K, maxSize;
vec2d(int, G, MAXRC, MAXRC, 0);
vec2d(int, depth, MAXRC, MAXRC, 0);

void getLeftDepth(int row) {
    static multiset<int> window;
    window.clear();
    rep(i, C) {
        window.insert(G[row][i]);
        while (*window.rbegin() - *window.begin() > K) {
            int key = G[row][i + 1 - len(window)];
            window.erase(window.find(key));
        }
        depth[row][i] = len(window);
    }
}

inline void maxRectangle(int col) {
    static vector<int> window;
    window.clear();
    depth[R][col] = 0;
    rep(i, R + 1) {
        while (window.size() and depth[window.back()][col] >= depth[i][col]) {
            int height = depth[window.back()][col];
            window.pop_back();
            int size = height * (i - (window.size() ? window.back() : -1) - 1);
            asmax(maxSize, size);
        }
        window.push_back(i);
    }
}

void solve(int _turn) {
    scanf("%d%d%d", &R, &C, &K);
    rep(i, R) {
        G[i].resize(C);
        rep(j, C) { scanf("%d", &G[i][j]); }
    }
    maxSize = 1;

    rep(i, R) getLeftDepth(i);
    rep(i, C) maxRectangle(i);

    printf("Case #%d: %d\n", _turn, maxSize);
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
