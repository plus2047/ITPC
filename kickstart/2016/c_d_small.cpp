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
const int V_MAX = 1E4 + 8;
vector<pair<int, int> > ps;
vector<pair<int, int> > Aidx, Didx;
vector<vector<int> > dp = vector<vector<int> >(V_MAX, vector<int>(V_MAX, -1));

bool play(int A, int D) {
    if (dp[A][D] != -1) return dp[A][D];

    bool succ = false;
    auto ai = upper_bound(allof(Aidx), make_pair(A, INT_MAX));
    while (not succ and ai != Aidx.end()) {
        auto p = ps[(ai++)->second];
        succ = succ or not play(max(A, p.first), max(D, p.second));
    }
    if (succ) return dp[A][D] = succ;

    auto di = upper_bound(allof(Didx), make_pair(D, INT_MAX));
    while (not succ and di != Didx.end()) {
        auto p = ps[(di++)->second];
        succ = succ or not play(max(A, p.first), max(D, p.second));
    }
    
    return dp[A][D] = succ;
}

void solve(int _turn) {
    int N;
    scanf("%d", &N);
    ps.resize(N), Aidx.resize(N), Didx.resize(N);
    rep(i, N) {
        scanf("%d%d", &ps[i].first, &ps[i].second);
        Aidx[i] = {ps[i].first, i};
        Didx[i] = {ps[i].second, i};
    }
    sort(allof(Aidx)), sort(allof(Didx));
    for (auto& v : dp) {
        fill(allof(v), -1);
    }

    bool succ = play(0, 0);

    printf("Case #%d: %s\n", _turn + 1, succ ? "YES" : "NO");
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
