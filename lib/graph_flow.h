#pragma once
#include <limits>
#include <queue>
#include <vector>

namespace contest {

template <typename INDEX = int, typename NUM = int>
struct MFEdge {
    INDEX from, to;
    NUM capacity, flow;
};

template <typename INDEX = int, typename NUM = int>
struct MaxFlow {
    // Edmonds Karps Algorithm
    std::vector<MFEdge<INDEX, NUM>> edges;
    std::vector<std::vector<INDEX>> graph;

    std::vector<NUM> node_max_flow;
    std::vector<INDEX> path_from;

    void init(INDEX num_node) {
        graph.clear();
        graph.resize(num_node);
        edges.clear();
        node_max_flow.resize(num_node);
        path_from.resize(num_node);
    }

    void add_edge(INDEX from, INDEX to, NUM cap) {
        edges.push_back({from, to, cap, 0});
        int m = edges.size();
        graph[from].push_back(m - 1);
    }

    inline bool bfs(INDEX start, INDEX stop) {
        // bfs generate node_max_flow as the max flow to each node
        // and use this to check arrived.
        fill(node_max_flow.begin(), node_max_flow.end(), 0);
        node_max_flow[start] = std::numeric_limits<NUM>::max();

        std::queue<INDEX> Q;
        Q.push(start);

        while (!Q.empty()) {
            INDEX x = Q.front();
            Q.pop();
            for (INDEX i = 0; i < graph[x].size(); i++) {
                auto& e = edges[graph[x][i]];
                if (!node_max_flow[e.to] && e.capacity > e.flow) {
                    path_from[e.to] = graph[x][i];
                    node_max_flow[e.to] =
                        std::min(node_max_flow[x], e.capacity - e.flow);
                    Q.push(e.to);
                }
            }
            if (node_max_flow[stop]) break;
        }
        return node_max_flow[stop] != 0;
    }

    NUM max_flow(INDEX start, INDEX stop) {
        NUM flow = 0;
        while (bfs(start, stop)) {
            for (INDEX i = stop; i != start; i = edges[path_from[i]].from) {
                edges[path_from[i]].flow += node_max_flow[stop];
            }
            flow += node_max_flow[stop];
        }
        return flow;
    }
};

template <typename INDEX = int, typename NUM = int>
struct MCMFEdge {
    INDEX from, to;
    NUM capacity, flow, cost;
};

template <typename INDEX = int, typename NUM = int>
struct MinCostMaxFlow {
    std::vector<MCMFEdge<INDEX, NUM>> edges;
    std::vector<std::vector<INDEX>> graph;
    std::vector<INDEX> path_from;
    std::vector<NUM> path_weight, node_max_flow;
    std::vector<bool> in_queue;

    void init(INDEX num_node) {
        graph.clear();
        graph.resize(num_node);
        edges.clear();
        in_queue.resize(num_node);
        path_weight.resize(num_node);
        path_from.resize(num_node);
        node_max_flow.resize(num_node);
    }

    bool bellman_ford(INDEX start, INDEX stop, INDEX& flow, INDEX& cost) {
        auto INF = std::numeric_limits<NUM>::max();
        std::fill(in_queue.begin(), in_queue.end(), 0);
        std::fill(path_weight.begin(), path_weight.end(), INF);
        path_weight[start] = 0;
        in_queue[start] = true;
        node_max_flow[start] = INF;

        std::queue<INDEX> Q;
        Q.push(start);
        while (!Q.empty()) {
            auto u = Q.front();
            Q.pop();
            in_queue[u] = false;
            for (INDEX i = 0; i < graph[u].size(); i++) {
                auto& e = edges[graph[u][i]];
                if (e.capacity > e.flow &&
                    path_weight[e.to] > path_weight[u] + e.cost) {
                    path_weight[e.to] = path_weight[u] + e.cost;
                    path_from[e.to] = graph[u][i];
                    node_max_flow[e.to] =
                        min(node_max_flow[u], e.capacity - e.flow);
                    if (!in_queue[e.to]) {
                        Q.push(e.to);
                        in_queue[e.to] = true;
                    }
                }
            }
            if (path_weight[stop] == INF) return false;
            flow += node_max_flow[stop];
            cost += path_weight[stop] * node_max_flow[stop];
            for (INDEX u = stop; u != start; u = edges[path_from[u]].from) {
                edges[path_from[u]].flow += node_max_flow[stop];
                edges[path_from[u] ^ 1].flow -= node_max_flow[stop];
            }
        }
        return true;
    }

    void min_cost_max_flow(INDEX start, INDEX stop, NUM& flow, NUM& cost) {
        flow = 0;
        cost = 0;
        while (bellman_ford(start, stop, flow, cost))
            ;
    }
};
}  // namespace contest
