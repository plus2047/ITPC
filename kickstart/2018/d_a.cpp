// ===== programing contest template ======
// ===== using standrod: C++ 11 =====

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
#define len(c) int((c).size())
#define allof(container) (container).begin(), (container).end()
#define rep(i, N) for (int i = 0; i < int(N); i++)
#define repr(i, begin, end) for (int i = int(begin); i < int(end); i++)
#define repi(i, N) for (int i = int(N) - 1; i >= 0; i++)

template <int group = 16, typename ITER>
void show(const char* note, ITER begin, ITER end) {
#ifdef __LOCAL__
    printf("%s", note);
    int i = 1;
    for (; begin != end; i++) {
        std::cout << *(begin++) << ' ';
        if (i % group == 0) std::cout << std::endl;
    }
    if (i % group != 1) std::cout << std::endl;
#endif
}

// ===== personal contest template =====

// ========== contest code ==========
void solve(int _turn) {
    LL N, Odd, D;
    scanf("%lld%lld%lld", &N, &Odd, &D);
    LL X1, X2, A, B, C, M, L;
    scanf("%lld%lld%lld%lld%lld%lld%lld", &X1, &X2, &A, &B, &C, &M, &L);
    vector<LL> S(N), prefix_sum(N);
    S[0] = X1 + L, S[1] = X2 + L;
    prefix_sum[0] = S[0], prefix_sum[1] = S[0] + S[1];
    repr(i, 2, N) {
        LL Xi = (A * X2 + B * X1 + C) % M;
        S[i] = Xi + L;
        X1 = X2, X2 = Xi;
        prefix_sum[i] = prefix_sum[i - 1] + S[i];
    }
    // show("S:\n", allof(S));
    // show("prefix_sum:\n", allof(prefix_sum));

    const LL MIN_S = numeric_limits<LL>::min();
    LL max_s = MIN_S;

    int begin = 0, end = 0, odd_cnt = 0;
    multiset<LL> sums;
    LL bias = 0;
    while (begin < N) {
        while (!(odd_cnt == Odd and S[end] % 2) and end < N) {
            sums.insert(prefix_sum[end]);
            if (S[end] % 2) odd_cnt++;
            end++;
        }
        if (begin < end) {
            auto f = sums.upper_bound(D + bias);
            if (f != sums.begin()) max_s = max(max_s, *prev(f) - bias);
            sums.erase(sums.find(prefix_sum[begin]));
            if (S[begin] % 2) odd_cnt--;
        }

        bias = prefix_sum[begin];
        if (begin == end) end++;
        begin++;
    }

    if (max_s == MIN_S) {
        printf("Case #%d: IMPOSSIBLE\n", _turn);
    } else {
        printf("Case #%d: %lld\n", _turn, max_s);
    }
}

// ===== kickstart template =====
int main() {
#ifdef __LOCAL__  // define in build command.
    freopen("_kickstart.in", "r", stdin);
    freopen("_debug.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
