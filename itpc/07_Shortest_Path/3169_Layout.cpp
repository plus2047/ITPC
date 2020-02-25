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
const int N_MAX = 102400;
int n, ml, md;
int tot, to[N_MAX], nex[N_MAX], weight[N_MAX], head[N_MAX];
int vis[N_MAX], dis[N_MAX], cnt[N_MAX];

void add(int u, int v, int w) {
    to[tot] = v;
    weight[tot] = w;
    nex[tot] = head[u];
    head[u] = tot++;
}

bool spfa(int start = 1) {
    memset(vis, 0, sizeof(vis));
    memset(dis, 0x3f, sizeof(dis));
    dis[start] = 0;
    vis[start] = 1;
    cnt[start]++;
    queue<int> que;
    que.push(start);
    while (que.size()) {
        int now = que.front();
        que.pop();
        vis[now] = 0;
        for (int i = head[now]; i != -1; i = nex[i]) {
            if (dis[to[i]] > dis[now] + weight[i]) {
                dis[to[i]] = dis[now] + weight[i];
                if (vis[to[i]]) continue;
                if (++cnt[to[i]] > n) return false;
                que.push(to[i]);
                vis[to[i]] = 1;
            }
        }
    }
    return true;
}

// ===== kickstart template =====
int main() {
    while (scanf("%d%d%d", &n, &ml, &md) != EOF) {
        tot = 0;
        memset(head, -1, sizeof(head));
        int u, v, w;
        rep(i, ml) {
            scanf("%d%d%d", &u, &v, &w);
            add(u, v, w);
        }
        rep(i, md) {
            scanf("%d%d%d", &u, &v, &w);
            add(v, u, -w);
        }
        rep(i, n) { add(i + 1, i, 0); }
        bool succ = spfa();
        int res = 0;
        if (succ == false) {
            res = -1;
        } else if (dis[n] >= 0x3f3f3f3f) {
            res = -2;
        } else {
            res = dis[n];
        }
        printf("%d\n", res);
    }
}