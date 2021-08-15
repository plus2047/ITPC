#pragma once
#include <algorithm>
#include <limits>
#include <queue>
#include <vector>

namespace contest {

struct Graph {
    int N, M, edge_index = 0;
    std::vector<int> first, from, to, next;
    Graph(int N, int M) : N(N), M(M), first(N, -1), from(M), to(M), next(M) {}
    void add_edge(int _from, int _to) {
        from[edge_index] = _from;
        to[edge_index] = _to;
        next[edge_index] = first[_from];
        first[_from] = edge_index++;
    }
};

}  // namespace contest
