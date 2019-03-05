// ===== programing contest template ======
// ===== using standrod: C++ 11 =====

#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// ===== persional contest env =====

typedef long long int LL;
typedef long long unsigned LLU;
typedef long double LD;
#define G(_tuple, num) (get<num>(_tuple))
#define len(c) int((c).size())
#define allof(container) (container).begin(), (container).end()
#define rep(i, N) for (int i = 0; i < int(N); i++)
#define repr(i, begin, end) for (int i = int(begin); i < int(end); i++)
#define repi(i, N) for (int i = int(N) - 1; i >= 0; i--)
template <typename ITER>
void show(const char* note, ITER begin, ITER end) {
    printf("%s", note);
    while (begin != end) {
        std::cout << *(begin++) << ' ';
    }
    std::cout << std::endl;
}

template <typename ITER>
void show(const char* note, ITER begin, ITER end, int group) {
    printf("%s", note);
    int i = 1;
    for (; begin != end; i++) {
        std::cout << *(begin++) << ' ';
        if (i % group == 0) std::cout << std::endl;
    }
    if (i % group != 1) std::cout << std::endl;
}
struct MergeFindSet {
    std::vector<int> p;
    MergeFindSet(int n) : p(n) {
        for (int i = 0; i < n; i++) p[i] = i;
    }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void merge(int x, int y) { p[find(y)] = find(x); }
};

// ========== contest code ==========
vector<tuple<int, int, int>> graph;
vector<int> taken_cnt;
vector<int> path;
int cnt, N, edges_num;

void check() {
    if (path.size() > 2) {
        int max_edge = 0, sum_edge = 0;
        for (int edge : path) {
            if (edge > max_edge) max_edge = edge;
            sum_edge += edge;
        }
        if (sum_edge > max_edge * 2) {
            cnt++;
        }
    }
}

void dfs(int idx) {
    if (idx == edges_num) return;
    int x, y, num;
    tie(x, y, num) = graph[idx];
    if (!taken_cnt[x] and !taken_cnt[y]) {
        taken_cnt[x]++, taken_cnt[y]++;
        path.push_back(num);
        check();
        dfs(idx + 1);
        path.pop_back();
        taken_cnt[x]--, taken_cnt[y]--;
    }
    dfs(idx + 1);
}

void solve(int _turn) {
    scanf("%d", &N);
    graph.clear();
    rep(i, N) rep(j, N) {
        int num;
        scanf("%d", &num);
        if (i < j and num != 0) {
            graph.push_back({i, j, num});
        }
    }
    cnt = 0;
    edges_num = len(graph);
    taken_cnt = vector<int>(N, 0);
    path.clear();
    dfs(0);
    printf("Case #%d: %d\n", _turn, cnt);
}

// ===== kickstart template =====
int main() {
#ifdef __LOCAL__  // define in build command.
    freopen("_kickstart.in", "r", stdin);
    freopen("_debug.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
