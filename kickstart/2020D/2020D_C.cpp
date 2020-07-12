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
void dfs(vector<vector<int> >& G, vector<double>& pos, vector<int>& path,
         int curr, int step) {
    path.push_back(curr);
    for (int child : G[curr]) {
        dfs(G, pos, path, child, step);
    }
    pos[curr]++;
    path.pop_back();
    if (len(path) >= step) {
        pos[path[len(path) - step]] += pos[curr];
    }
}

void solve(int _turn) {
    lld N, A, B;
    scanf("%lld%lld%lld", &N, &A, &B);
    vector<vector<int> > G(N);
    vector<int> parent(N);
    for (int i = 1; i < N; i++) {
        int p;
        scanf("%d", &p);
        G[p - 1].push_back(i);
    }
    vector<double> pA(N), pB(N);
    vector<int> path;
    dfs(G, pA, path, 0, A);
    dfs(G, pB, path, 0, B);
    double res = 0;
    rep(i, N) {
        pA[i] /= N;
        pB[i] /= N;
        res += pA[i] + pB[i] - pA[i] * pB[i];
    }
    printf("Case #%d: %lf\n", _turn + 1, res);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
