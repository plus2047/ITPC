#pragma once
#include <algorithm>
#include <vector>

#include "merge_find.h"

namespace contest {

// Minimal Spanning Tree (MST) algorithm: Kruskal algotithm
// for un-directional graph.
// for a edge(u, v, w), it's not necessary to add (v, u, w) into input set.

template <typename weight_t>
struct MinSpaningTree {
    typedef std::tuple<weight_t, int, int> Edge;

    std::vector<Edge> edges;
    std::vector<Edge> mst;
    MergeFindSet mf;
    MinSpaningTree(int n) : mf(n){};

    void add_edge(int node1, int node2, weight_t weight) {
        edges.push_back({weight, node1, node2});
    }

    void min_spaning_tree() {
        mst.clear();
        std::sort(edges.begin(), edges.end());
        for (auto& e : edges) {
            auto r1 = mf.find(std::get<1>(e)), r2 = mf.find(std::get<2>(e));
            if (r1 != r2) {
                mf.merge(r1, r2);
                mst.push_back(e);
            }
        }
    }
};
// Note: Prim's algorithm is also used for un-directional ded MST
// but it's more complex to implement.
}  // namespace contest