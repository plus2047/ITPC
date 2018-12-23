#ifndef __ITPC_MATH_H__
#define __ITPC_MATH_H__

#include <algorithm>
#include <vector>
#include "merge_find_set.h"
#include "named_tuple.h"

// Minimal Spanning Tree (MST) algorithm: Kruskal algotithm
// for un-directional ded graph.
// for a edge(u, v, w), it's not necessary to add (v, u, w) into input set.
template <typename index_t, typename weight_t>
struct Kruskal {
    typedef std::tuple<index_t, index_t, weight_t> Edge;
    static const std::size_t node1_ = 0, node2_ = 1, weight_ = 2;

    std::vector<Edge> edges;
    std::vector<Edge> mst;
    MergeFindSet<index_t> mf;

    Kruskal(index_t n) : mf(n){};

    void add_edge(index_t node1, index_t node2, weight_t weight) {
        edges.push_back({node1, node2, weight});
    }

    void kruskal() {
        using namespace std;
        mst.clear();
        sort(edges.begin(), edges.end());
        for (auto& e : edges) {
            auto r1 = mf.find(get<node1_>(e)), r2 = mf.find(get<node2_>(e));
            if (r1 != r2) {
                mf.merge(r1, r2);
                mst.push_back(e);
            }
        }
    }
};
// Note: Prim's algorithm is also used for un-directional ded MST
// but it's more complex to implement.

#endif  // define __ITPC_MATH_H__