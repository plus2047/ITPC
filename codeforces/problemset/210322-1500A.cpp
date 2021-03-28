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

// ========== contest code ==========

void solve(int _turn) {
    const int n_max = 2.5E6 + 10;
    lld n;
    scanf("%lld", &n);
    vector<lld> nums(n);
    rep(i, n) scanf("%lld", &nums[i]);
    auto nil = make_pair(-1, -1);
    vector<pair<int, int> > sums(n_max * 2, nil);
    for (int x = 0; x < n; x++) {
        for (int y = x + 1; y < n; y++) {
            lld s = nums[x] + nums[y];
            auto p = sums[s];
            if (p != nil) {
                if (p.first != x and p.second != y and p.first != y and
                    p.second != x) {
                    printf("YES\n%d %d %d %d\n", p.first + 1, p.second + 1,
                           x + 1, y + 1);
                    return;
                }
            } else {
                sums[s] = {x, y};
            }
        }
    }
    printf("NO\n");
}

int main() {
    int T = 1;
    // scanf("%d", &T);
    rep(t, T) { solve(t); }
}
