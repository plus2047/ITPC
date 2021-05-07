// ===== programing contest template ======

#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
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

typedef long long int lld;
#define frontof(c, k) (c).begin(), (c).begin() + (k)
#define allof(c) (c).begin(), (c).end()
#define len(container) int((container).size())
#define asmin(var, val) var = min(var, val)
#define asmax(var, val) var = max(var, val)
#define rep(i, N) for (int i = 0; i < int(N); ++i)
#define inv(i, N) for (int i = int(N) - 1; i >= 0; --i)

// #undef __LOCAL__

template <typename ITER>
void print(const char* note, ITER begin, ITER end) {
#ifdef __LOCAL__
    std::cout << note;
    for (; begin != end; begin++) std::cout << *begin << ' ';
    cout << endl;
#endif  // __LOCAL__
}

void print(const char* fmt, ...) {
#ifdef __LOCAL__
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
#endif  // __LOCAL__
}

// ========== contest code ==========
template <typename num_t>
inline num_t greatest_common_divisor(num_t a, num_t b) {
    while (b) {
        tie(a, b) = make_pair(b, a % b);
    }
    return a;
}

template <typename NUM>
struct SegmentTree {
    // a + b or max(a, b) or min(a, b)
    inline NUM func(NUM a, NUM b) { return greatest_common_divisor(a, b); }
    // VOID == 0 for sum, NUM_MAX for min, NUM_MIN for max
    const static NUM VOID = 0;

    int size;
    std::vector<NUM> tree;  // 1-indexed full tree
    inline NUM get(int idx) { return tree[idx + size]; }
    SegmentTree() : size(0) {}
    SegmentTree(int size) : size(size), tree(size * 2, VOID) {}
    SegmentTree(std::vector<NUM>& data) { init(data); }

    void init(std::vector<NUM>& data) {
        size = int(data.size());
        tree.resize(size * 2);
        std::copy(data.begin(), data.end(), tree.begin() + size);
        for (int i = size - 1; i > 0; i--) {
            tree[i] = func(tree[i * 2], tree[i * 2 + 1]);
        }
    }

    void update(int idx, NUM val) {
        idx += size;
        tree[idx] = val;
        while (idx != 0) {
            idx /= 2;
            tree[idx] = func(tree[2 * idx], tree[2 * idx + 1]);
        }
    }

    NUM query(int left, int right) {
        left += size, right += size;
        NUM res = VOID;
        while (left <= right) {
            if (left % 2 == 1) res = func(res, tree[left++]);
            if (right % 2 == 0) res = func(res, tree[right--]);
            left /= 2, right /= 2;
        }
        return res;
    }
};

lld N, Q;
typedef tuple<lld, lld, lld, lld> Edge;  // <child, lim, a, edgeIdx>
typedef tuple<lld, lld, lld> Query;      // <index, weight, result>
vector<vector<Edge> > G;
vector<vector<Query> > res;
SegmentTree<lld> st;
unordered_map<lld, lld> valIdx;
inline lld key(lld val, lld idx) { return (val << 30) | idx; }

void dfs(int parent, int node) {
    for (auto& v : res[node]) {
        lld index, weight, _;
        tie(index, weight, _) = v;
        get<2>(v) = st.query(0, valIdx[key(weight, N)]);
    }
    assert(node < G.size());
    for (auto& e : G[node]) {
        lld child, lim, a, eIdx;
        tie(child, lim, a, eIdx) = e;
        if (child == parent) continue;
        lld k = valIdx[key(lim, eIdx)];
        st.update(k, a);
        dfs(node, child);
        st.update(k, 0);
    }
}

void solve(int _turn) {
    scanf("%lld%lld", &N, &Q);

    vector<pair<lld, lld> > vals;
    G = vector<vector<Edge> >(N + 1);
    rep(i, N - 1) {
        lld f, t, l, a;
        scanf("%lld%lld%lld%lld", &f, &t, &l, &a);
        G[f].push_back({t, l, a, i});
        G[t].push_back({f, l, a, i});
        vals.push_back({l, i});
        // vals.push_back({l, N});
    }
    res = vector<vector<Query> >(N + 1);
    rep(i, Q) {
        lld c, w;
        scanf("%lld%lld", &c, &w);
        res[c].push_back({i, w, -1});
        vals.push_back({w, N});
    }
    sort(vals.begin(), vals.end());
    vals.resize(unique(allof(vals)) - vals.begin());
    valIdx.clear();
    for (int i = 0; i < len(vals); i++) {
        auto p = vals[i];
        valIdx[key(p.first, p.second)] = i;
    }

    st = SegmentTree<lld>(len(vals));
    dfs(-1, 1);

    printf("Case #%d:", _turn + 1);
    vector<Query> _res;
    for (auto& v : res) _res.insert(_res.end(), allof(v));
    sort(allof(_res));
    for (auto& q : _res) {
        lld i, w, r;
        tie(i, w, r) = q;
        if (i != -1) {
            printf(" %lld", r);
        }
    }
    printf("\n");
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
