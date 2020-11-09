#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
typedef long long int lld;

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

lld N, M, K;
lld L, R, W, idx;
typedef tuple<lld, lld, lld, lld> T4;

inline bool check(lld V, vector<T4>& seg, vector<lld>& res) {
    fill(res.begin(), res.end(), 0);
    FenwickTree<lld> ft(M);
    priority_queue<tuple<lld, lld, lld> > pq;  // <R, W, idx>
    lld cost = 0;

    for (lld x = 0, i = 0; x < M and cost <= K; x++) {
        while (i < N and get<0>(seg[i]) <= x) {
            tie(L, R, W, idx) = seg[i++];
            pq.push({R, W, idx});
        }
        lld curr = ft.prefix_sum(M) - ft.prefix_sum(x - 1);
        while (curr < V) {
            if (pq.empty()) return false;
            tie(R, W, idx) = pq.top(), pq.pop();
            if (R < x) return false;

            lld delta = min(W, V - curr);
            curr += delta;
            cost += delta;
            res[idx] += delta;
            ft.add(R, delta);
            if (delta < W) {
                pq.push({R, W - delta, idx});
            }
        }
    }

    return cost <= K;
}

int main() {
    while (scanf("%lld%lld%lld", &N, &M, &K) != EOF) {
        vector<tuple<lld, lld, lld, lld> > seg(N);  // <L, R, W, idx>
        for (lld i = 0; i < N; i++) {
            scanf("%lld%lld%lld", &L, &R, &W);
            seg[i] = {L, R - 1, W, i};
        }
        sort(seg.begin(), seg.end());

        vector<lld> res(N);
        lld left = 0, right = INT64_MAX;
        while (left < right) {
            lld mid = right - (right - left) / 2;
            if (check(mid, seg, res)) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }

        check(left, seg, res);
        printf("%lld\n", left);
        for (int i = 0; i < N; i++) {
            printf("%lld ", res[i]);
        }
        printf("\n");
    }
}
