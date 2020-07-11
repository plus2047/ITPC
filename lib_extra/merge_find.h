#pragma once
#include <vector>

namespace contest {

struct CountMergeFindSet {
    std::vector<int> p;
    std::vector<int> cnt;
    CountMergeFindSet(int n) : p(n), cnt(n, 1) { init(); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    int count(int x) { return cnt[find(x)]; }
    bool merge(int root, int child) {
        int rr = find(root), rc = find(child);
        if (rr == rc) return false;
        p[rc] = rr;
        cnt[rr] += cnt[rc];
        cnt[rc] = 0;
        return true;
    }
    void init() {
        for (int i = 0; i < int(p.size()); i++) p[i] = i;
    }
};

}  // namespace contest
