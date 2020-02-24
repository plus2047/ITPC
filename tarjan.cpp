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
const int maxm = 1024, maxn = 1024;
struct Edge {
    int u, v;
    Edge(int u = 0, int v = 0) : u(u), v(v) {}
} e[maxm];
int n, m, stamp, dfn[maxn], low[maxn], iscut[maxn], bccno[maxn];
int scnt, _stack[maxm], bcc_cnt;
vector<int> vec[maxn], bcc[maxn];

void tarjan(int index, int fa) {
    int child = 0, tmp;
    dfn[index] = low[index] = ++stamp;
    for (int i = 0; i < vec[index].size(); i++) {
        tmp = e[vec[index][i]].v;
        if (!dfn[tmp]) {
            _stack[++scnt] = vec[index][i], child++;
            tarjan(tmp, index);
            low[index] = min(low[index], low[tmp]);
            if (low[tmp] >= dfn[index]) {
                iscut[index] = 1;
                bcc[++bcc_cnt].clear();
                while (1) {
                    int num = _stack[scnt--];
                    if (bccno[e[num].u] != bcc_cnt) {
                        bcc[bcc_cnt].push_back(e[num].u);
                        bccno[e[num].u] = bcc_cnt;
                    }
                    if (bccno[e[num].v] != bcc_cnt) {
                        bcc[bcc_cnt].push_back(e[num].v);
                        bccno[e[num].v] = bcc_cnt;
                    }
                    if (e[num].u == index && e[num].v == tmp) break;
                }
            }
        } else if (dfn[tmp] < dfn[index] && tmp != fa) {
            _stack[++scnt] = vec[index][i];
            low[index] = min(low[index], dfn[tmp]);
        }
    }
    if (fa < 0 && child == 1) iscut[index] = 0;
}

void find_bcc() {
    // 割顶的bccno值无意义
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(iscut, 0, sizeof(iscut));
    memset(bccno, 0, sizeof(bccno));
    memset(bcc, 0, sizeof(bcc));
    stamp = scnt = bcc_cnt = 0;
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i, -1);
}

// ========== contest code ==========

void solve(int _turn) {
    e[0] = {0, 1};
    e[1] = {0, 3};
    vec[0] = {0, 1};
    e[2] = {1, 0};
    e[3] = {1, 2};
    vec[1] = {2, 3};
    e[4] = {2, 1};
    e[5] = {2, 3};
    vec[2] = {4, 5};
    e[6] = {3, 0};
    e[7] = {3, 2};
    e[8] = {3, 4};
    vec[3] = {6, 7, 8};
    e[9] = {4, 3};
    e[10] = {4, 5};
    e[11] = {4, 6};
    vec[4] = {9, 10, 11};
    e[12] = {5, 4};
    e[13] = {5, 6};
    vec[5] = {12, 13};
    e[14] = {6, 4};
    e[15] = {6, 5};
    vec[6] = {14, 15};
    n = 7;
    find_bcc();
    rep(i, bcc_cnt) {
        for(auto p: bcc[i + 1]) {
            printf("%d ", p);
        }
        printf("\n");
    }
}

// ===== kickstart template =====
int main() {
    int T = 1;
    // scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
