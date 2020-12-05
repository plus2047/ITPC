#pragma once
#include <vector>

namespace contest {
using namespace std;

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

}  // namespace contest
