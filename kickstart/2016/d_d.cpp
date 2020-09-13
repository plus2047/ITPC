// ===== programing contest template ======

#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <bitset>
#include <functional>
#include <random>
#include <unordered_map>
#include <unordered_set>
#endif  // C++11

using namespace std;

typedef long long int lld;
#define frontof(c, k) (c).begin(), (c).begin() + (k)
#define allof(c) (c).begin(), (c).end()
#define len(container) int((container).size())
#define asmin(var, val) var = min(var, val)
#define asmax(var, val) var = max(var, val)
#define rep(i, N) for (int i = 0; i < int(N); ++i)
#define inv(i, N) for (int i = int(N) - 1; i >= 0; --i)

// ========== contest code ==========
template <typename NUM>
struct SegmentTree {
    // a + b or max(a, b) or min(a, b)
    inline NUM func(NUM a, NUM b) { return min(a, b); }
    // VOID == 0 for sum, NUM_MAX for min, NUM_MIN for max
    const static NUM VOID = INT64_MAX;

    int size;
    std::vector<NUM> tree;  // 1-indexed full tree
    inline NUM get(int idx) { return tree[idx + size]; }
    SegmentTree(int size) : size(size), tree(size * 2, VOID) {}
    SegmentTree(std::vector<NUM>& data) { init(data); }

    void init(std::vector<NUM>& data) {
        size = int(data.size());
        tree.resize(size * 2);
        std::copy(data.begin(), data.end(), tree.begin() + size);
        for (int i = size - 1; i > 0; i--) {
            tree[i] = func(tree[i * 2], tree[i * 2 + 1]);
        }
    }

    void update(int idx, NUM val) {
        idx += size;
        tree[idx] = val;
        while (idx != 0) {
            idx /= 2;
            tree[idx] = func(tree[2 * idx], tree[2 * idx + 1]);
        }
    }

    NUM query(int left, int right) {
        left += size, right += size;
        NUM res = VOID;
        while (left <= right) {
            if (left % 2 == 1) res = func(res, tree[left++]);
            if (right % 2 == 0) res = func(res, tree[right--]);
            left /= 2, right /= 2;
        }
        return res;
    }
};

void solve(int _turn) {
    lld N, M, L;
    scanf("%lld%lld%lld", &N, &M, &L);

    vector<lld> A(N), B(N), P(N);
    rep(i, N) { scanf("%lld%lld%lld", &A[i], &B[i], &P[i]); }

    vector<lld> _t(L + 1, M + 1);
    SegmentTree<lld> dp(_t);
    dp.update(0, 0);

    rep(i, N) {
        for (int j = L; j > 0; j--) {
            int left = j - B[i], right = j - A[i];
            if (right >= 0) {
                int _l = max(0, left), _r = min(int(L), right);
                dp.update(j, min(dp.get(j), P[i] + dp.query(_l, _r)));
            }
        }
    }

    printf("Case #%d:", _turn + 1);
    if (dp.get(L) <= M) {
        printf(" %lld", dp.get(L));
    } else {
        printf(" IMPOSSIBLE");
    }
    printf("\n");
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
