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

void solve(int _turn) {
    int N, K;
    scanf("%d%d", &N, &K);
    vector<pair<lld, lld> > intervals(N);
    rep(i, N) { scanf("%lld%lld", &intervals[i].first, &intervals[i].second); }
    sort(allof(intervals));

    int res = 0;
    lld curr_last = -1;  // included
    rep(i, N) {
        lld start, last;
        tie(start, last) = intervals[i];
        if (start >= curr_last) {
            curr_last = start + K;
            res++;
        }
        if (last > curr_last) {
            lld delta = last - curr_last;
            delta = delta / K + (delta % K ? 1 : 0);
            res += delta;
            curr_last += K * delta;
        }
    }

    printf("Case #%d: %d\n", _turn + 1, res);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
