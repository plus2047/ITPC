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
const int MAXS = 1024;
const lld INF = INT_MAX;
char S[MAXS];

void solve(int _turn) {
    lld X, Y;
    scanf("%lld%lld%s", &X, &Y, S);
    lld N = strlen(S);
    vector<lld> costC(N, INF), costJ(N, INF);
    if (S[0] == 'C') {
        costC[0] = 0, costJ[0] = INF;
    } else if (S[0] == 'J') {
        costC[0] = INF, costJ[0] = 0;
    } else {
        costC[0] = 0, costJ[0] = 0;
    }
    for (int i = 1; i < N; i++) {
        if (S[i] == 'C') {
            costC[i] = min(costC[i - 1], costJ[i - 1] + Y);
            costJ[i] = INF;
        } else if (S[i] == 'J') {
            costJ[i] = min(costJ[i - 1], costC[i - 1] + X);
            costC[i] = INF;
        } else {
            costC[i] = min(costC[i - 1], costJ[i - 1] + Y);
            costJ[i] = min(costJ[i - 1], costC[i - 1] + X);
        }
    }
    lld res = min(costC[N - 1], costJ[N - 1]);
    printf("Case #%d: %lld\n", _turn + 1, res);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
