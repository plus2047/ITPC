#pragma once
#include <vector>

namespace contest {

struct MergeFindSet {
    std::vector<int> p;
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void merge(int root, int child) { p[find(child)] = find(root); }
    MergeFindSet(int n) : p(n) {
        for (int i = 0; i < n; i++) p[i] = i;
    }
};

struct MergeBigger {
    std::vector<int> p;
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void merge(int x, int y) {
        int rx = find(x), ry = find(y);
        p[std::min(rx, ry)] = std::max(rx, ry);
    }
    MergeBigger(int n) : p(n) {
        for (int i = 0; i < n; i++) p[i] = i;
    }
};

}  // namespace contest
