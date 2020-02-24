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
struct MergeFindSet {
    std::vector<int> p;
    MergeFindSet(int n) : p(n) {
        for (int i = 0; i < n; i++) p[i] = i;
    }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void merge(int root, int child) { p[find(child)] = find(root); }
};

// ========== contest code ==========
vector<pair<int, int> > path;
int p, q;
char seen[32][32];

bool dfs(int i, int j) {
    if (i < 0 or j < 0 or i >= p or j >= q or seen[i][j]) return false;

    seen[i][j] = true;
    path.push_back({i, j});

    bool succ = len(path) == p * q or dfs(i - 1, j - 2) or dfs(i + 1, j - 2) or
                dfs(i - 2, j - 1) or dfs(i + 2, j - 1) or dfs(i - 2, j + 1) or
                dfs(i + 2, j + 1) or dfs(i - 1, j + 2) or dfs(i + 1, j + 2);

    seen[i][j] = false;
    if (not succ) path.pop_back();
    return succ;
}
// ===== kickstart template =====
int main() {
    int n;
    scanf("%d", &n);
    for (int t = 1; t <= n; t++) {
        scanf("%d%d", &p, &q);
        bool succ = false;
        for (int x = 0; x < p and not succ; x++) {
            for (int y = 0; y < q and not succ; y++) {
                memset(seen, 0, sizeof(seen));
                path.clear();
                succ = succ or dfs(x, y);
            }
        }

        printf("Scenario #%d:\n", t);
        if (succ) {
            rep(i, len(path)) {
                printf("%c%c", char(path[i].second + 'A'),
                       char(path[i].first + '1'));
            }
        } else {
            printf("impossible");
        }
        printf("\n\n");
    }
}
