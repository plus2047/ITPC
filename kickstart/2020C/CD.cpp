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
struct FenwickTree {
    std::vector<NUM> tree;
    const int SIZE;
    // user index range: [0, SIZE]
    // tree index range: [1, SIZE + 1]
    FenwickTree(int size) : SIZE(size + 1), tree(size + 2, 0) {}

    inline void add(int idx, NUM val) {
        assert(idx >= 0 and idx <= SIZE);
        for (int k = idx + 1; k <= SIZE; k += (k & -k)) tree[k] += val;
    }

    inline NUM prefix_sum(int last) {
        if (last < 0) return 0;
        if (last > SIZE) last = SIZE;
        NUM res = 0;
        for (int k = last + 1; k > 0; k -= (k & -k)) res += tree[k];
        return res;
    }
};

void solve(int _turn) {
    int N, Q;
    scanf("%d%d", &N, &Q);
    vector<int> A(N + 1);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }

    FenwickTree<lld> pre(N), step(N);
    for (int i = 1; i <= N; i++) {
        int flag = i % 2 ? -1 : 1;
        pre.add(i, flag * A[i]);
        step.add(i, flag * i * A[i]);
    }

    lld res = 0;
    rep(i, Q) {
        char buff[32];
        scanf("%s", buff);
        if (buff[0] == 'U') {
            int X, V;
            scanf("%d%d", &X, &V);
            int flag = X % 2 ? -1 : 1;
            pre.add(X, -flag * A[X]);
            step.add(X, -flag * X * A[X]);
            A[X] = V;
            pre.add(X, flag * V);
            step.add(X, flag * X * V);
        } else {
            int L, R;
            scanf("%d%d", &L, &R);
            lld X = step.prefix_sum(R) - step.prefix_sum(L - 1);
            lld Y = pre.prefix_sum(R) - pre.prefix_sum(L - 1);
            lld flag = L % 2 ? -1 : 1;
            res += flag * (X - (L - 1) * Y);
            // printf("X: %lld, Y: %lld, res: %lld\n", X, Y, res);
        }
    }

    printf("Case #%d: %lld\n", _turn + 1, res);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
