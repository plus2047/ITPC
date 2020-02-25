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
bool bellman_ford(vector<vector<pair<int, int> > >& graph, vector<int>& weight,
                  int start) {
    int N = len(graph);
    vector<int> que_count(N, 0);
    vector<char> seen(N, false);
    queue<int> que;
    que.push(start);
    weight[start] = 0;
    seen[start] = true;
    que_count[start] = 1;
    while (que.size()) {
        int node = que.front();
        que.pop();
        seen[node] = false;
        for (int i = 0; i < len(graph[node]); i++) {
            pair<int, int> p = graph[node][i];
            int _node = p.first;
            int _weight = p.second;
            if (_weight + weight[node] < weight[_node]) {
                que.push(_node);
                weight[_node] = _weight + weight[node];
                que_count[_node]++;
                if (que_count[_node] > N) {
                    return false;
                }
            }
        }
    }
    return true;
}

// ========== contest code ==========
const int N_MAX = 512, INF = 1E8;
int dist[N_MAX][N_MAX];

int main() {
    int F;
    scanf("%d", &F);
    rep(f, F) {
        int N, M, W;
        scanf("%d%d%d", &N, &M, &W);
        rep(i, N) rep(j, N) { dist[i][j] = INF; }
        rep(i, N) { dist[i][i] = 0; }

        int x, y, w;
        rep(i, M) {
            scanf("%d%d%d", &x, &y, &w);
            x--, y--;
            dist[x][y] = min(dist[x][y], w);
            dist[y][x] = min(dist[y][x], w);
        }
        rep(i, W) {
            scanf("%d%d%d", &x, &y, &w);
            x--, y--;
            dist[x][y] = min(dist[x][y], -w);
        }

        vector<vector<pair<int, int> > > graph(N + 1);
        rep(i, N) rep(j, N) {
            if (dist[i][j] < INF) {
                graph[i].push_back({j, dist[i][j]});
            }
        }
        rep(i, N) { graph[N].push_back({i, 0}); }

        vector<int> _dist(N + 1, INF);
        bool no_circle = bellman_ford(graph, _dist, N);

        printf(no_circle ? "NO\n" : "YES\n");
    }
}
