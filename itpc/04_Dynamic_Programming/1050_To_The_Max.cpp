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
    int n;
    scanf("%d", &n);
    int mat[n][n];
    rep(i, n) rep(j, n) scanf("%d", &mat[i][j]);

    range(i, 1, n - 1) {
        mat[i][0] += mat[i - 1][0];
        mat[0][i] += mat[0][i - 1];
    }
    range(i, 1, n - 1) range(j, 1, n - 1) {
        mat[i][j] += mat[i - 1][j] + mat[i][j - 1] - mat[i - 1][j - 1];
    }

    int res = -128;
    rep(i, n) rep(j, n) {
        res = max(res, mat[i][j]);
        rep(_i, i) res = max(res, mat[i][j] - mat[_i][j]);
        rep(_j, j) res = max(res, mat[i][j] - mat[i][_j]);
        rep(_i, i) rep(_j, j) {
            res = max(res, mat[i][j] - mat[_i][j] - mat[i][_j] + mat[_i][_j]);
        }
    }

    printf("%d\n", res);
}
