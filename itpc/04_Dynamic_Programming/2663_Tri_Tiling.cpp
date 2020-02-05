// ===== programing contest template ======
// ===== using a very very old C++ version =====

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

#include <bitset>
#include <map>
#include <queue>
#include <set>
#include <stack>
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

// #undef __LOCAL__

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

int main() {
    int dp[32][7] = {
        {1, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 0}
    };
    range(i, 2, 31) {
        dp[i][0] = dp[i - 1][3] + dp[i - 2][0] * 2 + dp[i - 2][4];
        dp[i][3] = dp[i - 1][6] + dp[i - 1][0];
        dp[i][4] = dp[i - 1][1];
        dp[i][6] = dp[i - 1][3];
        dp[i][1] = dp[i - 1][4] + dp[i - 1][0];
    }

    int n;
    while (scanf("%d", &n), n != -1) {
        printf("%d\n", dp[n][0]);
    }
}
