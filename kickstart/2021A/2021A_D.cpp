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

struct MergeFindSet {
    std::vector<int> p;
    MergeFindSet(int n) : p(n) { init(); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    void merge(int root, int child) { p[find(child)] = find(root); }
    void init() {
        for (int i = 0; i < int(p.size()); i++) p[i] = i;
    }
};

// ========== contest code ==========
// bool valid(MergeFindSet& mfs, vector<int>& countR, vector<int>& countC, int g) {
//     lld N = countR.size();
//     lld eqCount = 0, voidCount = 0;
//     bool oneR = false, oneC = false;
//     rep(i, N) {
//         if(mfs.find(i) == g) {
//             voidCount += countR[i];
//             if(countR[i] == 1) oneR = true;
//             eqCount++;
//         }
//         if(mfs.find(N + i) == g) {
//             if(countC[i] == 1) oneC = true;
//             eqCount++;
//         }
//     }
//     return eqCount >= voidCount and (oneR or oneC);
// }


void solve(int _turn) {
    lld N;
    scanf("%lld", &N);
    lld A[N][N], B[N][N];
    rep(i, N) rep(j, N) scanf("%lld", &A[i][j]);
    rep(i, N) rep(j, N) scanf("%lld", &B[i][j]);
    lld sumR[N], sumC[N];
    rep(i, N) scanf("%lld", &sumR[i]);
    rep(i, N) scanf("%lld", &sumC[i]);

    vector<tuple<lld, int, int> > costs;
    lld total = 0;
    rep(i, N) rep(j, N) {
        if (B[i][j]) {
            costs.push_back({B[i][j], i, j});
            total += B[i][j];
        }
    }

    sort(costs.begin(), costs.end());
    reverse(costs.begin(), costs.end());

    lld get = 0;
    vector<int> countR(N), countC(N);
    MergeFindSet mfs(N * 2);

    for (auto& t : costs) {
        lld c;
        int i, j;
        tie(c, i, j) = t;

        auto _mfs = mfs;
        _mfs.merge(i, N + j);
        countR[i]++;
        countC[j]++;
        // if(valid(_mfs, countR, countC, _mfs.find(i))) {
        if(mfs.find(i) != mfs.find(N + j)) {
            mfs.merge(i, N + j);
            get += c;
        } else {
            // countR[i]--;
            // countC[j]--;
        }
    }
    lld res = total - get;

    printf("Case #%d: %lld\n", _turn + 1, res);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
