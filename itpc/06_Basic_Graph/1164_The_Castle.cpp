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
int graph[64][64];
int M, N;
inline int id(int i, int j) { return i * N + j; }

// ===== kickstart template =====
int main() {
    while (scanf("%d%d", &M, &N) != EOF) {
        MergeFindSet mfs(M * N);
        rep(i, M) rep(j, N) {
            int val;
            scanf("%d", &val);
            if(j != 0 and not (val & 1)) mfs.merge(id(i, j), id(i, j - 1));
            if(i != 0 and not (val & 2)) mfs.merge(id(i, j), id(i - 1, j));
            if(j != N - 1 and not (val & 4)) mfs.merge(id(i, j), id(i, j + 1));
            if(i != M - 1 and not (val & 8)) mfs.merge(id(i, j), id(i + 1, j));
        }

        vector<int> cnt(M * N);
        int group = 0;
        rep(i, M) rep(j, N) {
            int _id = id(i, j);
            int root = mfs.find(_id);
            if(_id == root) group++;
            cnt[root]++;
        }
        int max_group = cnt.empty() ? 0 : *max_element(allof(cnt));
        printf("%d\n%d\n", group, max_group);
    }
}
