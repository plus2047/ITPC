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
#define inv(i, N) for (int i = int(N) - 1; i >= 0; --i)

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
const int CHAR_N = 26;
struct TrieNode {
    TrieNode* child[CHAR_N];
    int path_cnt = 0, leaf_cnt = 0;
    TrieNode() { std::fill(child, child + CHAR_N, nullptr); }
};

void insert(TrieNode* node, std::string& str) {
    for (int i = 0; i < int(str.size()); i++) {
        node->path_cnt++;
        int ci = str[i] - 'A';  // CHECK THIS!
        if (not node->child[ci]) {
            node->child[ci] = new TrieNode();
        }
        node = node->child[ci];
    }
    node->path_cnt++;
    node->leaf_cnt++;
}

int N, K;

int total;
int dfs(TrieNode* node, int depth) {
    if (not node or node->path_cnt < K) return 0;
    int sub_cost = 0;
    rep(i, CHAR_N) { sub_cost += dfs(node->child[i], depth + 1); }
    int r = node->path_cnt - sub_cost;
    total += depth * (r / K);
    return node->path_cnt - r % K;
}

// ========== contest code ==========
void solve(int _turn) {
    cin >> N >> K;
    TrieNode* root = new TrieNode();
    string inp;
    rep(i, N) {
        cin >> inp;
        insert(root, inp);
    }
    total = 0;
    dfs(root, 0);

    printf("Case #%d: %d\n", _turn + 1, total);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
