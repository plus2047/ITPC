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
    lld N;
    scanf("%lld", &N);
    lld A[N][N], B[N][N];
    rep(i, N) rep(j, N) scanf("%lld", &A[i][j]);
    rep(i, N) rep(j, N) scanf("%lld", &B[i][j]);
    lld sumR[N], sumC[N];
    rep(i, N) scanf("%lld", &sumR[i]);
    rep(i, N) scanf("%lld", &sumC[i]);

    if (N > 5) return;  // only for small dataset
    unsigned maxMask = 0;
    lld totalScore = 0;
    int k = 0;
    rep(i, N) rep(j, N) {
        if (A[i][j] == -1) {
            maxMask |= 1 << k;
            totalScore += B[i][j];
        }
        k++;
    }

    lld maxScore = 0;
    vector<int> countR(N), countC(N);
    for (unsigned mask = maxMask; mask != 0; mask = (mask - 1) & maxMask) {
        fill(allof(countR), 0);
        fill(allof(countC), 0);

        lld score = 0, voidCount = 0;
        int k = 0;
        rep(i, N) rep(j, N) {
            if (mask & (1 << k)) {
                voidCount++;
                countR[i]++;
                countC[j]++;
                score += B[i][j];
            }
            if (B[i][j] and not(mask & (1 << k))) {
                A[i][j] = 0;
            }
            k++;
        }

        bool valid = true;
        while (voidCount) {
            bool succ = false;
            rep(i, N) rep(j, N) {
                if (A[i][j] == -1 and (countR[i] == 1 or countC[j] == 1)) {
                    A[i][j] = 0;
                    countR[i]--;
                    countC[j]--;
                    voidCount--;
                    succ = true;
                }
            }
            if (not succ) {
                valid = false;
                break;
            }
        }

        k = 0;
        rep(i, N) rep(j, N) {
            if (B[i][j]) {
                A[i][j] = -1;
            }
            k++;
        }
        if (valid) {
            maxScore = max(maxScore, score);
        }
    }

    lld res = totalScore - maxScore;
    printf("Case #%d: %lld\n", _turn + 1, res);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
