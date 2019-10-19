#pragma once
#include <algorithm>
#include <vector>

#include "merge_find.h"

namespace contest {
// Minimal Spanning Tree (MST) algorithm: Kruskal algotithm
// for un-directional graph.
// for a edge(u, v, w), it's not necessary to add (v, u, w) into input set.
template <typename index_t, typename weight_t>
struct MinSpaningTree {
    typedef std::tuple<index_t, index_t, weight_t> Edge;
    static const std::size_t node1_ = 0, node2_ = 1, weight_ = 2;

    std::vector<Edge> edges;
    std::vector<Edge> mst;
    MergeFindSet mf;

    MinSpaningTree(index_t n) : mf(n){};

    void add_edge(index_t node1, index_t node2, weight_t weight) {
        edges.push_back({node1, node2, weight});
    }

    void min_spaning_tree() {
        mst.clear();
        std::sort(edges.begin(), edges.end());
        for (auto& e : edges) {
            auto r1 = mf.find(std::get<node1_>(e)),
                 r2 = mf.find(std::get<node2_>(e));
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