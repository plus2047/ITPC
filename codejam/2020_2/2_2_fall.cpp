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
int edge_t[D_MAX];
int node_t[C_MAX];
int edge_idx[C_MAX][C_MAX];

struct S {
    int x, node, parent;
};
bool operator<(const S& s1, const S& s2) { return s1.x > s2.x; }

void solve(int _turn) {
    scanf("%d%d", &C, &D);
    rep(i, C - 1) { scanf("%d", &X[i + 2]); }
    rep(i, D) { scanf("%d%d", &U[i], &V[i]); }

    vector<vector<int> > G(C + 1);
    rep(i, D) {
        G[U[i]].push_back(V[i]);
        G[V[i]].push_back(U[i]);
        edge_idx[U[i]][V[i]] = i;
        edge_idx[V[i]][U[i]] = i;
    }

    rep(i, D) { edge_t[i] = INF; }
    rep(i, C + 1) { node_t[i] = INF; }

    priority_queue<S> q_ord, q_time;
    q_ord.push({0, 1, 0});
    edge_idx[1][0] = edge_idx[0][1] = D;

    int tail_t = -1, tail_n = 1, tail_ord = -1;
    while (q_ord.size() or q_time.size()) {
        S s = {-1, -1, -1};
        if (q_ord.size() and q_ord.top().x == tail_ord) {
            s = q_ord.top();
            q_ord.pop();
            if (node_t[s.node] != INF) continue;
            node_t[s.node] = tail_t;
            tail_n++;
        } else if (q_time.size() and q_time.top().x == tail_t) {
            s = q_time.top();
            q_time.pop();
            if (node_t[s.node] != INF) continue;
            node_t[s.node] = tail_t;
            tail_n++;
        } else if (q_ord.size() and q_ord.top().x == tail_ord + tail_n) {
            s = q_ord.top();
            q_ord.pop();
            if (node_t[s.node] != INF) continue;
            tail_t++;
            node_t[s.node] = tail_t;
            tail_ord += tail_n;
            tail_n = 1;
        } else if (q_time.size()) {
            s = q_time.top();
            q_time.pop();
            if (node_t[s.node] != INF) continue;
            tail_t = s.x;
            node_t[s.node] = tail_t;
            tail_ord += tail_n;
            tail_n = 1;
        }

        edge_t[edge_idx[s.node][s.parent]] = node_t[s.node] - node_t[s.parent];
        for (int child : G[s.node]) {
            int x = X[child];
            if (node_t[child] != INF) continue;
            if (x < 0) {
                q_ord.push({-x, child, s.node});
            } else {
                q_time.push({x, child, s.node});
            }
        }
        while (q_ord.size() and q_ord.top().x < tail_ord) {
            q_ord.pop();
        }
        while (q_time.size() and q_time.top().x < tail_t) {
            q_time.pop();
        }
    }

    printf("Case #%d:", _turn + 1);
    rep(i, D) { printf(" %d", edge_t[i]); }
    printf("\n");
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
