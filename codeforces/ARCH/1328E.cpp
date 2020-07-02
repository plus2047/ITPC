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
#include <tuple>
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
#define inv(i, N) for (int i = int(N) - 1; i >= 0; --i)

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

// ========== contest code ==========
int n, m;
vector<int> parent, depth;
vector<pair<int, int> > graph;
vector<int> head;

inline void push(int p, int c) {
    graph.push_back({c, head[p]});
    head[p] = len(graph) - 1;
}

int stamp;
vector<int> t_in, t_out;

void dfs(int node, int _parent, int _depth) {
    stamp++;
    t_in[node] = stamp;
    parent[node] = _parent;
    depth[node] = _depth;
    for (int ci = head[node]; ci != -1; ci = graph[ci].second) {
        int c = graph[ci].first;
        if (c != _parent) {
            dfs(c, node, _depth + 1);
        }
    }
    t_out[node] = stamp;
}

vector<int> nodes;
vector<char> path;
inline void query() {
    int k;
    scanf("%d", &k);
    nodes.resize(k);
    rep(i, k) {
        scanf("%d", &nodes[i]);
        nodes[i]--;
    }

    int max_depth = -1, max_depth_node = -1;
    rep(i, k) {
        int node = nodes[i];
        if (depth[node] > max_depth) {
            max_depth = depth[node];
            max_depth_node = node;
        }
    }

    bool succ = true;
    for (int node : nodes) {
        int p = parent[node];
        if (not(t_in[p] <= t_in[max_depth_node] and
                t_out[p] >= t_out[max_depth_node])) {
            succ = false;
            break;
        }
    }

    printf("%s\n", succ ? "YES" : "NO");
}

int main() {
    scanf("%d%d", &n, &m);

    graph.clear();
    graph.reserve(n);
    head = vector<int>(n, -1);
    parent = vector<int>(n);
    depth = vector<int>(n);
    stamp = 0;
    t_in.resize(n);
    t_out.resize(n);

    rep(i, n - 1) {
        int x, y;
        scanf("%d%d", &x, &y);
        x--, y--;
        push(x, y);
        push(y, x);
    }

    dfs(0, 0, 0);

    rep(i, m) { query(); }
}
