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

typedef long long int LL;
#define G(_tuple, num) (get<num>(_tuple))
#define len(container) int((container).size())
#define allof(c) (c).begin(), (c).end()
#define frontof(c, k) (c).begin(), (c).begin() + (k)
#define rep(i, N) for (int i = 0; i < int(N); i++)
#define repr(i, begin, end) for (int i = int(begin); i < int(end); i++)
#define repi(i, N) for (int i = int(N) - 1; i >= 0; i--)
#define asmax(m, update) \
    if (m < update) m = update;
#define asmin(m, update) \
    if (m > update) m = update;
#define vec2d(type, name, m, n, v) \
    vector<vector<type>> name = vector<vector<type>>(m, vector<type>(n, v))

template <int group = 20, typename ITER>
void show(const char* note, ITER begin, ITER end) {
#ifdef __LOCAL__
    cout << note;
    for (int i = 1; begin != end; i++) {
        std::cout << *(begin++) << ' ';
        if (i % group == 0 or begin == end) std::cout << std::endl;
    }
#endif  // __LOCAL__
}

#ifdef __LOCAL__
std::clock_t _t0 = 0;
void timer_begin() { _t0 = clock(); }
void timer_end(const char* note) {
    double delta = double(clock() - _t0) / CLOCKS_PER_SEC;
    printf("%s cost: %lf sec.\n", note, delta);
}
#else
#define timer_begin() (void(0))
#define timer_end(note) (void(0))
#endif  // __LOCAL__

// ===== personal contest template =====

// ========== contest code ==========
char s1[2048], s2[2048];

void expand(char s[], string& p) {
    for (; *s; s++) {
        if (*s == '*') {
            p += "****";
        } else {
            p += *s;
        }
    }
}

void solve(int _turn) {
    scanf("%s%s", s1, s2);
    string p1 = "_", p2 = "_";
    expand(s1, p1);
    expand(s2, p2);

    int n1 = len(p1), n2 = len(p2);
    vec2d(char, dp, n1 + 1, n2 + 1, 0);

    dp[0][0] = 1;

    rep(i, n1) rep(j, n2) {
        char& isValid = dp[i + 1][j + 1];
        if (p1[i] == '*') {
            isValid = isValid or dp[i][j] or dp[i][j + 1];
        }
        if (p2[j] == '*') {
            isValid = isValid or dp[i][j] or dp[i + 1][j];
        }
        if(p1[i] == p2[j]) {
            isValid = isValid or dp[i][j];
        }
        if(p1[i] != p2[j] and p1[i] != '*' and p2[j] != '*') {
            isValid = 0;
        }
    }

    printf("Case #%d: %s\n", _turn, dp[n1][n2] ? "TRUE" : "FALSE");
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
