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
    lld R, C, K;
    scanf("%lld%lld%lld", &R, &C, &K);
    queue<pair<lld, lld> > que;
    lld cnt = R * C;
    vector<vector<char> > block(R, vector<char>(C, false));
    rep(i, K) {
        lld x, y;
        scanf("%lld%lld", &x, &y);
        que.push({x, y});
        block[x][y] = true;
        cnt--;
    }
    rep(i, R) { que.push({i, C}); }
    rep(j, C) { que.push({R, j}); }
    lld res = 0;
    const lld D[3][2] = {{-1, 0}, {0, -1}, {-1, -1}};
    while (cnt) {
        res += cnt;
        int qsize = len(que);
        rep(_, qsize) {
            lld x, y;
            tie(x, y) = que.front(), que.pop();
            for (int d = 0; d < 3; d++) {
                int _x = x + D[d][0], _y = y + D[d][1];
                if (_x >= 0 and _y >= 0 and _x < R and _y < C and
                    not block[_x][_y]) {
                    block[_x][_y] = true;
                    que.push({_x, _y});
                    cnt--;
                }
            }
        }
    }

    printf("Case #%d: %lld\n", _turn + 1, res);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
