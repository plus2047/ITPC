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
// codeforces 1495B
// https://codeforces.com/problemset/problem/1495/B

template <typename NUM>
struct SegmentTree {
    // a + b or max(a, b) or min(a, b)
    inline NUM func(NUM a, NUM b) { return max(a, b); }
    // VOID == 0 for sum, NUM_MAX for min, NUM_MIN for max
    const static NUM VOID = 0;

    int size;
    std::vector<NUM> tree;  // 1-indexed full tree
    inline NUM get(int idx) { return tree[idx + size]; }
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

void solve(int _turn) {
    lld n;
    scanf("%lld", &n);
    vector<lld> P(n);
    rep(i, n) scanf("%lld", &P[i]);
    vector<lld> left(n, 1), right(n, 1);
    rep(i, n) if (i != 0 and P[i] > P[i - 1]) left[i] = left[i - 1] + 1;
    inv(i, n) if (i != n - 1 and P[i] > P[i + 1]) right[i] = right[i + 1] + 1;
    SegmentTree<lld> sleft(left), sright(right);

    // print("left : ", allof(left));
    // print("right: ", allof(right));

    lld res = 0;
    rep(i, n) {
        bool in_valid = false;
        if (left[i] == right[i]) {
            if (left[i] % 2) {
                in_valid = false;
            } else {
                in_valid = true;
            }
        } else {
            in_valid = true;
        }

        lld pathSize = max(left[i], right[i]);
        lld _left = i - left[i], _right = i + right[i];
        lld otherMaxSize =
            max({sleft.query(0, _left), sright.query(0, _left),
                 sleft.query(_right, n - 1), sright.query(_right, n - 1)});

        bool out_valid = otherMaxSize >= pathSize;

        if (not in_valid and not out_valid) {
            print("pos: %d, left: %lld, right: %lld, in: %d, out: %d\n", i,
                  left[i], right[i], int(in_valid), int(out_valid));
            res++;
        }
    }
    printf("%lld\n", res);
}

int main() {
    int T = 1;
    // scanf("%d", &T);
    rep(t, T) { solve(t); }
}
