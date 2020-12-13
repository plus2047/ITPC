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

pair<lld, lld> get_polar(Graph& graph, int node, int parent) {
    pair<lld, lld> res = {node, 0};  // <polar, distance>
    for (auto& p : graph[node]) {
        if (p.first == parent) continue;
        auto _p = get_polar(graph, p.first, node);
        _p.second += p.second;
        if (_p.second > res.second) {
            res = _p;
        }
    }
    return res;
}

vector<lld> farthest_dp;
lld get_farthest(Graph& graph, lld node, lld parent) {
    if (farthest_dp[node] != -1) return farthest_dp[node];
    lld farthest = 0;
    for (auto& p : graph[node]) {
        if (p.first == parent) continue;
        farthest = max(farthest, p.second + get_farthest(graph, p.first, node));
    }
    return farthest_dp[node] = farthest;
}

void mark(Graph& graph, vector<lld>& weight, lld node, lld parent, lld inital) {
    if (graph[node].size() == 1 and parent != -1) {
        weight[node] = inital;
        return;
    }
    lld farthest_dist = -1;
    lld farthest_subtree = -1;
    for (auto& p : graph[node]) {
        if (p.first == parent) continue;
        lld f = p.second + get_farthest(graph, p.first, node);
        if (f > farthest_dist) {
            farthest_dist = f;
            farthest_subtree = p.first;
        }
    }
    for (auto& p : graph[node]) {
        if (p.first == parent) continue;
        lld _initial = p.second;
        if (p.first == farthest_subtree) _initial += inital;
        mark(graph, weight, p.first, node, _initial);
    }
}

int main() {
    lld n;
    while (scanf("%lld", &n) != EOF) {
        Graph graph(n);
        farthest_dp = vector<lld>(n, -1);
        for (lld i = 1; i < n; i++) {
            lld u, v;
            lld w;
            scanf("%lld%lld%lld", &u, &v, &w);
            graph[u - 1].push_back({v - 1, w});
            graph[v - 1].push_back({u - 1, w});
        }

        lld polar = get_polar(graph, 0, -1).first;

        vector<lld> weight(n);
        mark(graph, weight, polar, -1, 0);
        sort(weight.begin(), weight.end());

        lld pre = 0;
        for (lld i = n - 1; i >= 0; i--) {
            printf("%lld ", pre);
            pre += weight[i];
        }
        printf("\n");
    }
}
