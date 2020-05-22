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
const int C_MAX = 128, D_MAX = 1024, INF = 1E6;
int C, D, X[C_MAX], U[D_MAX], V[D_MAX];

void solve(int _turn) {
    scanf("%d%d", &C, &D);
    rep(i, C - 1) { scanf("%d", &X[i + 2]); }
    rep(i, D) { scanf("%d%d", &U[i], &V[i]); }

    vector<int> T(C + 1), R(C + 1);
    vector<pair<int, int> > t, r;
    for (int i = 2; i <= C; i++) {
        int x = X[i];
        if (x < 0) {
            r.push_back({-x, i});
            R[i] = -x;
        } else {
            t.push_back({x, i});
            T[i] = x;
        }
    }
    sort(allof(r));
    sort(allof(t));

    int ri = 0, ti = 0, k = 1;
    for (int N = 1; N < C; N++) {
        if (ri < len(r) and r[ri].first <= N) {
            int i = r[ri].second;
            T[i] = R[i] == R[k] ? T[k] : T[k] + 1;
            ri++;
            k = i;
        } else {
            int j = t[ti].second;
            R[j] = T[j] == T[k] ? R[k] : N;
            ti++;
            k = j;
        }
    }

    printf("Case #%d:", _turn + 1);
    rep(i, D) { printf(" %d", max(1, abs(T[U[i]] - T[V[i]]))); }
    printf("\n");
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
