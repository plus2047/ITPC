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
// this function can get primes less than 1E9 in 4 seconds.
// all flags should be init as true
// assert flags.size() >= 2
void prime_flags(std::vector<bool>& flags) {
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

const lld ZMAX = 1LL << 60LL;
const lld PMAX = 1LL << 30LL;

vector<bool> pf(PMAX, true);
vector<lld> primes;

void solve(int _turn) {
    lld Z;
    scanf("%lld", &Z);
    lld last = 1, res = 0;
    for (int x : primes) {
        if (x * last <= Z) {
            res = x * last;
        } else {
            break;
        }
        last = x;
    }
    printf("Case #%d: %lld\n", _turn + 1, res);
}

int main() {
    int T;
    scanf("%d", &T);
    prime_flags(pf);
    for (lld x = 0; x < PMAX; x++) {
        if (pf[x]) {
            primes.push_back(x);
        }
    }
    vector<pair<lld, int> > Z(T);
    rep(i, T) {
        scanf("%lld", &Z[i].first);
        Z[i].second = i;
    }
    sort(allof(Z));
    vector<lld> res(T);
    lld last = 1, curr = 0, lastRes = 1;
    for (lld x = 1; x < PMAX; x++) {
        if (pf[x]) {
            while (curr < T and x * last > Z[curr].first) {
                res[Z[curr].second] = lastRes;
                curr++;
            }
            if (curr >= T) break;
            lastRes = last * x;
            last = x;
        }
    }
    rep(i, T) { printf("Case #%d: %lld\n", i + 1, res[i]); }
}
