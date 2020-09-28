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

inline lld get_ord(lld i, lld j) {
    lld before = (i - 1) * (i - 1);
    return before + j - 1;
}

inline pair<lld, lld> get_pos(lld ord) {
    ord++;
    lld i = 1;
    if (ord > 25) {
        i = 6;
    } else if (ord > 16) {
        i = 5;
    } else if (ord > 9) {
        i = 4;
    } else if (ord > 4) {
        i = 3;
    } else if (ord > 1) {
        i = 2;
    }
    return {i, ord - (i - 1) * (i - 1)};
}

lld S;
map<tuple<lld, lld, lld>, lld> dp;
lld score(lld mask, lld ord_a, lld ord_b) {
    if (ord_a == -1 and ord_b == -1) return 0;
    if (ord_a == -1) return -score(mask, ord_b, -1);

    auto k = make_tuple(mask, ord_a, ord_b);
    if (dp.count(k)) return dp[k];

    lld ia, ja;
    tie(ia, ja) = get_pos(ord_a);
    lld _a[3] = {-1, -1, -1};
    if (ja != 1) {
        _a[0] = get_ord(ia, ja - 1);
    }
    if (ja != 2 * ia - 1) {
        _a[1] = get_ord(ia, ja + 1);
    }
    if (ja % 2) {
        if (ia + 1 <= S) {
            _a[2] = get_ord(ia + 1, ja + 1);
        }
    } else {
        _a[2] = get_ord(ia - 1, ja - 1);
    }

    lld res = INT_MIN;
    for (lld d = 0; d < 3; d++) {
        if (_a[d] == -1) continue;
        lld _mask = 1LL << _a[d];
        if ((mask & _mask) == 0LL) {
            res = max(res, 1 - score(mask | _mask, ord_b, _a[d]));
        }
    }

    return dp[k] = res == INT_MIN ? -score(mask, ord_b, -1) : res;
}

void solve(int _turn) {
    lld RA, PA, RB, PB, C;
    scanf("%lld%lld%lld%lld%lld%lld", &S, &RA, &PA, &RB, &PB, &C);
    lld ord_a = get_ord(RA, PA), ord_b = get_ord(RB, PB);
    lld init_mask = (1LL << ord_a) | (1LL << ord_b);
    rep(i, C) {
        lld x, y;
        scanf("%lld%lld", &x, &y);
        init_mask = init_mask | (1LL << get_ord(x, y));
    }
    dp.clear();
    lld res = score(init_mask, ord_a, ord_b);
    printf("Case #%d: %lld\n", _turn + 1, res);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
