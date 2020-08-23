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
    int N;
    scanf("%d", &N);
    vector<lld> E(N), R(N);
    rep(i, N) scanf("%lld%lld", &E[i], &R[i]);

    lld total = accumulate(allof(E), lld(0));
    int y = 0;
    lld z = total;

    typedef pair<lld, int> S;
    set<S, greater<S> > pre;
    lld _total = total;
    lld _pre_sum = 0;
    rep(i, N) {
        pre.insert({E[i] + R[i], i});
        _pre_sum += E[i];
        while (pre.size() and pre.begin()->first > _total) {
            lld ei = E[pre.begin()->second];
            _pre_sum -= ei;
            _total -= ei;
            pre.erase(pre.begin());
        }
        lld _z = _total + _pre_sum;
        if (_z >= z) {
            int rm = (i + 1) - len(pre);
            y = _z == z ? min(y, rm) : rm;
            z = _z;
        }
    }

    printf("Case #%d:", _turn + 1);
    if (len(pre) == 0) {
        printf(" %d %lld\n", y, z);
    } else {
        printf(" %d INDEFINITELY\n", N - len(pre));
    }
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
