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

struct Kosaraju {
    vector<vector<int> > ori_g, inv_g;
    vector<int> post, marks;
    vector<bool> seen;
    int N;

    Kosaraju() {}

    vector<int>& solve(const vector<vector<int> >& graph) {
        N = int(graph.size());
        ori_g = graph;
        inv_g = vector<vector<int> >(N);
        post = vector<int>();
        marks = vector<int>(N);
        seen = vector<bool>(N, false);

        for (int i = 0; i < N; i++) {
            for (int j : graph[i]) {
                inv_g[j].push_back(i);
            }
        }

        for (int i = 0; i < N; i++) {
            get_post(i);
        }

        int curr = 0;
        fill(seen.begin(), seen.end(), false);
        reverse(post.begin(), post.end());
        for (int node : post) {
            if (not seen[node]) {
                dfs_mark(node, curr);
                curr++;
            }
        }

        return marks;
    }

    void get_post(int node) {
        if (seen[node]) return;
        seen[node] = true;
        for (int child : ori_g[node]) get_post(child);
        post.push_back(node);
    }

    void dfs_mark(int node, int mark) {
        if (seen[node]) return;
        seen[node] = true;
        for (int child : inv_g[node]) dfs_mark(child, mark);
        marks[node] = mark;
    }
};

lld dfs(vector<lld>& score, vector<lld>& total, vector<vector<int> >& graph,
        int node) {
    if (total[node] != -1) return total[node];
    lld ms = 0;
    for (int child : graph[node]) {
        ms = max(ms, dfs(score, total, graph, child));
    }
    return total[node] = score[node] + ms;
}

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        int N = m + n;
        vector<lld> S;
        for (int i = 0; i < n; i++) {
            lld s;
            scanf("%lld", &s);
            S.push_back(s);
        }
        vector<vector<int> > graph(N);
        for (int i = 0; i < m; i++) {
            int u, v;
            lld w;
            scanf("%d%d%lld", &u, &v, &w);
            S.push_back(w);
            graph[u - 1].push_back(n + i);
            graph[n + i].push_back(v - 1);
        }

        vector<int> marks = Kosaraju().solve(graph);

        vector<lld> score(N, -1);
        vector<vector<int> > _graph(N);
        for (int i = 0; i < N; i++) {
            int g = marks[i];
            if (score[g] == -1) score[g] = 0;
            score[g] += S[i];
            for (int child : graph[i]) {
                int _g = marks[child];
                if (_g != g) _graph[g].push_back(_g);
            }
        }

        vector<lld> total(N, -1);
        lld res = 0;
        for (int i = 0; i < N; i++) {
            int g = marks[i];
            res = max(res, dfs(score, total, _graph, g));
        }
        printf("%lld\n", res);
    }
}
