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
void solve(int _turn) {
    // KEEP CALM AND CARRY ON!
    int n;
    scanf("%d\n", &n);
    mat<int> matrix = make_mat(n, n, 0);
    rep(i, n) rep(j, n) { scanf("%d", &matrix[i][j]); }
    int k = 0, r = 0, c = 0;
    rep(i, n) { k += matrix[i][i]; }
    vector<char> seen_r(n + 1), seen_c(n + 1);
    rep(i, n) {
        fill(allof(seen_r), 0);
        fill(allof(seen_c), 0);
        bool r_dup = false, c_dup = false;
        rep(j, n) {
            if (seen_r[matrix[i][j]]) {
                r_dup = true;
            }
            if (seen_c[matrix[j][i]]) {
                c_dup = true;
            }
            seen_r[matrix[i][j]] = 1;
            seen_c[matrix[j][i]] = 1;
        }
        if(r_dup) r++;
        if(c_dup) c++;
    }
    printf("Case #%d: %d %d %d\n", _turn + 1, k, r, c);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
