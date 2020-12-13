#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
typedef long long int lld;
typedef vector<vector<pair<int, lld> > > Graph;

struct MergeFindSet {
    std::vector<int> p;
    MergeFindSet(int n) : p(n) { init(); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void merge(int root, int child) { p[find(child)] = find(root); }
    void init() {
        for (int i = 0; i < int(p.size()); i++) p[i] = i;
    }
};

template <typename weight_t>
void dijstra(std::vector<std::vector<pair<int, weight_t> > >& G,
             std::vector<weight_t>& dist, int start) {
    typedef std::tuple<weight_t, int, int> S;  // <dist, from, current>
    std::priority_queue<S, vector<S>, greater<S> > Q;
    Q.push({(weight_t)(0), -1, start});

    while (Q.size()) {
        weight_t d;
        int from, curr;
        tie(d, from, curr) = Q.top();
        Q.pop();

        if (dist[curr] <= d) continue;
        dist[curr] = d;

        for (auto& p : G[curr]) {
            Q.push({p.second + d, curr, p.first});
        }
    }
}

int main() {
    for (int N, M, S, T; scanf("%d%d%d%d", &N, &M, &S, &T) != EOF;) {
        S--, T--;
        vector<tuple<lld, int, int> > edges(M);
        for (int i = 0; i < M; i++) {
            int u, v;
            lld w;
            scanf("%d%d%lld", &u, &v, &w);
            edges[i] = {w, u - 1, v - 1};
        }
        sort(edges.begin(), edges.end());

        MergeFindSet mfs(N);
        vector<int> valid_edges;
        for (int i = 0; i < M;) {
            int j = i;
            while (j < M and get<0>(edges[j]) == get<0>(edges[i])) j++;
            bool drop = true;
            for (int k = i; k < j and drop; k++) {
                if (mfs.find(get<1>(edges[k])) != mfs.find(get<2>(edges[k]))) {
                    drop = false;
                }
            }
            for (int k = i; k < j and not drop; k++) {
                valid_edges.push_back(k);
                mfs.merge(get<1>(edges[k]), get<2>(edges[k]));
            }
            i = j;
        }

        vector<vector<pair<int, lld> > > graph(N);
        for (int i : valid_edges) {
            int u, v;
            lld w;
            tie(w, u, v) = edges[i];
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
            // printf("%d %d %lld\n", u, v, w);
        }

        vector<lld> dist(N, INT64_MAX);
        dijstra(graph, dist, S);
        printf("%lld\n", dist[T]);
    }
}
