// ===== programing contest template ======
// ===== using a very very old C++ version =====

#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <bitset>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

using namespace std;

// ===== personal contest env =====

typedef long long int lld;
#define len(container) int((container).size())
#define allof(c) (c).begin(), (c).end()
#define frontof(c, k) (c).begin(), (c).begin() + (k)
#define rep(i, N) for (int i = 0; i < int(N); ++i)
#define range(i, left, right) for (int i = int(left); i <= int(right); ++i)
#define irange(i, left, right) for (int i = int(right); i >= int(left); --i)

// #undef __LOCAL__

template <typename ITER>
void show(const char* note, ITER begin, ITER end) {
#ifdef __LOCAL__
    std::cout << note;
    for (; begin != end; begin++) std::cout << *begin << ' ';
    cout << endl;
#endif  // __LOCAL__
}

void echo(const char* fmt, ...) {
#ifdef __LOCAL__
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
#endif  // __LOCAL__
}

// ===== personal contest template =====

// ========== contest code ==========
const int V_MAX = 512, P_MAX = 32;
int v, p, vs[V_MAX];
int cost1[V_MAX][V_MAX];
int cost[V_MAX][P_MAX];
const int INF = 1E7;

int main() {
    scanf("%d%d", &v, &p);
    rep(i, v) scanf("%d", &vs[i]);

    rep(i, v) cost1[i][i] = 0;
    rep(i, v - 1) cost1[i][i + 1] = vs[i + 1] - vs[i];
    range(x, 3, v) for (int left = 0, right = x - 1; right < v;
                        left++, right++) {
        cost1[left][right] = cost1[left + 1][right - 1] + vs[right] - vs[left];
    }

    rep(i, v) range(c, 0, p) cost[i][c] = INF;
    rep(i, v) cost[i][1] = cost1[0][i];
    range(i, 1, v - 1) range(c, 2, p) {
        int _cost = INF;
        range(left, 1, i) {
            _cost = min(_cost, cost[left - 1][c - 1] + cost1[left][i]);
        }
        cost[i][c] = _cost;
    }

    printf("%d\n", cost[v - 1][p]);
}
