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
#include <bitset>
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
#define vec2d(type, name, m, n, v) \
    vector<vector<type>> name = vector<vector<type>>(m, vector<type>(n, v))

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

// ========== contest code ==========
inline LL comb(LL val, LL num) {
    LL res = 1;
    rep(i, num) { res *= (val - i); }
    rep(i, num) { res /= (i + 1); }
    return res;
}

inline LL count_less_equal(vector<pair<LL, LL>>& cnt, vector<LL>& prefix,
                           LL val) {
    if (val < cnt[0].first) return 0;
    int idx = lower_bound(allof(cnt), make_pair(val + 1, 0LL)) - cnt.begin() - 1;
    return prefix[idx];
}

inline LL count(vector<pair<LL, LL>>& cnt, vector<LL>& prefix, LL left,
                LL right) {
    LL res = count_less_equal(cnt, prefix, right) - count_less_equal(cnt, prefix, left - 1);
    return res;
}

void solve(int _turn) {
    LL N;
    scanf("%lld", &N);
    unordered_map<LL, LL> cnt_map;
    rep(i, N) {
        LL num;
        scanf("%lld", &num);
        cnt_map[num]++;
    }

    vector<pair<LL, LL>> cnt(allof(cnt_map));
    sort(allof(cnt));

    LL val_num = len(cnt);
    vector<LL> prefix(val_num);

    prefix[0] = cnt[0].second;
    repr(i, 1, val_num) { prefix[i] = cnt[i].second + prefix[i - 1]; }

    LL total = 0;

    // with three edges equal
    rep(i, val_num) {
        LL diff_max = cnt[i].first * 3 - 1;
        LL n = cnt[i].second;
        total += comb(n, 3) * (count(cnt, prefix, 0, diff_max) - n);
    }

    // with only two edges equal
    rep(i, val_num) {
        LL val = cnt[i].first, num = cnt[i].second;
        if (num < 2) continue;
        LL t = comb(num, 2);
        LL diff_max = val * 2 - 1;
        rep(left, val_num) {
            if (left == i) continue;
            LL left_val = cnt[left].first;
            LL left_num = cnt[left].second;
            LL right_max = left_val + diff_max;
            LL right_num = count(cnt, prefix, left_val + 1, right_max);
            if (left_val <= val and val <= right_max) {
                right_num -= num;
            }
            total += t * left_num * right_num;
        }
    }

    printf("Case #%d: %lld\n", _turn, total);
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
