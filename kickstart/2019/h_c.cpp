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
void get_prime_flags(std::vector<bool>& flags) {
    // this function can get primes less than 1E9 in 4 seconds.
    // all flags should be init as true
    // assert flags.size() >= 2
    int lim = int(flags.size());
    flags[0] = flags[1] = false;
    for (int n = 4; n < lim; n += 2) {
        flags[n] = false;
    }
    for (int n = 3; n * n <= lim; n += 2) {
        if (flags[n]) {
            for (int t = n * 3; t < lim; t += n << 1) {
                flags[t] = false;
            }
        }
    }
}

template <typename NUM = int>
std::vector<NUM> prime_fact(NUM num) {  // worst complexity: O(num ^ 0.5)
    std::vector<NUM> res;

    while (num % 2 == 0) {
        num /= 2;
        res.push_back(2);
    }

    for (int p = 3; p * p <= num; p += 2) {
        if (num % p == 0) {
            while (num % p == 0) {
                res.push_back(p);
                num /= p;
            }
        }
    }

    if (num > 1) res.push_back(num);

    return res;
}

template <typename NUM>
NUM totient(NUM num) {  // Euler's totient function
    std::vector<NUM> facts = prime_fact(num);
    facts.push_back(-1);
    NUM res = 1, p = facts[0];
    int cnt = 0;
    for (NUM f : facts) {
        if (f != p) {
            while (--cnt) res *= p;
            res *= p - 1;
            p = f;
            cnt = 1;
        } else {
            cnt++;
        }
    }
    return res;
}

template <typename NUM>
struct ModNCalculator {
    const NUM MAX_NUM, MOD;
    NUM PHI;                          // Euler's totient function
    std::vector<NUM> fact, inv_fact;  // factorial & it's inverse

    inline NUM multiply(std::initializer_list<NUM> nums) {
        NUM res = 1;
        for (auto p = nums.begin(); p != nums.end(); p++) {
            res = res * (*p) % MOD;
        }
        return res;
    }

    inline NUM pow(NUM base, NUM n) {  // base ** n % MOD
        NUM res = 1, cur = base;
        while (n) {
            if (n % 2) res = (res * cur) % MOD;
            cur = (cur * cur) % MOD;
            n /= 2;
        }
        return res;
    }

    inline NUM inv(NUM num) {  // inv(n) * n % mod == 1
        // based on Fermat's little theorem.
        assert(num < MOD);
        return pow(num, PHI - 1);
    }

    inline NUM comb(NUM N, NUM k) {
        // N chooce k mod MOD
        assert(k <= N and k >= 0 and N < MOD);
        NUM res = fact[N];
        res = (res * inv_fact[k]) % MOD;
        res = (res * inv_fact[N - k]) % MOD;
        return res;
    }

    ModNCalculator(NUM max_num, NUM mod, bool is_prime)
        : MAX_NUM(max_num), MOD(mod), fact(max_num + 1), inv_fact(max_num + 1) {
        assert(1.0 * MOD * MOD < 1.0 * std::numeric_limits<NUM>::max());
        PHI = is_prime ? mod - 1 : totient(mod);
        if (max_num < 1) return;
        // init the calculator's pre-calculated factorial & inv
        // if donot need to use fact & comb, just set max_num = 0.
        fact[0] = fact[1] = 1;
        inv_fact[0] = inv_fact[1] = 1;
        for (int i = 2; i <= MAX_NUM; i++) {
            fact[i] = fact[i - 1] * i % MOD;
            inv_fact[i] = inv(fact[i]);
        }
    }
};

// ========== contest code ==========
vector<LL> A = vector<LL>(9);
ModNCalculator<LL> mod11c = ModNCalculator<LL>(128LL, 11LL, true);

#define subtract(a, b) (((a) + 11LL - (b)) % 11LL)

void solve(int _turn) {
    rep(i, 9) scanf("%lld", &A[i]);

    LL total_cnt = accumulate(allof(A), 0LL);
    LL neg_cnt = total_cnt / 2LL;

    LL total_sum_mod = 0LL;
    rep(i, 9) { total_sum_mod += (i + 1) * A[i]; }
    total_sum_mod %= 11LL;

    LL neg_sum_mod = mod11c.multiply({total_sum_mod, mod11c.inv(2)});

    // printf("total sum mod: %lld, neg sum mod: %lld\n", total_sum_mod,
    // neg_sum_mod);

    vec2d(char, target2cnt, 11, 11, 0);
    vec2d(char, _target2cnt, 11, 11, 0);
    target2cnt[0][0] = 1;

    rep(i, 9) {
        _target2cnt = target2cnt;
        LL max_cnt = min(11LL, A[i]);
        for (LL i_cnt = 1; i_cnt <= max_cnt; i_cnt++) {
            LL r = (i + 1) * i_cnt % 11LL;

            rep(target, 11) {
                rep(cnt, 11) {
                    if (target2cnt[target][cnt]) {
                        _target2cnt[(target + r) % 11][(cnt + i_cnt) % 11] = 1;
                    }
                }
            }
        }

        target2cnt = _target2cnt;
        // printf("target2cnt after %d:\n", i + 1);
        // rep(i, 11) {
        //     rep(j, 11) { printf("%d ", target2cnt[i][j] == 0 ? 0 : 1); }
        //     printf("\n");
        // }
    }

    bool succ = target2cnt[neg_sum_mod][neg_cnt % 11LL];

    printf("Case #%d: %s\n", _turn, succ ? "YES" : "NO");
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
