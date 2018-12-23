#ifndef __MERGE_FIND_SET_H__
#define __MERGE_FIND_SET_H__
#include <vector>

template <typename index_t = int>
struct MergeFindSet {
    std::vector<index_t> p;
    MergeFindSet(index_t n) {
        p.resize(n);
        for (index_t i = 0; i < n; i++) p[i] = i;
    }
    index_t find(index_t x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void merge(index_t x, index_t y) { p[find(y)] = find(x); }
};

#endif  // define __MERGE_FIND_SET_H__
