#pragma once
#include <vector>

namespace contest {
template <typename index_t>
void dfs_mark(std::vector<std::vector<index_t> >& graph, index_t start,
              index_t valid_mark, index_t new_mark,
              std::vector<index_t>& marks) {
    if (marks[start] != valid_mark) return;
    marks[start] = new_mark;
    for (auto to : graph[start]) {
        dfs_mark(graph, to, valid_mark, new_mark, marks);
    }
};

template <typename index_t>
std::vector<index_t> kosaraju(std::vector<std::vector<index_t> >& graph) {
    int N = graph.size();

    std::vector<index_t> marks(N);
    for (int i = 0; i < N; i++) {
        dfs_mark(graph, i, 0, N + i, marks);
    }

    std::vector<std::vector<index_t> > inv_g(N);
    for (int i = 0; i < N; i++) {
        for (auto j : graph[i]) {
            inv_g[j].push_back(i);
        }
    }

    index_t mark_count = 0;
    for (int i = 0; i < N; i++) {
        if (marks[i] >= N) {
            dfs_mark(inv_g, i, marks[i], mark_count, marks);
            mark_count++;
        }
    }

    return marks;
}

}  // namespace contest
