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
    int M;
    scanf("%d", &M);
    vector<int> C(M + 1);
    rep(i, M + 1) { scanf("%d", &C[i]); }
    C[0] *= -1;

    auto eq = [&](long double r) {
        long double t = 1, res = 0;
        inv(i, M + 1) {
            res += C[i] * t;
            t *= r;
        }
        return res;
    };

    long double delta = 1E-7, eq_delta = 1E-20;
    long double left = delta, right = 2 - delta;
    long double x1 = eq(left), x2 = eq(right), x3 = 0;
    while (right - left > delta) {
        long double mid = (left + right) / 2;
        x3 = eq(mid);
        if (abs(x3) < eq_delta) {
            left = right = mid;
            break;
        } else if (x1 * x3 < 0) {
            right = mid;
            x2 = x3;
        } else {
            left = mid;
            x1 = x3;
        }
    }
    printf("Case #%d: %.7Lf\n", _turn + 1, (left + right) / 2 - 1);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
