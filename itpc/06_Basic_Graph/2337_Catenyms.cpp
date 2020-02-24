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

// graph =====
struct Edge {
    int to, next, index;
    bool seen;
};

vector<Edge> edges;
vector<int> head;

void init_graph(int node_num) {
    edges.clear();
    head.resize(node_num);
    fill(head.begin(), head.end(), -1);
}

void add_edge(int u, int v, int index) {
    edges.push_back({v, head[u], index, false});
    head[u] = int(edges.size()) - 1;
}

void dfs(vector<int>& path, int u) {
    for (int i = head[u]; i != -1; i = edges[i].next) {
        if (not edges[i].seen) {
            edges[i].seen = true;
            dfs(path, edges[i].to);
            path.push_back(edges[i].index);
        }
    }
}

int main() {
    const int CHAR_NUM = 26, STR_LEN = 32;
    int T, n;
    scanf("%d", &T);
    rep(t, T) {
        scanf("%d", &n);
        vector<string> strs;
        static char buff[STR_LEN];
        rep(i, n) {
            scanf("%s", buff);
            strs.push_back(buff);
        }
        sort(allof(strs));

        init_graph(CHAR_NUM);
        vector<int> in_deg(CHAR_NUM), out_deg(CHAR_NUM);
        int dfs_first = 100;  // init as the min node.
        rev(i, n) {           // reverse insert
            int u = *strs[i].begin() - 'a', v = *strs[i].rbegin() - 'a';
            add_edge(u, v, i);
            in_deg[v]++;
            out_deg[u]++;
            if (u < dfs_first) dfs_first = u;
            if (v < dfs_first) dfs_first = v;
        }

        int first_cnt = 0, last_cnt = 0;
        rep(i, CHAR_NUM) {
            int diff = out_deg[i] - in_deg[i];
            if (diff == 1) {
                first_cnt++;
                dfs_first = i;
            } else if (diff == -1) {
                last_cnt++;
            } else if (diff != 0) {
                first_cnt = 2;
            }
        }

        if (not((first_cnt == 0 and last_cnt == 0) or
                (first_cnt == 1 and last_cnt == 1))) {
            printf("***\n");
            continue;
        }

        vector<int> path;
        dfs(path, dfs_first);
        if (len(path) != n) {
            printf("***\n");
            continue;
        }

        for (int i = len(path) - 1; i >= 0; i--) {
            printf("%s", strs[path[i]].c_str());
            if (i > 0) {
                printf(".");
            } else {
                printf("\n");
            }
        }
    }
}