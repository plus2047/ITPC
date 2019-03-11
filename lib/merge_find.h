#pragma once
#include <vector>

namespace contest {
struct MergeFindSet {
    std::vector<int> p;
    MergeFindSet(int n) : p(n) {
        for (int i = 0; i < n; i++) p[i] = i;
    }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void merge(int root, int child) { p[find(child)] = find(root); }
};

struct CountMergeFindSet {
    std::vector<int> p;
    std::vector<int> cnt;
    CountMergeFindSet(int n) : p(n), cnt(n, 1) {
        for (int i = 0; i < n; i++) p[i] = i;
    }
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
};
}  // namespace contest
