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
#define len(c) int((c).size())
#define allof(container) (container).begin(), (container).end()
#define rep(i, N) for (int i = 0; i < int(N); i++)
#define repr(i, begin, end) for (int i = int(begin); i < int(end); i++)
#define repi(i, N) for (int i = int(N) - 1; i >= 0; i--)

template <int group = 16, typename ITER>
void show(const char* note, ITER begin, ITER end) {
#ifdef __LOCAL__
    printf("%s", note);
    int i = 1;
    for (; begin != end; i++) {
        std::cout << *(begin++) << ' ';
        if (i % group == 0) std::cout << std::endl;
    }
    if (i % group != 1) std::cout << std::endl;
#endif
}

// ===== personal contest template =====
template <typename num_t>
num_t gcd(num_t a, num_t b) {
    // Greatest Common Divisor
    // gcd(0, n) == gcd(n, 0) == n
    // gcd(1, n) == gcd(n, 1) == 1
    // (for this implement) gcd(0, 0) == 0
    while (b) {
        num_t r = a % b;
        a = b;
        b = r;
    }
    return a;
}

// ========== contest code ==========
const int MAX_L = 128;
char words[MAX_L][MAX_L];
int cnt[MAX_L][MAX_L][2][MAX_L];  // [last_i][last_j][row or column][first]
int _cnt[MAX_L][MAX_L];

const int MAX_W = 5000 + 8;
char buff[MAX_W];

void solve(int _turn) {
    int R, C, W;
    scanf("%d%d%d", &R, &C, &W);
    rep(i, R) { scanf("%s", words[i]); }

    unordered_map<string, int> dict;
    rep(i, W) {
        scanf("%s", buff);
        dict[buff]++;
        reverse(buff, buff + int(strlen(buff)));
        dict[buff]++;
    }

    fill((int*)cnt, (int*)(cnt) + MAX_L * MAX_L * MAX_L * 2, 0);
    rep(first_i, R) rep(first_j, C) {
        string str;
        repr(last_i, first_i, R) {
            str.push_back(words[last_i][first_j]);
            int n = dict[str] * (last_i - first_i + 1);
            rep(_i, first_i + 1) cnt[last_i][first_j][1][_i] += n;
        }
        str.clear();
        repr(last_j, first_j, C) {
            str.push_back(words[first_i][last_j]);
            int n = dict[str] * (last_j - first_j + 1);
            rep(_j, first_j + 1) cnt[first_i][last_j][0][_j] += n;
        }
    }
    // rep(last_i, R) rep(last_j, C) {
    //     printf("i: %d, j: %d\n", last_i, last_j);
    //     show("row: ", cnt[last_i][last_j][0], cnt[last_i][last_j][0] + C);
    //     show("column: ", cnt[last_i][last_j][1], cnt[last_i][last_j][1] + R);
    // }

    LL a = 0, b = 1, num = 0;  // a / b
    rep(first_i, R) rep(first_j, C) repr(last_i, first_i, R)
        repr(last_j, first_j, C) {
        LL n;
        n = cnt[last_i][last_j][1][first_i] + cnt[last_i][last_j][0][first_j];
        if (last_i != first_i) n += _cnt[last_i - 1][last_j];
        if (last_j != first_j) n += _cnt[last_i][last_j - 1];
        if (last_i != first_i and last_j != first_j) {
            n -= _cnt[last_i - 1][last_j - 1];
        }
        _cnt[last_i][last_j] = n;
        // printf("(%d, %d), (%d, %d): %lld\n", first_i, first_j, last_i,
        // last_j, n);

        // if (n == 0) continue;
        LL _b = last_i - first_i + last_j - first_j + 2;
        LL t1 = n * b, t2 = a * _b;
        if (t1 > t2) {
            a = n, b = _b, num = 1;
        } else if (t1 == t2) {
            num++;
        }
    }
    LL _gcd = gcd(a, b);
    a /= _gcd, b /= _gcd;

    printf("Case #%d: %lld/%lld %lld\n", _turn, a, b, num);
    fprintf(stderr, "%d\n", _turn);
}

// ===== kickstart template =====
int main() {
#ifdef __LOCAL__  // define in build command.
    freopen("_kickstart.in", "r", stdin);
    // freopen("_debug.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
