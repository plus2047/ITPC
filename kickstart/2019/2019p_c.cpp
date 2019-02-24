// ===== programing contest template ======
// ===== using standrod: C++ 11 =====

#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// ===== persional contest env =====

typedef long long int LL;
typedef long long unsigned LLU;
typedef long double LD;
#define G(_tuple, num) (get<num>(_tuple))
#define len(c) int((c).size())
#define allof(container) (container).begin(), (container).end()
#define rep(i, N) for (int i = 0; i < int(N); i++)
#define repr(i, begin, end) for (int i = int(begin); i < int(end); i++)
#define repi(i, N) for (int i = int(N) - 1; i >= 0; i--)
template <typename ITER>
void show(const char* note, ITER begin, ITER end) {
    printf("%s", note);
    while (begin != end) {
        std::cout << *(begin++) << ' ';
    }
    std::cout << std::endl;
}

template <typename ITER>
void show(const char* note, ITER begin, ITER end, int group) {
    printf("%s", note);
    int i = 1;
    for (; begin != end; i++) {
        std::cout << *(begin++) << ' ';
        if (i % group == 0) std::cout << std::endl;
    }
    if (i % group != 1) std::cout << std::endl;
}

template <typename NUM>
struct ModPCalculator {
    const NUM MAX_NUM, PRIME;
    std::vector<NUM> fact, inv_fact;  // factorial & it's inverse

    inline NUM power(NUM base, NUM n) {  // base ** n % PRIME
        NUM res = 1, cur = base;
        while (n) {
            if (n % 2) res = (res * cur) % PRIME;
            cur = (cur * cur) % PRIME;
            n /= 2;
        }
        return res;
    }

    inline NUM inv(NUM num) {  // inv(n) * n % prime == 1
        // based on Fermat's little theorem.
        assert(num < PRIME);
        return power(num, PRIME - 2);
    }

    NUM comb(NUM N, NUM k) {
        // N chooce k mod PRIME
        assert(k <= N and k >= 0 and N < PRIME);
        NUM res = fact[N];
        res = (res * inv_fact[k]) % PRIME;
        res = (res * inv_fact[N - k]) % PRIME;
        return res;
    }

    ModPCalculator(NUM max_num, NUM prime)
        : MAX_NUM(max_num),
          PRIME(prime),
          fact(max_num + 1),
          inv_fact(max_num + 1) {
        assert(1.0 * PRIME * PRIME < 1.0 * std::numeric_limits<NUM>::max());
        fact[0] = fact[1] = 1;
        inv_fact[0] = inv_fact[1] = 1;
        for (int i = 2; i <= MAX_NUM; i++) {
            fact[i] = fact[i - 1] * i % PRIME;
            inv_fact[i] = inv(fact[i]);
        }
    }
};

// ========== contest code ==========
const LL MOD = 1E9 + 7;
void solve(int _turn) {
    LL N, K, X1, Y1, C, D, E1, E2, F;
    scanf("%lld%lld%lld%lld%lld%lld%lld%lld%lld", &N, &K, &X1, &Y1, &C, &D, &E1,
          &E2, &F);
    vector<LL> A(N);
    A[0] = (X1 + Y1) % F;
    repr(i, 1, N) {
        LL _x = (C * X1 + D * Y1 + E1) % F;
        LL _y = (D * X1 + C * Y1 + E2) % F;
        A[i] = (_x + _y) % F;
        X1 = _x, Y1 = _y;
    }

    // show("A: ", allof(A));
    ModPCalculator<LL> pcal(0, MOD);
    LL res = 0;
    LL coef = K;
    rep(n, N) {
        if (n != 0) {
            LL _t = (pcal.power(n + 1, K) - 1) * pcal.inv(n) % MOD;
            coef = (coef + (n + 1) * _t) % MOD;
        }
        LL _t = A[n] * coef % MOD;
        res = (res + (N - n) * _t) % MOD;
    }
    printf("Case #%d: %lld\n", _turn, res);
}

// ===== kickstart template =====
int main() {
#ifdef __LOCAL__  // define in build command.
    freopen("_kickstart.in", "r", stdin);
    freopen("_debug.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
