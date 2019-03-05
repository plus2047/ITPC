#pragma once
#include <cassert>
#include <vector>

namespace contest {

// compare Range Tree & Fenwick Tree:
// range tree is easier to understand,
// it can be used for range sum & min & max.
// Fenwick tree is easier to implement,
// and it's data structure is more clear
// it can be extend to high dimensions.

template <typename NUM>
struct SegmentTree {
    // range tree can be used to get range max or min or sum.
    // if necessary modify this function. default: sum
    inline NUM func(NUM a, NUM b) { return a + b; }
    // VOID is a NUM s.t. func(VOID, x) == x
    // VOID == 0 for sum, NUM_MAX for min, NUM_MIN for max
    const NUM VOID = 0;

    // imply as a full tree.
    // tree[0] is never used.
    // tree begin at tree[1]
    const int SIZE;
    std::vector<NUM> tree;

    SegmentTree(int size) : SIZE(size) {
        assert(SIZE >= 0);
        tree.resize(SIZE * 2);
        std::fill(tree.begin(), tree.end(), VOID);
    }

    // O(n) init from a vector:
    void init(std::vector<NUM>& data) {
        assert(int(data.size()) <= SIZE);
        std::fill(tree.begin(), tree.end(), VOID);
        std::copy(data.begin(), data.end(), tree.begin() + SIZE);
        for (int i = SIZE - 1; i > 0; i--) {
            tree[i] = func(tree[i * 2], tree[i * 2 + 1]);
        }
    }

    inline NUM get(int idx) { return tree[idx + SIZE]; }
    
    void update(int idx, int val) {
        assert(idx >= 0 and idx < SIZE);
        idx += SIZE;
        tree[idx] = val;
        while (idx != 0) {
            idx /= 2;
            tree[idx] = func(tree[2 * idx], tree[2 * idx + 1]);
        }
    }
    
    NUM query(int first, int last) {
        assert(first <= last and first >= 0 and last < SIZE);
        first += SIZE, last += SIZE;
        NUM res = VOID;
        while (first <= last) {
            if (first % 2 == 1) res += tree[first++];
            if (last % 2 == 0) res += tree[last--];
            first /= 2, last /= 2;
        }
        return res;
    }
};

template <typename NUM>
struct FenwickTree {
    std::vector<NUM> tree;
    const int SIZE;
    // user index range: [0, SIZE]
    // tree index range: [1, SIZE + 1]
    FenwickTree(int size) : SIZE(size + 1), tree(size + 2, 0) {}

    inline void add(int idx, NUM val) {
        assert(idx >= 0 and idx <= SIZE);
        for (int k = idx + 1; k <= SIZE; k += (k & -k)) tree[k] += val;
    }

    inline NUM prefix_sum(int last) {
        if (last < 0) return 0;
        if (last > SIZE) last = SIZE;
        NUM res = 0;
        for (int k = last + 1; k > 0; k -= (k & -k)) res += tree[k];
        return res;
    }
};

template <typename NUM>
struct FenwickTree2D {
    std::vector<std::vector<NUM>> tree;
    int SIZE0, SIZE1;
    FenwickTree2D(int size0, int size1)
        : SIZE0(size0 + 1),
          SIZE1(size1 + 1),
          tree(size0 + 2, std::vector<NUM>(size1 + 2)) {}

    inline void add(int idx0, int idx1, NUM val) {
        assert(idx0 >= 0 and idx0 <= SIZE0);
        assert(idx1 >= 0 and idx1 <= SIZE1);
        for (int i = idx0 + 1; i <= SIZE0; i += (i & -i)) {
            for (int j = idx1 + 1; j <= SIZE1; j += (j & -j)) {
                tree[i][j] += val;
            }
        }
    }

    inline NUM prefix_sum(int last0, int last1) {
        if (last0 < 0 or last1 < 0) return 0;
        if (last0 > SIZE0) last0 = SIZE0;
        if (last1 > SIZE1) last1 = SIZE1;
        NUM res = 0;
        for (int i = last0 + 1; i > 0; i -= (i & -i)) {
            for (int j = last1 + 1; j > 0; j -= (j & -j)) {
                res += tree[i][j];
            }
        }
        return res;
    }
};
}  // namespace contest
