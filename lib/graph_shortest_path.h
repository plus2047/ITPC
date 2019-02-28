#pragma once
#include <algorithm>
#include <limits>
#include <queue>
#include <vector>

namespace contest {
template <typename index_t, typename weight_t>
struct ShortestPath {
    // implement graph using 2D-vector. (not dense matrix.)
    // implement dijkstra & bellmen-ford algorithm in this struct because
    // they are very similar & both of them can run on 2D-vector.

    // to check if a node is reachable, check if path_weight[i] == INF
    // donot use arrived vector
    // because bellmen_ford algorithm could clear it after run.

    typedef std::tuple<index_t, weight_t> Edge;
    static const std::size_t edge_to_ = 0, edge_weight_ = 1;

    std::vector<std::vector<Edge>> graph;

    std::vector<bool> arrived;
    std::vector<weight_t> path_weight;
    std::vector<index_t> path_from;
    std::vector<index_t> count;
    weight_t INF;

    ShortestPath(std::size_t n) {
        graph.resize(n);
        INF = std::numeric_limits<weight_t>::max();
    }

    inline void add_edge(index_t from, index_t to, weight_t d) {
        graph[from].push_back({to, d});
    }

    inline void _init(index_t start) {
        path_weight.resize(graph.size());
        std::fill(path_weight.begin(), path_weight.end(), INF);
        path_weight[start] = 0;

        arrived.resize(graph.size());
        std::fill(arrived.begin(), arrived.end(), false);

        path_from.resize(graph.size());
        // warning: path_from[start] is init to 0.

        // count just used in bellmen_ford algorithm.
        count.resize(graph.size());
        std::fill(count.begin(), count.end(), 0);
    }

    void dijkstra(index_t start) {
        // (directed positive-weighted graph shortest path)
        // run dijstra's algorithm.
        // result is saved in weight & path_from vector.
        // there cannot be negative path in graph.
        _init(start);

        typedef std::tuple<weight_t, index_t> HNode;
        const std::size_t heap_node_weight_ = 0, heap_node_index_ = 1;
        std::priority_queue<HNode, std::vector<HNode>, std::greater<HNode>> Q;
        Q.push({0, start});

        while (!Q.empty()) {
            auto node = std::get<heap_node_index_>(Q.top());
            Q.pop();

            if (arrived[node]) continue;
            arrived[node] = true;

            for (auto& e : graph[node]) {
                auto _to = std::get<edge_to_>(e);
                auto _weight = std::get<edge_weight_>(e);
                // path_weight[node] must not be INF
                // so path_weight[node] + _weight is safe.
                if (path_weight[_to] > path_weight[node] + _weight) {
                    path_weight[_to] = path_weight[node] + _weight;
                    path_from[_to] = node;
                    Q.push({path_weight[_to], _to});
                }
            }
        }
    }

    bool bellmen_ford(index_t start) {
        // run bellmen_ford algorithm.
        // there can be negative path in graph.
        // if negative-circle exist, return false.
        // else result is saved in weight & path_from vector.
        _init(start);

        std::queue<index_t> Q;
        Q.push(start);

        // use `arrived` vector to mark if a node is in queue.
        // (it's differenet from the using in dijkstra algorithm.)
        // a node can be add to queue at most N (number of nodes) times.
        arrived[start] = true;

        while (!Q.empty()) {
            auto node = Q.front();
            Q.pop();
            arrived[node] = false;

            for (auto& e : graph[node]) {
                auto _to = std::get<edge_to_>(e);
                auto _weight = std::get<edge_weight_>(e);
                if (path_weight[node] != INF &&
                    path_weight[_to] > path_weight[node] + _weight) {
                    path_weight[_to] = path_weight[node] + _weight;
                    path_from[_to] = node;
                    if (!arrived[_to]) {
                        Q.push(_to);
                        arrived[_to] = true;
                        if (++count[_to] > graph.size()) {
                            return false;
                        }
                    }
                }
            }
        }

        return true;
    }
};

template <typename weight_t>
struct Floyd {
    weight_t INF;
    std::vector<std::vector<weight_t>> graph;  // dense matrix

    Floyd(std::size_t N)
        : INF(std::numeric_limits<weight_t>::max()),
          graph(N, std::vector<weight_t>(N, INF)) {
        // after init, set edge weight manually.
        for (int i = 0; i < N; i++) {
            graph[i][i] = 0;
        }
    };

    void floyd() {
        // in-place algorithm!
        // it will generate result on graph matrix.
        std::size_t N = graph.size();
        for (int k = 0; k < N; k++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (graph[i][k] < INF && graph[k][j] < INF) {
                        graph[i][j] =
                            std::min(graph[i][j], graph[i][k] + graph[k][j]);
                    }
                }
            }
        }
    }
};
}  // namespace contest
