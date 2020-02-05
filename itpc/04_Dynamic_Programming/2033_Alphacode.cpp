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
char s[10240];
lld dp[10240];

int main() {
    while (scanf("%s", s), s[0] != '0') {
        int n = strlen(s);
        dp[n] = 1;
        dp[n + 1] = 0;
        irange(i, 0, n - 1) {
            dp[i] = 0;
            if (s[i] != '0') dp[i] += dp[i + 1];
            if (s[i] == '1') dp[i] += dp[i + 2];
            if (s[i] == '2' and s[i + 1] <= '6' and i != n - 1)
                dp[i] += dp[i + 2];
        }
        printf("%lld\n", dp[0]);
    }
}
