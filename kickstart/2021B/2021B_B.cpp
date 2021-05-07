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
    vector<lld> A(N);
    rep(i, N) scanf("%lld", &A[i]);

    vector<lld> s1(N, 1), s2(N, 1);
    for (int i = 1; i < N; i++) {
        bool last = i != 1 and A[i] - A[i - 1] == A[i - 1] - A[i - 2];
        s1[i] = (last ? s1[i - 1] : 1) + 1;
    }
    for (int i = N - 2; i >= 0; i--) {
        bool last = i != N - 1 and A[i] - A[i + 1] == A[i + 1] - A[i + 2];
        s2[i] = (last ? s2[i + 1] : 1) + 1;
    }

    lld res = max(1 + s2[1], 1 + s1[N - 2]);
    for (int i = 1; i <= N - 2; i++) {
        if (i != 1 and i != N - 2 and
            A[i + 2] - A[i + 1] == A[i - 1] - A[i - 2] and
            2 * (A[i + 2] - A[i + 1]) == A[i + 1] - A[i - 1]) {
            res = max(res, 1 + s1[i - 1] + s2[i + 1]);
        } else if (i != N - 2 and
                   2 * (A[i + 2] - A[i + 1]) == A[i + 1] - A[i - 1]) {
            res = max(res, 2 + s2[i + 1]);
        } else if (i != 0 and
                   2 * (A[i - 2] - A[i - 1]) == A[i - 1] - A[i + 1]) {
            res = max(res, 2 + s1[i - 1]);
        }
        res = max(res, max(1 + s1[i - 1], 1 + s2[i + 1]));
    }

    printf("Case #%d: %lld\n", _turn + 1, res);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
