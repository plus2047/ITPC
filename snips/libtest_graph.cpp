#include <climits>
#include <cstdio>
#include "../lib/graph.h"
#include "../lib/show.h"

using namespace std;

void test_kruskal() {
    Kruskal<int, int> k(5);

    k.edges = {{0, 1, 8}, {0, 2, 2}, {0, 3, 4},
               {0, 4, 3}, {1, 3, 1}, {2, 4, 4}};
    // test kruskal
    k.kruskal();
    printf("test kruskal:\n");
    for (auto& e : k.mst) {
        printf("%d %d\n", get<0>(e), get<1>(e));
    }
}

void test_dijkstra() {
    ShortestPath<int, int> d(5);
    vector<vector<int>> edges = {{0, 1, 8}, {0, 2, 2}, {0, 3, 4},
                                 {0, 4, 3}, {1, 3, 1}, {2, 4, 4}};
    for (auto& e : edges) {
        d.add_edge(e[0], e[1], e[2]);
        d.add_edge(e[1], e[0], e[2]);
    }
    d.dijkstra(0);

    printf("test dijkstra:\n");
    for (auto& dis : d.path_weight) {
        printf("%d ", dis);
    }
    printf("\n");

    for (auto& p : d.path_from) {
        printf("%d ", p);
    }
    printf("\n");
}

void test_flody() {
    Floyd<int> f(5);
#define set(i, j, k) \
    { f.graph[i][j] = f.graph[j][i] = k; }
    set(0, 1, 8);
    set(0, 2, 2);
    set(0, 3, 4);
    set(0, 4, 3);
    set(1, 3, 1);
    set(2, 4, 4);
    f.floyd();
    printf("test floyd:\n");
    for(int i = 0; i < 5; i ++){
        for(int j = 0; j < 5; j ++){
            printf("%d ", f.graph[i][j]);
        }
        printf("\n");
    }
}

void test_kosaraju() {
    // this is a graph from ITPC 06 P36
    vector<vector<int>> graph = {{1},    {2, 4, 5}, {3, 6}, {2, 7},
                                 {0, 5}, {6},       {5},    {3, 6}};
    auto mark = kosaraju(graph);
    show("mark: ", mark.begin(), mark.end());
}

int main() {
    // test_kruskal();
    // test_dijkstra();
    // test_kosaraju();
    test_flody();
}