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
    int N, X;
    scanf("%d%d", &N, &X);
    vector<int> A(N);
    rep(i, N) { scanf("%d", &A[i]); }
    rep(i, N) { A[i] = A[i] / X + (A[i] % X ? 1 : 0); }
    vector<int> res;
    vector<pair<int, int>> T;
    rep(i, N) { T.push_back({A[i], i}); }
    sort(allof(T));
    printf("Case #%d:", _turn + 1);
    rep(i, N) { printf(" %d", T[i].second + 1); }
    printf("\n");
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
