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

typedef long long int lld;
#define len(container) int((container).size())
#define allof(c) (c).begin(), (c).end()
#define frontof(c, k) (c).begin(), (c).begin() + (k)
#define rep(i, N) for (int i = 0; i < int(N); ++i)
#define range(i, left, right) for (int i = int(left); i <= int(right); ++i)
#define irange(i, left, right) for (int i = int(right); i >= int(left); --i)

#undef __LOCAL__

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
const int CAKE_MAX = 100;
const int N_MAX = 10000;
vector<int> dp = vector<int>(N_MAX + 1, N_MAX);

void init() {
    dp[0] = 0;
    for(int n = 1; n <= N_MAX; n++) {
        for(int i = 1; i * i <= n; i++) {
            dp[n] = min(dp[n], dp[n - i * i] + 1);
        }
    }
}

void solve(int _turn) {
    int n;
    scanf("%d", &n);
    printf("Case #%d: %d\n", _turn, dp[n]);
}

// ===== kickstart template =====
int main() {
    init();
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
