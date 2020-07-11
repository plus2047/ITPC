#pragma once
#include <vector>

namespace contest {

struct MergeFindSet {
    std::vector<int> p;
    MergeFindSet(int n) : p(n) { init(); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void merge(int root, int child) { p[find(child)] = find(root); }
    void init() {
        for (int i = 0; i < int(p.size()); i++) p[i] = i;
    }
};

}  // namespace contest
