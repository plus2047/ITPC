// ===== programing contest template ======
// ===== using standrod: C++ 11 =====

#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>

#include <array>
#include <bitset>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// ===== personal contest env =====

typedef long long int LL;
#define G(_tuple, num) (get<num>(_tuple))
#define len(container) int((container).size())
#define allof(c) (c).begin(), (c).end()
#define frontof(c, k) (c).begin(), (c).begin() + (k)
#define rep(i, N) for (int i = 0; i < int(N); i++)
#define repr(i, begin, end) for (int i = int(begin); i < int(end); i++)
#define repi(i, N) for (int i = int(N) - 1; i >= 0; i--)
#define asmax(m, update) \
    if (m < update) m = update;
#define asmin(m, update) \
    if (m > update) m = update;
#define vec2d(type, name, m, n, v) \
    vector<vector<type>> name = vector<vector<type>>(m, vector<type>(n, v))

template <int group = 20, typename ITER>
void show(const char* note, ITER begin, ITER end) {
#ifdef __LOCAL__
    cout << note;
    for (int i = 1; begin != end; i++) {
        std::cout << *(begin++) << ' ';
        if (i % group == 0 or begin == end) std::cout << std::endl;
    }
#endif  // __LOCAL__
}

#ifdef __LOCAL__
std::clock_t _t0 = 0;
void timer_begin() { _t0 = clock(); }
void timer_end(const char* note) {
    double delta = double(clock() - _t0) / CLOCKS_PER_SEC;
    printf("%s cost: %lf sec.\n", note, delta);
}
#else
#define timer_begin() (void(0))
#define timer_end(note) (void(0))
#endif  // __LOCAL__

// ===== personal contest template =====

// ========== contest code ==========
const LL INF = LL(UINT_MAX) * 2, NEG_INF = LL(INT_MIN) * 4;

void solve(int _turn) {
    int V;
    scanf("%d", &V);
    vector<int> B(V), X(V - 1), Y(V - 1);
    rep(i, V) {
        scanf("%d", &B[i]);
        B[i];
    }
    rep(i, V - 1) {
        scanf("%d%d", &X[i], &Y[i]);
        X[i]--;
        Y[i]--;
    }

    vector<vector<int>> graph(V);

    vector<int> edges_num(V);
    rep(i, V - 1) {
        edges_num[X[i]]++;
        edges_num[Y[i]]++;
        graph[X[i]].push_back(Y[i]);
        graph[Y[i]].push_back(X[i]);
    }

    queue<int> que;
    rep(i, V) {
        if (edges_num[i] == 1) {
            que.push(i);
        }
    }
    vector<int> order;
    while (len(que)) {
        int node = que.front();
        que.pop();
        order.push_back(node);
        for (int neighbor : graph[node]) {
            edges_num[neighbor]--;
            if (edges_num[neighbor] == 1) {
                que.push(neighbor);
            }
        }
    }
    // printf("order size: %d\n", len(order));
    // show("order: ", allof(order));

    vector<LL> on(V, -1), light(V, -1), dark(V, -1);
    for (int node : order) {
        on[node] = B[node];     // node on
        light[node] = B[node];  // node off but CAN BE lighted
        dark[node] = 0;         // node off but CANNOT BE lighted

        LL min_delta_for_light = INF;
        bool has_nei = false;
        
        for (int nei : graph[node]) {
            if (dark[nei] == -1) {
                continue;
            }
            has_nei = true;

            on[node] += max({on[nei], light[nei], dark[nei] + B[nei]});
 
            light[node] += max({on[nei], light[nei], dark[nei]});
            LL delta = max(light[nei], dark[nei]) - on[nei];
            if (delta < min_delta_for_light) {
                min_delta_for_light = delta;
            }
 
            dark[node] += max(light[nei], dark[nei]);
        }
        if (min_delta_for_light != INF and min_delta_for_light > 0) {
            light[node] -= min_delta_for_light;
        }
        if (!has_nei) {
            light[node] = NEG_INF;
        }
    }
    // show("on: ", allof(on));
    // show("light: ", allof(light));
    // show("dark: ", allof(dark));

    int last_node = order.back();
    printf("Case #%d: %lld\n", _turn,
           max({on[last_node], light[last_node], dark[last_node]}));
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
