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

// ========== contest code ==========
char buff[128];

pair<int, int> max_dist(vector<vector<pair<int, int> > >& graph, int node,
                        int parent) {
    int max_d = 0, max_node = node;
    vector<pair<int, int> >& v = graph[node];
    for (int i = 0; i < len(v); i++) {
        pair<int, int> p = v[i];
        if (p.first == parent) continue;
        pair<int, int> r = max_dist(graph, p.first, node);
        int dist = r.second + p.second;
        if (dist > max_d) {
            max_d = dist;
            max_node = r.first;
        }
    }
    return {max_node, max_d};
}

int main() {
    for (int N, M; scanf("%d%d", &N, &M) != EOF;) {
        vector<vector<pair<int, int> > > graph(N);
        rep(i, M) {
            int x, y, w;
            scanf("%d%d%d%s", &x, &y, &w, buff);
            x--, y--;
            graph[x].push_back({y, w});
            graph[y].push_back({x, w});
        }
        pair<int, int> r1 = max_dist(graph, 0, -1);
        pair<int, int> r2 = max_dist(graph, r1.first, -1);
        printf("%d\n", r2.second);
    }
}
