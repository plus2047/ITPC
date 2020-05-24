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

struct log2Calculater {
    typedef double num;
    vector<num> fact;
    log2Calculater(int lim) : fact(lim) {
        fact[0] = fact[1] = 0;
        for (int i = 2; i < lim; i++) {
            fact[i] = fact[i - 1] + log2(num(i));
        }
    }
    inline num comb(int N, int k) { return fact[N] - fact[k] - fact[N - k]; }
};

auto cal = log2Calculater(10E5 + 8);

double pos(int x, int y) {
    // 1-indexed
    // C(x - 1, x + y - 2) / 2 ** (x + y - 2)
    double A = cal.comb(x + y - 2, x - 1);
    double B = x + y - 2;
    assert(A <= B);
    return pow(2.0, A - B);
}

void solve(int _turn) {
    int W, H, L, U, R, D;
    scanf("%d%d%d%d%d%d", &W, &H, &L, &U, &R, &D);

    double res = 0;
    if(D < H) {
        for(int i = 1; i < L; i++) {
            res += pos(i, D) / 2;
        }
    }
    if(R < W) {
        for(int j = 1; j < U; j++) {
            res += pos(R, j) / 2;
        }
    }

    printf("Case #%d: %lf\n", _turn + 1, res);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
