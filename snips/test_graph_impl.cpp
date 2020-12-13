// =====
// implement of graph
// =====
#include <vector>
using namespace std;

void test_graph_impl() {
    // test the two implement of graph: 2D vector or adjacency list
    // result:
    // for N = 4000, M = N * 100
    // 2D vector takes 10ms to build while adjacency list takes 1ms.
    // althrough adjacency is faster, but 2D vector is fast enough for
    // a normal OJ question. and 2D vector is faster to travel.
    // adjacency list may be useful when
    // the graph is very very sparse and node number is very very large.
    using namespace std;

    int N = 100000, M = N * 100;
    vector<vector<int>> g1(N);
    vector<pair<int, int>> edge_sample(M);
    for (int edge_id = 0; edge_id < M; edge_id++) {
        edge_sample[edge_id] = {abs(random()) % N, abs(random()) % N};
    }
    clock_t t0, t1;

    t0 = clock();
    for (int edge_id = 0; edge_id < M; edge_id++) {
        g1[edge_sample[edge_id].first].push_back(edge_sample[edge_id].second);
    }
    t1 = clock();
    int total = 0;
    for (int edge_id = 0; edge_id < N; edge_id++) {
        total += g1[edge_id].size();
    }
    printf("total: %d, time: %lf\n", total, float(t1 - t0) / CLOCKS_PER_SEC);

    vector<int> first(N, -1), from(M), to(M), next(M);
    t0 = clock();
    for (int edge_id = 0; edge_id < M; edge_id++) {
        from[edge_id] = edge_sample[edge_id].first;
        to[edge_id] = edge_sample[edge_id].second;
        next[edge_id] = first[from[edge_id]];
        first[from[edge_id]] = edge_id;
    }
    t1 = clock();
    total = 0;
    int hash = 0;
    for (int edge_id = 0; edge_id < N; edge_id++) {
        int curr = first[edge_id];  // core part

        int index = g1[edge_id].size() - 1;  // for check
        while (curr != -1) {
            total++; // for check
            assert(from[curr] == edge_id);  // for check
            assert(to[curr] == g1[edge_id][index--]);  // for check
        
            curr = next[curr];  // core part
        }
    }
    printf("total: %d, time: %lf\n", total, float(t1 - t0) / CLOCKS_PER_SEC);
}

int main(){
    test_graph_impl();
}