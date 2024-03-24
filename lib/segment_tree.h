#pragma once
#include <cassert>
#include <vector>

namespace contest {

// compare Range Tree & Fenwick Tree:
// range tree is easier to understand,
// it can be used for range sum & min & max.
// Fenwick tree is easier to implement,
// and it's data structure is more clear
// it can be extend to high dimensions easily.

// careful: FinwickTree is 1-indexed.
// but this implement will always plus one on the input index.
// so we can use this as 0-indexed.
template <typename NUM>
struct FenwickTree {
    std::vector<NUM> tree;
    const int SIZE;
    FenwickTree(int size) : SIZE(size + 1), tree(size + 2, 0) {}

    inline void add(int idx, NUM val) {
        for (int k = idx + 1; k <= SIZE; k += (k & -k)) tree[k] += val;
    }

    inline NUM prefix_sum(int last) {
        NUM res = 0;
        for (int k = last + 1; k > 0; k -= (k & -k)) res += tree[k];
        return res;
    }
};

template <typename NUM>
struct FenwickTree2D {
    std::vector<std::vector<NUM> > tree;
    int SIZE0, SIZE1;
    FenwickTree2D(int size0, int size1)
        : SIZE0(size0 + 1),
          SIZE1(size1 + 1),
          tree(size0 + 2, std::vector<NUM>(size1 + 2)) {}

    inline void add(int idx0, int idx1, NUM val) {
        for (int i = idx0 + 1; i <= SIZE0; i += (i & -i)) {
            for (int j = idx1 + 1; j <= SIZE1; j += (j & -j)) {
                tree[i][j] += val;
            }
        }
    }

    inline NUM prefix_sum(int last0, int last1) {
        NUM res = 0;
        for (int i = last0 + 1; i > 0; i -= (i & -i)) {
            for (int j = last1 + 1; j > 0; j -= (j & -j)) {
                res += tree[i][j];
            }
        }
        return res;
    }
};

template <typename NUM>
struct SegmentTree {
    // a + b or max or min or ^ or any opt support associative property
    inline NUM func(NUM a, NUM b) { return a + b; }
    // VOID == 0 for sum, NUM_MAX for min, NUM_MIN for max, etc
    constexpr static NUM VOID = 0;

    int size;
    std::vector<NUM> tree;  // 1-indexed full tree
    SegmentTree(std::vector<NUM>& data) { init(data); }

    SegmentTree(int size) : size(size), tree(size * 2, VOID) {}
    // SegmentTree(int size) { this->size = size, this->tree.resize(size * 2); }

    void init(std::vector<NUM>& data) {
        size = int(data.size());
        tree.resize(size * 2);
        std::copy(data.begin(), data.end(), tree.begin() + size);
        for (int i = size - 1; i > 0; i--) {
            tree[i] = func(tree[i * 2], tree[i * 2 + 1]);
        }
    }

    // set & get index mast be in [0, size)
    inline NUM get(int idx) { return tree[idx + size]; }
    void set(int idx, NUM val) {
        idx += size;
        tree[idx] = val;
        while (idx > 1) {
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

}  // namespace contest
