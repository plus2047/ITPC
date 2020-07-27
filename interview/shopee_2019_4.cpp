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

int main() {
    int n;
    scanf("%d", &n);
    vector<vector<int> > mat(n, vector<int>(n));
    vector<int> cx(n), cy(n);
    int total = 0;
    rep(i, n) rep(j, n) {
        scanf("%d", &mat[i][j]);
        if (mat[i][j]) {
            cx[i]++;
            cy[j]++;
            total++;
        }
    }

    int res = INT_MAX;

    int px = 0, pwx = 0, sx = total, swx = 0;
    rep(i, n) { swx += cx[i] * i; }
    
    rep(i, n) {
    
        int py = 0, pwy = 0, sy = total, swy = 0;
        rep(j, n) { swy += cy[j] * j; }
    
        rep(j, n) {
            if (mat[i][j] == 0) {
                res = min(res, pwx + swx + pwy + swy);
            }
            py += cy[j];
            pwy += py;
            sy -= cy[j];
            swy -= sy;
        }
        px += cx[i];
        pwx += px;
        sx -= cx[i];
        swx -= sx;
    }

    printf("%d\n", res == INT_MAX ? -1 : res);
}
