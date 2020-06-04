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
    int R, C;
    scanf("%d%d", &R, &C);
    auto grid = vector<vector<int> >(R, vector<int>(C));
    rep(i, R) rep(j, C) { scanf("%d", &grid[i][j]); }

    int N = R * C;
    auto G = vector<vector<int> >(N + 1);
    auto ID = [&](int x, int y) { return x * C + y; };
    rep(i, R) rep(j, C) {
        auto& ch = G[ID(i, j)];
        if (i != 0) ch.push_back(ID(i - 1, j));
        if (i != R - 1) ch.push_back(ID(i + 1, j));
        if (j != 0) ch.push_back(ID(i, j - 1));
        if (j != C - 1) ch.push_back(ID(i, j + 1));

        if (i == 0 or i == R - 1 or j == 0 or j == C - 1) {
            ch.push_back(N);
            G[N].push_back(ID(i, j));
        }
    }

    auto cost = vector<int>(N + 1, -1);
    auto arrived = vector<char>(N + 1, 0);
    cost[N] = 0;

    typedef pair<int, int> S;
    priority_queue<S, vector<S>, greater<S> > Q;
    Q.push({0, N});
    while (Q.size()) {
        int c, n;
        tie(c, n) = Q.top();
        Q.pop();

        if (arrived[n]) continue;
        arrived[n] = true;

        for (int child : G[n]) {
            if (arrived[child]) continue;
            int _cost = max(cost[n], grid[child / C][child % C]);
            if (cost[child] < _cost) {
                cost[child] = _cost;
                Q.push({_cost, child});
            }
        }
    }

    int res = 0;
    rep(i, N) { res += cost[i] - grid[i / C][i % C]; }

    printf("Case #%d: %d\n", _turn + 1, res);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
