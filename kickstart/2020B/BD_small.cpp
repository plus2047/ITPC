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
    int W, H, L, U, R, D;
    scanf("%d%d%d%d%d%d", &W, &H, &L, &U, &R, &D);
    vector<vector<double> > P(H, vector<double>(W));
    P[0][0] = 1;
    L--, U--, R--, D--;
    rep(i, H) rep(j, W) {
        if (i == 0 and j == 0) continue;
        if (i >= U and i <= D and j >= L and j <= R) continue;
        if (i != 0) {
            if (j != W - 1) {
                P[i][j] += P[i - 1][j] / 2;
            } else {
                P[i][j] += P[i - 1][j];
            }
        }
        if (j != 0) {
            if (i != H - 1) {
                P[i][j] += P[i][j - 1] / 2;
            } else {
                P[i][j] += P[i][j - 1];
            }
        }
    }
    printf("Case #%d: %lf\n", _turn + 1, P[H - 1][W - 1]);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
