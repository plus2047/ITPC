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
int n;
char s[5010];
short dp[5010][5010];

int main() {
    scanf("%d", &n);
    scanf("%s", &s[0]);
    rep(i, n) range(j, i - 1, n - 1) dp[i][j] = 0;

    range(x, 2, n) for (int left = 0, right = x - 1; right < n;
                        left++, right++) {
        if (s[left] == s[right]) {
            dp[left][right] = dp[left + 1][right - 1];
        } else {
            dp[left][right] = 1 + min(dp[left + 1][right], dp[left][right - 1]);
        }
    }

    printf("%d\n", (int)dp[0][n - 1]);
}
