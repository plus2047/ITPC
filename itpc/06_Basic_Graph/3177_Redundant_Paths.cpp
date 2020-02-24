// ===== programing contest template ======
// ===== using standrod: C++ 11 =====

// #undef __LOCAL__

#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <bitset>
#include <functional>
#include <random>
#include <unordered_map>
#include <unordered_set>
#endif  // C++11

using namespace std;

// ===== personal contest env =====

typedef long long int lld;

#define frontof(c, k) (c).begin(), (c).begin() + (k)
#define allof(c) (c).begin(), (c).end()
#define len(container) int((container).size())
#define asmin(var, val) var = min(var, val)
#define asmax(var, val) var = max(var, val)

#define iter(i, begin, end) \
    for (int i = begin, d = begin < end ? 1 : -1; i != end; i += d)
#define each(i, first, last) \
    for (int i = first, d = first < last ? 1 : -1; i != last + d; i += d)

#define rep(i, N) for (int i = 0; i < int(N); ++i)
#define rev(i, N) for (int i = int(N) - 1; i >= 0; --i)

#if __cplusplus >= 201103L
template <typename num>
using mat = vector<vector<num> >;

template <typename num>
inline mat<num> make_mat(int s1, int s2, num val) {
    return mat<num>(s1, vector<num>(s2, val));
}

template <typename num>
inline void fill(mat<num>& m, num val) {
    for (auto& v : m)
        for (auto& n : v) n = val;
}

template <typename num>
void show(mat<num> m) {
    for (const auto& v : m) {
        for (const auto& n : v) cout << n << ' ';
        cout << endl;
    }
}
#endif  // C++11

template <typename ITER>
void show(const char* note, ITER begin, ITER end) {
#ifdef __LOCAL__
    std::cout << note;
    for (; begin != end; begin++) std::cout << *begin << ' ';
    cout << endl;
#endif  // __LOCAL__
}

void echo(const char* fmt, ...) {
#ifdef __LOCAL__
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
#endif  // __LOCAL__
}

// ===== personal contest template =====
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

// ===== kickstart template =====
int main() {
    Tarjan tarjan;
    for (int F, R; scanf("%d%d", &F, &R) != EOF;) {
        vector<vector<int> > graph(F);
        rep(i, R) {
            int x, y;
            scanf("%d%d", &x, &y);
            --x, --y;
            graph[x].push_back(y);
            graph[y].push_back(x);
        }
        tarjan.run(graph);
        // tarjan.print();
        // printf("\n");

        vector<int> degree(F);
        set<pair<int, int> > seen;
        rep(i, F) {
            vector<int>& v = graph[i];
            rep(j, len(v)) {
                int x = tarjan.ebcc_find(v[j]);
                int y = tarjan.ebcc_find(i);
                if (x == y) continue;
                if (x > y) swap(x, y);
                if (seen.count({x, y})) continue;
                seen.insert({x, y});
                degree[x]++;
                degree[y]++;
            }
        }
        // show("degree: ", allof(degree));
        int cnt1 = 0;
        rep(i, F) cnt1 += degree[i] == 1;
        printf("%d\n", (cnt1 + 1) / 2);
    }
}
