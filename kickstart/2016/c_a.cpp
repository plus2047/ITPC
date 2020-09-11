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
char buff[32];
char graph[32][32];
double hasPos[32][32];

void solve(int _turn) {
    int R, C, RS, CS, S;
    scanf("%d%d%d%d%d", &R, &C, &RS, &CS, &S);
    double P, Q;
    scanf("%lf%lf", &P, &Q);
    rep(i, R) rep(j, C) {
        scanf("%s", buff);
        graph[i][j] = buff[0];
        hasPos[i][j] = 1;
    }
    unsigned mLim = 1 << (S * 2);
    double posMax = 0;
    for (unsigned mask = 0; mask < mLim; mask++) {
        double pos = 0;
        unsigned m = mask;
        rep(i, R) rep(j, C) { hasPos[i][j] = 1; }
        int x = RS, y = CS;
        for (int step = 0; step < S; step++) {
            unsigned _m = m & 3;
            m >>= 2;

            if (_m == 0) {
                x++;
            } else if (_m == 1) {
                x--;
            } else if (_m == 2) {
                y++;
            } else {
                y--;
            }

            if (x < 0 or y < 0 or x >= R or y >= C) {
                pos = 0;
                break;
            }

            double p = graph[x][y] == 'A' ? P : Q;
            pos += hasPos[x][y] * p;
            hasPos[x][y] *= 1 - p;
        }
        posMax = max(posMax, pos);
    }

    printf("Case #%d: %.8lf\n", _turn + 1, posMax);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
