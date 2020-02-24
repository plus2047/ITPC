#pragma once
#include <set>
#include <utility>
#include <vector>

namespace contest {
// ===== personal contest template =====

// Tarjan algorithm
// cut vertex, bridge, vertex-biconnected or edge-biconnected compounds
// for UNDIRECTED, CONNECTED graph.
// if the graph isn't connected, it also run on each connected subgraph.
// Reference:
// https://blog.csdn.net/fuyukai/article/details/51039788
// https://blog.csdn.net/fuyukai/article/details/51303292
//
// cut vertex: if remove this vertex, the connected graph (or subgraph)
// will become unconnected.
//
// bridge: if remove this edge, the connected graph will become unconnected.
//
// vertex-biconnected compounds: in this graph, there must be at least two
// paths between any two vertex and those two paths share NO vertex.
// OR if you remove any one EDGE from this subgraph, it still connected.
// OR any two edges in this subgraph must be in one CIRCLE.
// be careful: this algorithm will also treat two nodes with one edge
// connected as vertex biconnected compounds.
//
// edge-biconnected compounds: in this graph, there must be at least two
// paths between any two vertex and those two paths share NO edge.
// OR if you remove any one VERTEX from this subgraph, it still connected.
// OR any one edge in this subgraph must be in one CIRCLE.
// OR any two vertices are in one CIRCLE.
//
// the key of this algorithm is the DFS function.
struct Tarjan {
    void tarjan_dfs(int node, int parent) {
        // UNSEEN child of this node
        int child_cnt = 0;

        // dfn[node]: deep first number of this node.
        // the order of this node been seen.
        //
        // low[node]: the lowest dfn this node's children
        // can seen.
        low[node] = dfn[node] = ++stamp;

        for (int i = 0; i < int(graph[node].size()); i++) {
            int child = graph[node][i];
            if (child == parent) continue;
            std::pair<int, int> edge = make_edge(node, child);

            if (!dfn[child]) {
                child_cnt++;

                // tracing the dfs path.
                dfs_trace.push_back(edge);
                tarjan_dfs(child, node);

                low[node] = std::min(low[node], low[child]);

                // mark cut vertex and vertex-biconnected compounds.
                if (low[child] >= dfn[node] and child != parent) {
                    // mark cut
                    cut[node] = 1;

                    // mark vertex biconnected compound
                    // vertex_biconnected don't hold all of edges
                    // in the vertex-biconnected compound.
                    // but all node must show at least once.
                    vertex_biconnected.push_back({});
                    while (true) {
                        std::pair<int, int> _edge = dfs_trace.back();
                        vertex_biconnected.back().push_back(_edge);
                        dfs_trace.pop_back();
                        if (_edge == edge) break;
                    }
                }

                // mark bridge
                if (low[child] > dfn[node]) {
                    bridge.insert(edge);
                }
            } else {
                low[node] = std::min(low[node], dfn[child]);
            }
        }

        if (parent < 0 and child_cnt == 1) {  // root
            cut[node] = 0;
        }
    }

    void run(std::vector<std::vector<int> >& graph) {
        node_num = int(graph.size());

        low.resize(node_num);
        fill(low.begin(), low.end(), 0);

        dfn.resize(node_num);
        fill(dfn.begin(), dfn.end(), 0);

        cut.resize(node_num);
        fill(cut.begin(), cut.end(), 0);

        vertex_biconnected.clear();

        bridge.clear();
        stamp = 0;
        this->graph = graph;

        for (int i = 0; i < node_num; i++) {
            if (not dfn[i]) {
                tarjan_dfs(0, -1);
            }
        }

        // get edge biconnected compounds
        // using merge-find set.
        edge_biconnected.resize(node_num);
        for (int i = 0; i < node_num; i++) {
            edge_biconnected[i] = i;
        }
        for (int i = 0; i < node_num; i++) {
            std::vector<int>& child_vec = graph[i];
            for (int j = 0; j < int(child_vec.size()); j++) {
                std::pair<int, int> edge = make_edge(i, child_vec[j]);
                if (bridge.count(edge)) continue;
                ebcc_merge(edge.first, edge.second);
            }
        }
    }

    inline std::pair<int, int> make_edge(int node1, int node2) {
        if (node1 > node2) std::swap(node1, node2);
        return std::make_pair(node1, node2);
    }

    int stamp, node_num;
    std::vector<int> low, dfn;
    std::vector<std::pair<int, int> > dfs_trace;
    std::vector<std::vector<int> > graph;

    std::vector<char> cut;
    std::set<std::pair<int, int> > bridge;
    std::vector<std::vector<std::pair<int, int> > > vertex_biconnected;
    // merge find set for the edge biconnected compounds
    std::vector<int> edge_biconnected;
    int ebcc_find(int x) {
        return edge_biconnected[x] == x ? x : ebcc_find(edge_biconnected[x]);
    }
    void ebcc_merge(int root, int leaf) {
        edge_biconnected[ebcc_find(leaf)] = edge_biconnected[ebcc_find(root)];
    }

    void print() {
        printf("cut vertex:\n");
        for (int i = 0; i < node_num; i++) {
            printf("%d ", int(cut[i]));
        }
        printf("\n");

        printf("birdge:\n");
        std::set<std::pair<int, int> >::iterator iter;
        for (iter = bridge.begin(); iter != bridge.end(); iter++) {
            printf("%d-%d ", iter->first, iter->second);
        }
        printf("\n");

        printf("vertex-biconnected compounds:\n");
        for (int i = 0; i < int(vertex_biconnected.size()); i++) {
            std::vector<std::pair<int, int> >& v = vertex_biconnected[i];
            for (int j = 0; j < int(v.size()); j++) {
                printf("%d-%d ", v[j].first, v[j].second);
            }
            printf("\n");
        }

        printf("edge-biconnected compounds:\n");
        for (int i = 0; i < node_num; i++) {
            printf("%d ", ebcc_find(i));
        }
        printf("\n");
    }
};

// ========== contest code ==========

void tarjan_test() {
    std::vector<std::vector<int> > graph;
    Tarjan tarjan;

    graph = {
        {1, 3},     // 0
        {0, 2},     // 1
        {1, 3},     // 2
        {0, 2, 4},  // 3
        {3, 5, 6},  // 4
        {4, 6},     // 5
        {4, 5}      // 6
    };
    printf(
        "0 - 3 - 4 - 5\n"
        "|   |   | /\n"
        "1 - 2   6\n");
    tarjan.run(graph);
    tarjan.print();
    printf("\n");

    graph = {
        {1, 6},        // 0
        {0, 2, 3, 5},  // 1
        {1, 3, 4},     // 2
        {1, 2, 4},     // 3
        {2, 3},        // 4
        {1, 6, 7, 8},  // 5
        {0, 5},        // 6
        {5, 8},        // 7
        {5, 7, 9},     // 8
        {8}            // 9
    };
    printf(
        "4 - 3     7\n"
        "| / |    / \\\n"
        "2 - 1 - 5 - 8 - 9\n"
        "    |   |\n"
        "    0 - 6\n");
    tarjan.run(graph);
    tarjan.print();
    printf("\n");
}
}  // namespace contest
