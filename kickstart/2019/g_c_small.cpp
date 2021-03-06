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
template <typename num_t>
num_t quick_pow(num_t base, int n) {
    num_t res = 1;
    while (n) {
        if (n % 2) res *= base;
        base *= base;
        n /= 2;
    }
    return res;
}

// ========== contest code ==========
const int N_MAX = 32;
vector<int> A(N_MAX), B(N_MAX);

void solve(int _turn) {
    int N, H;
    scanf("%d%d", &N, &H);
    rep(i, N) scanf("%d", &A[i]);
    rep(i, N) scanf("%d", &B[i]);

    unsigned mask_lim = quick_pow(3, N);
    LL sum_a = 0, sum_b = 0, res = 0;
    for(LL mask = 0; mask < mask_lim; mask++) {
        sum_a = sum_b = 0;
        LL m = mask;
        rep(i, N) {
            int act = m % 3;
            m /= 3;
            if(not(act & 1)) sum_a += A[i];
            if(not(act & 2)) sum_b += B[i];
        }
        if(sum_a >= H and sum_b >= H) res++;
    }

    printf("Case #%d: %lld\n", _turn, res);
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
