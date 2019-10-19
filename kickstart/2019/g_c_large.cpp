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
template <typename num_t>
num_t quick_pow(num_t base, int n) {
    num_t res = 1;
    while (n) {
        if (n % 2) res *= base;
        base *= base;
        n /= 2;
    }
    return res;
}

// ========== contest code ==========
const int N_MAX = 32;
vector<pair<LL, LL>> ab(N_MAX);
vector<LL> preA(N_MAX), preB(N_MAX);
vector<LL> pow3(N_MAX);
LL res = 0;
LL N, H;

bool comp_sum(const pair<LL, LL>& a, const pair<LL, LL>& b) {
    return a.first + a.second > b.first + b.second;
}

void dfs(LL idx, LL targetA, LL targetB) {
    if (targetA <= 0 and targetB <= 0) {
        res += pow3[N - idx];
        return;
    }
    if(idx >= N) {
        return;
    }
    if (targetA > preA[N - 1] - (idx == 0 ? 0 : preA[idx - 1]) or
        targetB > preB[N - 1] - (idx == 0 ? 0 : preB[idx - 1])) {
        return;
    }
    dfs(idx + 1, targetA - ab[idx].first, targetB);
    dfs(idx + 1, targetA, targetB - ab[idx].second);
    dfs(idx + 1, targetA - ab[idx].first, targetB - ab[idx].second);
}

void solve(int _turn) {
    scanf("%lld%lld", &N, &H);
    rep(i, N) scanf("%lld", &ab[i].first);
    rep(i, N) scanf("%lld", &ab[i].second);
    sort(frontof(ab, N), comp_sum);

    preA[0] = ab[0].first;
    preB[0] = ab[0].second;
    repr(i, 1, N) {
        preA[i] = preA[i - 1] + ab[i].first;
        preB[i] = preB[i - 1] + ab[i].second;
    }

    res = 0;
    dfs(0, H, H);

    printf("Case #%d: %lld\n", _turn, res);
}

// ===== kickstart template =====
int main() {
    pow3[0] = 1;
    repr(i, 1, N_MAX) pow3[i] = pow3[i - 1] * 3;

    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
