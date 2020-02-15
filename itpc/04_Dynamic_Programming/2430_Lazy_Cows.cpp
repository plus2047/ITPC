// ===== programing contest template ======
// ===== using standrod: C++ 11 =====

// #undef __LOCAL__

#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <map>
#include <queue>
#include <set>
#include <stack>
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

// ===== personal contest env =====

typedef long long int lld;

#define frontof(c, k) (c).begin(), (c).begin() + (k)
#define allof(c) (c).begin(), (c).end()
#define len(container) int((container).size())

#define iter(i, begin, end) \
    for (int i = begin, d = begin < end ? 1 : -1; i != end; i += d)
#define each(i, first, last) \
    for (int i = first, d = first < last ? 1 : -1; i != last + d; i += d)

#define rep(i, N) for (int i = 0; i < int(N); ++i)
#define rev(i, N) for (int i = int(N) - 1; i >= 0; --i)

#if __cplusplus >= 201103L
template <typename num>
using mat = vector<vector<num> >;

template <typename num>
inline mat<num> make_mat(int s1, int s2, num val) {
    return mat<num>(s1, vector<num>(s2, val));
}

template <typename num>
inline void fill(mat<num>& m, num val) {
    for (auto& v : m)
        for (auto& n : v) n = val;
}

template <typename num>
void show(mat<num> m) {
    for (const auto& v : m) {
        for (const auto& n : v) cout << n << ' ';
        cout << endl;
    }
}
#endif  // C++11

template <typename ITER>
void show(const char* note, ITER begin, ITER end) {
#ifdef __LOCAL__
    std::cout << note;
    for (; begin != end; begin++) std::cout << *begin << ' ';
    cout << endl;
#endif  // __LOCAL__
}

void echo(const char* fmt, ...) {
#ifdef __LOCAL__
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
#endif  // __LOCAL__
}

// ===== personal contest template =====

// ========== contest code ==========
inline lld min4(lld* p) { return min(min(p[0], p[1]), min(p[2], p[3])); }
lld dp[1024][1024][4];

void solve(int _turn) {
    int N, K, B;
    scanf("%d%d%d", &N, &K, &B);

    vector<pair<int, int> > cows;
    rep(i, N) {
        int x, y;
        scanf("%d%d", &x, &y);
        cows.push_back({y - 1, x - 1});
    }
    sort(allof(cows));

    vector<pair<int, int> > pos;
    // pos[i].second:
    // 0 or 1: cow at 0 or 1
    // 2: cow at 0 and 1
    rep(i, N) {
        if (pos.empty() or pos.back().first != cows[i].first) {
            pos.push_back(cows[i]);
        } else {
            pos.back().second = 2;
        }
    }
    // echo("pos:\n");
    // for (auto& p : pos) {
    //     echo("%d %d\n", p.first, p.second);
    // }

    memset(dp, 0x3f, sizeof dp);
    dp[0][0][2] = 0;
    int pos_size = len(pos);

    each(i, 1, pos_size) {
        each(k, 1, K) {
            lld &v0 = dp[i][k][0], &v1 = dp[i][k][1];
            lld &v2 = dp[i][k][2], &v3 = dp[i][k][3];

            lld m1 = min4(dp[i - 1][k - 1]);
            lld dpos = i == 1 ? 1 : pos[i - 1].first - pos[i - 2].first;

            if (pos[i - 1].second == 0) {
                v0 = min(v0, m1 + 1);
                v0 = min(v0, dp[i - 1][k][0] + dpos);
                v0 = min(v0, dp[i - 1][k][3] + dpos);
            } else if (pos[i - 1].second == 1) {
                v1 = min(v1, m1 + 1);
                v1 = min(v1, dp[i - 1][k][1] + dpos);
                v1 = min(v1, dp[i - 1][k][3] + dpos);
            }

            v2 = min(v2, m1 + 2);
            v2 = min(v2, dp[i - 1][k][2] + 2LL * dpos);

            lld min_p = min(dp[i - 1][k - 1][0], dp[i - 1][k - 1][1]);
            v3 = min(min_p + dpos + 1, dp[i - 1][k][3] + 2LL * dpos);

            if (k >= 2) {
                v3 = min(v3, min4(dp[i - 1][k - 2]) + 2);
            }
        }
    }

    printf("%lld\n", min4(dp[pos_size][K]));
}

// ===== kickstart template =====
int main() {
    int T = 1;
    // scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
