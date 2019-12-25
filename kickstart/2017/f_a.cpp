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

typedef long long int lld;
#define len(container) int((container).size())
#define allof(c) (c).begin(), (c).end()
#define frontof(c, k) (c).begin(), (c).begin() + (k)
#define rep(i, N) for (int i = 0; i < int(N); ++i)
#define range(i, left, right) for (int i = int(left); i <= int(right); ++i)
#define irange(i, left, right) for (int i = int(right); i >= int(left); --i)

#undef __LOCAL__

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
struct FenwickTree {
    vector<int> tree;
    int size;
    FenwickTree(int size) : size(size), tree(size + 1) {}

    void set(int idx, int delta) {
        idx += 1;
        while (idx <= size) {
            tree[idx] += delta;
            idx += idx & -idx;
        }
    }

    int prefix(int idx) {
        idx += 1;
        int total = 0;
        while (idx > 0) {
            total += tree[idx];
            idx -= idx & -idx;
        }
        return total;
    }
};

// ========== contest code ==========

void solve(int _turn) {
    int N;
    scanf("%d", &N);
    vector<int> nums(N);
    rep(i, N) { scanf("%d", &nums[i]); }
    FenwickTree fenwick(N);
    vector<int> inv_idx(N + 1);
    rep(i, N) { inv_idx[nums[i]] = i; }

    int left = 1, right = N;
    while (left != right) {
        bool succ = false;
        for (int n : {left, right}) {
            int idx = inv_idx[n];
            int order = idx - fenwick.prefix(idx);
            if (order == (right - left) / 2) {
                succ = true;
                fenwick.set(idx, 1);
                if (n == left) {
                    left++;
                } else {
                    right--;
                }
                break;
            }
        }
        if (not succ) break;
    }

    printf("Case #%d: %s\n", _turn, left == right ? "YES" : "NO");
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
