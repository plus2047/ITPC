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
int N, X[N_MAX], Y[N_MAX], Z[N_MAX], R[N_MAX];
int _X[N_MAX], _Y[N_MAX], _Z[N_MAX];

inline int min1(int A[]) {
    int res = INT_MAX;
    rep(i, N) { res = min(res, A[i] - R[i]); }
    return res;
}

inline bool _check(int r) {
    int min1_x = min1(_X), min1_y = min1(_Y), min1_z = min1(_Z);
    int max1_x = min1_x + r, max1_y = min1_y + r, max1_z = min1_z + r;

    int min2_x = INT_MAX, min2_y = INT_MAX, min2_z = INT_MAX;
    int max2_x = INT_MIN, max2_y = INT_MIN, max2_z = INT_MIN;

    rep(i, N) {
        if (_X[i] + R[i] <= max1_x and _Y[i] + R[i] <= max1_y and
            _Z[i] + R[i] <= max1_z) {
            continue;
        }

        asmin(min2_x, _X[i] - R[i]);
        asmin(min2_y, _Y[i] - R[i]);
        asmin(min2_z, _Z[i] - R[i]);

        asmax(max2_x, _X[i] + R[i]);
        asmax(max2_y, _Y[i] + R[i]);
        asmax(max2_z, _Z[i] + R[i]);
    }

    return min2_x == INT_MAX or (max2_x - min2_x <= r and
                                 max2_y - min2_y <= r and max2_z - min2_z <= r);
}

inline bool check(int r) {
    rep(mask, 4) {
        rep(i, N) {
            _X[i] = X[i] * (mask & 1 ? -1 : 1);
            _Y[i] = Y[i] * (mask & 2 ? -1 : 1);
            _Z[i] = Z[i];
        }
        if (_check(r)) {
            return true;
        }
    }
    return false;
}

void solve(int _turn) {
    scanf("%d", &N);
    rep(i, N) { scanf("%d%d%d%d", &X[i], &Y[i], &Z[i], &R[i]); }

    int left = 0, right = 1E9;
    while (left < right) {
        int mid = (left + right) / 2;
        bool valid = check(mid);
        if (valid) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    printf("Case #%d: %d\n", _turn, left);
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
