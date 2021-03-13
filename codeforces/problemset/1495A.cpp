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
    lld n;
    scanf("%lld", &n);
    vector<lld> X, Y;
    rep(i, 2 * n) {
        lld x, y;
        scanf("%lld%lld", &x, &y);
        if(x) X.push_back(abs(x));
        if(y) Y.push_back(abs(y));
    }
    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());
    double res = 0;
    rep(i, n) {
        res += sqrt(X[i] * X[i] + Y[i] * Y[i]);
    }
    printf("%.12lf\n", res);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
