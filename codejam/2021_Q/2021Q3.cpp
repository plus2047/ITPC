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
    lld N, C;
    scanf("%lld%lld", &N, &C);
    lld minC = N - 1, maxC = (N + 2) * (N - 1) / 2;
    if (C < minC or C > maxC) {
        printf("Case #%d: IMPOSSIBLE\n", _turn + 1);
        return;
    }
    vector<lld> cs;
    for(int x = N; x >= 2; x--) {
        if (C - 1 <= (x + 1) * (x - 2) / 2) {
            cs.push_back(1);
            C--;
        } else {
            cs.push_back(x);
            C -= x;
        }
    }
    vector<lld> res(N);
    rep(i, N) res[i] = i + 1;
    inv(i, N - 1) {
        for(int x = i, y = i + cs[i] - 1; x < y; x++, y--) {
            swap(res[x], res[y]);
        }
    }
    // print("cs: ", allof(cs));
    printf("Case #%d:", _turn + 1);
    rep(i, N) printf(" %lld", res[i]);
    printf("\n");
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
