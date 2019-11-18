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
const int A_MAX = 1E5 + 8, N_MAX = 1E5 + 8;
struct SegmentTree {
    int size;
    vector<int> _max, _sum;

    SegmentTree(int n) {
        size = 1;
        while (size < n) { size <<= 1; }
        _max.resize(size * 2 - 1);
        _sum.resize(size * 2 - 1);
    }

    inline void set(int n, int val) {
        n = n + size - 1;
        _sum[n] = _max[n] = val;
        while (n) {
            n = (n - 1) / 2;
            int left = n * 2 + 1, right = n * 2 + 2;
            _sum[n] = _sum[left] + _sum[right];
            _max[n] = max(_max[left], _max[right] + _sum[left]);
        }
    }

    int max_prefix_sum() { return _max[0]; }
};

vec2d(int, idx, A_MAX, 0, 0);

void solve(int _turn) {
    int N, S;
    scanf("%d%d", &N, &S);
    vector<int> A(N);
    rep(i, N) { scanf("%d", &A[i]); }

    rep(i, A_MAX) idx[i].clear();
    rep(i, N) { idx[A[i]].push_back(i); }

    SegmentTree tree(N);
    rep(i, A_MAX) rep(j, len(idx[i])) {
        tree.set(idx[i][j], j == S ? -S : (j < S ? 1 : 0));
    }

    int res = tree.max_prefix_sum();
    rep(i, N) {
        tree.set(i, 0);

        vector<int>& a_idx_array = idx[A[i]];
        int a_num = len(a_idx_array);
        int a_idx = find(allof(a_idx_array), i) - a_idx_array.begin();
        int change_idx = a_idx + S;

        if (change_idx < a_num) {
            tree.set(a_idx_array[change_idx], 1);
        }
        if (change_idx + 1 < a_num) {
            tree.set(a_idx_array[change_idx + 1], -S);
        }

        res = max(res, tree.max_prefix_sum());
    }

    printf("Case #%d: %d\n", _turn, res);
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
