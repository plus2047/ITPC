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
struct IntervalTreeNode {
    IntervalTreeNode *left, *right;
    int first, last, depth;
    IntervalTreeNode(int first, int last)
        : first(first), last(last), depth(0), left(0), right(0) {}
};

inline int nodeLen(IntervalTreeNode* node) {
    return node ? node->last - node->first + 1 : 0;
}

inline void createChilds(IntervalTreeNode* node) {
    int nodeMid = (node->first + node->last) / 2;
    if (not node->left) {
        node->left = new IntervalTreeNode(node->first, nodeMid);
        node->right = new IntervalTreeNode(nodeMid + 1, node->last);
    }
}

void insert(IntervalTreeNode* node, int first, int last, int delta) {
    if (first > node->last or last < node->first) return;
    if (first <= node->first and last >= node->last) {
        node->depth += delta;
    } else {
        createChilds(node);
        insert(node->left, first, last, delta);
        insert(node->right, first, last, delta);
    }
}

int totalLen(IntervalTreeNode* node) {
    if (not node) return 0;
    if (node->depth > 0) return nodeLen(node);
    return totalLen(node->left) + totalLen(node->right);
}

int count(IntervalTreeNode* node, int first, int last, int depth) {
    if (node->first > last or node->last < first or depth < 0) {
        return 0;
    } else if (not node->left) {
        if (first <= node->first and last >= node->last and
            depth == node->depth) {
            return nodeLen(node);
        } else {
            return 0;
        }
    } else {
        depth -= node->depth;
        return count(node->left, first, last, depth) +
               count(node->right, first, last, depth);
    }
}

void solve(int _turn) {
    LL N, L1, R1, A, B, C1, C2, M;
    scanf("%lld%lld%lld%lld%lld%lld%lld%lld", &N, &L1, &R1, &A, &B, &C1, &C2,
          &M);
    typedef pair<LL, LL> Interval;
    vector<Interval> intervals;
    LL x = L1, y = R1;
    rep(i, N) {
        intervals.push_back({min(x, y), max(x, y)});
        LL _x = (A * x + B * y + C1) % M;
        LL _y = (A * y + B * x + C2) % M;
        x = _x, y = _y;
    }
    const LL P_MIN = 0, P_MAX = 1E9 + 7;
    IntervalTreeNode* root = new IntervalTreeNode(P_MIN, P_MAX);

    for (Interval& interval : intervals) {
        insert(root, interval.first, interval.second, 1);
    }

    LL maxCover = 0;
    for (Interval& interval : intervals) {
        LL cover = count(root, interval.first, interval.second, 1);
        asmax(maxCover, cover);
    }

    LL total = totalLen(root);

    printf("Case #%d: %lld\n", _turn, total - maxCover);
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
