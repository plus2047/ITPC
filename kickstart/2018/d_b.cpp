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
void create(vector<LL>& vec, int num) {
    LL A, B, C, M;
    scanf("%lld%lld%lld%lld%lld%lld", &vec[0], &vec[1], &A, &B, &C, &M);
    repr(i, 2, num) { vec[i] = (A * vec[i - 1] + B * vec[i - 2] + C) % M + 1; }
    // show("", allof(vec));
}
void solve(int _turn) {
    int N, K;
    scanf("%d%d", &N, &K);
    vector<LL> p(N), h(N), x(K), y(K);
    create(p, N), create(h, N), create(x, K), create(y, K);

    vector<pair<LL, int>> left(N);
    vector<LL> right(N), _right(N), _left(N);
    rep(i, N) {
        left[i] = {p[i] - h[i], i};
        right[i] = p[i] + h[i];
    }
    sort(allof(left));

    _right[0] = right[left[0].second];
    _left[0] = left[0].first;
    repr(i, 1, N) {
        _right[i] = max(_right[i - 1], right[left[i].second]);
        _left[i] = left[i].first;
    }
    // show("_left:\n", allof(_left));
    // show("_right:\n", allof(_right));

    int cnt = 0;
    rep(i, K) {
        LL left_ = x[i] - y[i], right_ = x[i] + y[i];
        int idx = upper_bound(allof(_left), left_) - _left.begin() - 1;
        // printf("idx: %d\n", idx);
        if (idx >= 0 and _right[idx] >= right_) cnt++;
    }
    printf("Case #%d: %d\n", _turn, cnt);
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
