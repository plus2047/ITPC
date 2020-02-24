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

#include <bitset>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
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

// ========== contest code ==========

const int N_MAX = 1024;
bitset<N_MAX> arr[N_MAX];
vector<char> seen;
vector<vector<int> > graph;

void dfs(int node) {
    if (seen[node]) return;
    seen[node] = true;

    vector<int>& child = graph[node];
    for (int i = 0; i < len(child); i++) {
        dfs(child[i]);
        arr[node] |= arr[child[i]];
    }
}

int main() {
    int N, M;
    scanf("%d%d", &N, &M);

    vector<pair<int, int> > edges;
    rep(i, M) {
        int x, y;
        scanf("%d%d", &x, &y);
        edges.push_back({x - 1, y - 1});
    }
    sort(allof(edges));

    graph.resize(N);
    rep(i, N) { graph[i].clear(); }
    rep(i, M) {
        if (i == 0 or edges[i] != edges[i - 1]) {
            graph[edges[i].first].push_back(edges[i].second);
        }
    }

    seen.resize(N);
    fill(allof(seen), 0);

    rep(i, N) {
        arr[i].reset();
        arr[i].set(i);
    }
    int cnt = 0;
    rep(i, N) {
        dfs(i);
        cnt += arr[i].count();
    }

    printf("%d\n", (N + 1) * N / 2 - cnt);
}
