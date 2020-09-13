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
int R, C;
const int N_MAX = 128;
char G[N_MAX][N_MAX];

int dfs(int i, int j) {
    if (i == R) i = 0, j++;
    if (j == C) return 0;
    int cnt = dfs(i + 1, j);
    if ((i <= 1 or G[i - 1][j] != 1 or G[i - 2][j] != 1) and
        (j <= 1 or G[i][j - 1] != 1 or G[i][j - 2] != 1)) {
        G[i][j] = 1;
        cnt = max(cnt, 1 + dfs(i + 1, j));
        G[i][j] = 0;
    }
    return cnt;
}

void solve(int _turn) {
    scanf("%d%d", &R, &C);
    // if (R > 5 or C > 5) throw "data limit exceed";
    memset(G, 0, sizeof(G));
    printf("Case #%d: %d\n", _turn + 1, dfs(0, 0));
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
