// ===== programing contest template ======
// ===== using standrod: C++ 11 =====

// must read the analysis!!!

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
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// ===== personal contest env =====

typedef long long int LL;
#define G(_tuple, num) (get<num>(_tuple))
#define len(container) int((container).size())
#define allof(c) (c).begin(), (c).end()
#define frontof(c, k) (c).begin(), (c).begin() + (k)
#define rep(i, N) for (int i = 0; i < int(N); i++)
#define repr(i, begin, end) for (int i = int(begin); i < int(end); i++)
#define repi(i, N) for (int i = int(N) - 1; i >= 0; i--)
#define asmax(m, update) \
    if (m < update) m = update;
#define asmin(m, update) \
    if (m > update) m = update;

template <int group = 20, typename ITER>
void show(const char* note, ITER begin, ITER end) {
#ifdef __LOCAL__
    cout << note;
    for (int i = 1; begin != end; i++) {
        std::cout << *(begin++) << ' ';
        if (i % group == 0 or begin == end) std::cout << std::endl;
    }
#endif  // __LOCAL__
}

#ifdef __LOCAL__
std::clock_t _t0 = 0;
void timer_begin() { _t0 = clock(); }
void timer_end(const char* note) {
    double delta = double(clock() - _t0) / CLOCKS_PER_SEC;
    printf("%s cost: %lf sec.\n", note, delta);
}
#else
#define timer_begin() (void(0))
#define timer_end(note) (void(0))
#endif  // __LOCAL__

// ===== personal contest template =====
int dp[128][128][128];  // (left, right, k)
int N, K;
int A[128];
map<int, int> cnt;

int cal(int left, int right, int k) {
    if (dp[left][right][k] != -1) return dp[left][right][k];

    int res;
    if (left == right) {
        res = 0;
    } else if (k == 0) {
        cnt.clear();
        for (int i = left; i <= right; i++) cnt[A[i]]++;
        int maxVal = 0;
        for (auto& p : cnt) asmax(maxVal, p.second);
        res = right - left + 1 - maxVal;
    } else {
        res = cal(left, right, 0);
        if(k != 0) {
            for (int mid = left; mid < right; mid++) {
                if (mid != right and A[mid] == A[mid + 1]) continue;
                int r = cal(left, mid, 0) + cal(mid + 1, right, k - 1);
                asmin(res, r);
            }
        }
    }

    // printf("left: %d, right: %d, K: %d, res: %d\n", left, right, K, res);
    return dp[left][right][k] = res;
}

// ========== contest code ==========
void solve(int _turn) {
    scanf("%d%d", &N, &K);
    rep(i, N) scanf("%d", &A[i]);

    rep(i, N) rep(j, N) rep(k, K + 1) dp[i][j][k] = -1;

    printf("Case #%d: %d\n", _turn, cal(0, N - 1, K));
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
