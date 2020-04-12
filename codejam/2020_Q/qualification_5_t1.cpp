// ===== programing contest template ======
// ===== using standrod: C++ 11 =====

// #undef __LOCAL__

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

// ===== personal contest env =====

typedef long long int lld;

#define frontof(c, k) (c).begin(), (c).begin() + (k)
#define allof(c) (c).begin(), (c).end()
#define len(container) int((container).size())
#define asmin(var, val) var = min(var, val)
#define asmax(var, val) var = max(var, val)

#define iter(i, begin, end) \
    for (int i = begin, d = begin < end ? 1 : -1; i != end; i += d)
#define each(i, first, last) \
    for (int i = first, d = first < last ? 1 : -1; i != last + d; i += d)

#define rep(i, N) for (int i = 0; i < int(N); ++i)
#define inv(i, N) for (int i = int(N) - 1; i >= 0; --i)

#if __cplusplus >= 201103L
template <typename num>
using mat = vector<vector<num> >;

template <typename num>
inline mat<num> make_mat(int s1, int s2, num val) {
    return mat<num>(s1, vector<num>(s2, val));
}

template <typename num>
inline void fill(mat<num>& m, num val) {
    for (auto& v : m)
        for (auto& n : v) n = val;
}

template <typename num>
void show(mat<num> m) {
    for (const auto& v : m) {
        for (const auto& n : v) cout << n << ' ';
        cout << endl;
    }
}
#endif  // C++11

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
int N, K;
mat<int> M;
mat<char> seen_r, seen_c;

bool dfs(int i, int j) {
    if (i == N) {
        int trace = 0;
        rep(x, N) { trace += M[x][x]; }
        return trace == K;
    }

    int _i = i, _j = j + 1;
    if (_j == N) {
        _j = 0, _i += 1;
    }

    rep(num, N) {
        if (not seen_r[i][num] and not seen_c[j][num]) {
            M[i][j] = num;
            seen_r[i][num] = true;
            seen_c[j][num] = true;
            if (dfs(_i, _j)) {
                return true;
            }
            seen_r[i][num] = false;
            seen_c[j][num] = false;
        }
    }
    return false;
}

void solve(int _turn) {
    // KEEP CALM AND CARRY ON!
    scanf("%d%d", &N, &K);
    K -= N;

    M = make_mat(N, N, 0);
    seen_r = make_mat(N, N, char(0));
    seen_c = make_mat(N, N, char(0));

    bool succ = dfs(0, 0);
    printf("Case #%d: %s\n", _turn + 1, succ ? "POSSIBLE" : "IMPOSSIBLE");
    if (succ) {
        rep(i, N) {
            rep(j, N) { printf("%d ", M[i][j] + 1); }
            printf("\n");
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
