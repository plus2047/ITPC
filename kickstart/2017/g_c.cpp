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
const int N_MAX = 64;
int N, M, mat[N_MAX][N_MAX];
int dp[N_MAX][N_MAX][N_MAX][N_MAX];
int min_val[N_MAX][N_MAX][N_MAX][N_MAX];

void solve(int _turn) {
    // CONTEST BEGIN!!!
    scanf("%d%d", &N, &M);
    rep(i, N) rep(j, M) { scanf("%d", &mat[i][j]); }

    rep(i, N) rep(j, M) { min_val[i][j][i][j] = mat[i][j]; }

    rep(i, N) rep(j, M) range(_i, i, N - 1) range(_j, j, M - 1) {
        if(_i == i and _j == j) continue;
        int& m = min_val[i][j][_i][_j];
        m = mat[_i][_j];
        if(_i != i) m = min(m, min_val[i][j][_i - 1][_j]);
        if(_j != j) m = min(m, min_val[i][j][_i][_j - 1]);
    }

    range(dx, 1, N) range(dy, 1, M) {
        if (dx == 1 and dy == 1) continue;
        rep(i, N) rep(j, M) {
            int _i = i + dx - 1, _j = j + dy - 1;
            if (_i >= N or _j >= M) break;

            int& score = dp[i][j][_i][_j];
            score = 0;
            range(cut_i, i, _i - 1) {
                score =
                    max(score, dp[i][j][cut_i][_j] + dp[cut_i + 1][j][_i][_j]);
            }
            range(cut_j, j, _j - 1) {
                score =
                    max(score, dp[i][j][_i][cut_j] + dp[i][cut_j + 1][_i][_j]);
            }
            score += min_val[i][j][_i][_j];
        }
    }

    printf("Case #%d: %d\n", _turn, dp[0][0][N - 1][M - 1]);
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
