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
const int INF = 1E8;

void dijkstra(vector<vector<pair<int, int> > >& graph, vector<int>& dist,
              int start) {
    priority_queue<pair<int, int>, vector<pair<int, int> >,
                   greater<pair<int, int> > >
        pq;
    pq.push({0, start});
    dist[start] = 0;

    while (pq.size()) {
        int w = pq.top().first, node = pq.top().second;
        pq.pop();
        for (int i = 0; i < len(graph[node]); i++) {
            pair<int, int> p = graph[node][i];
            int _w = w + p.second;
            if (_w < dist[p.first]) {
                pq.push({_w, p.first});
                dist[p.first] = _w;
            }
        }
    }
}

int main() {
    for (int N, A, B; scanf("%d%d%d", &N, &A, &B) != EOF;) {
        A--, B--;
        if (A < 0 or B < 0 or A >= N or B >= N) {
            printf("-1\n");
            continue;
        }

        vector<vector<pair<int, int> > > graph(N);
        rep(i, N) {
            int K, t;
            scanf("%d", &K);
            if (K > 0) {
                scanf("%d", &t);
                if (t >= 1 and t <= N) {
                    graph[i].push_back({t - 1, 0});
                }
                iter(k, 1, K) {
                    scanf("%d", &t);
                    if (t >= 1 and t <= N) {
                        graph[i].push_back({t - 1, 1});
                    }
                }
            }
        }

        vector<int> dist(N, INF);
        dijkstra(graph, dist, A);
        int r = dist[B];

        printf("%d\n", r < INF ? r : -1);
    }
}
