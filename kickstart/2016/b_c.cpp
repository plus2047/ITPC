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
    lld N, L1, R1, A, B, C1, C2, M;
    scanf("%lld%lld%lld%lld%lld%lld%lld%lld", &N, &L1, &R1, &A, &B, &C1, &C2,
          &M);

    typedef tuple<lld, int, int> S;  // <pos, action, index>
    vector<S> ss;
    lld x = L1, y = R1;
    for (int i = 0; i < N; i++) {
        lld l = min(x, y), r = max(x, y);
        ss.push_back({l, +1, i + 1});
        ss.push_back({r + 1, -1, i + 1});
        tie(x, y) =
            make_pair((A * x + B * y + C1) % M, (A * y + B * x + C2) % M);
    }

    sort(allof(ss));
    vector<int> size(N + 1);
    set<int> open;
    lld last = -1, total = 0;

    for (S st : ss) {
        lld pos;
        int act, idx;
        tie(pos, act, idx) = st;
        if (len(open) == 1) {
            size[*open.begin()] += pos - last;
        }
        if (len(open) != 0) {
            total += pos - last;
        }
        last = pos;
        if (act == 1) {
            open.insert(idx);
        } else {
            open.erase(idx);
        }
    }

    printf("Case #%d: %lld\n", _turn + 1, total - *max_element(allof(size)));
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
