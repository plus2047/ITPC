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

// ========== contest code ==========
const int R_MAX = 1E9 + 7;
vector<bool> prime_flags(R_MAX, true);
void init() {
    get_prime_flags(prime_flags);
}

bool isInteresting(int x) {
    if(x % 8 == 0) {
        return x == 8;
    } else if(x % 4 == 0) {
        int a = x / 4;
        return a == 1 or prime_flags[a];
    } else if(x % 2 == 0) {
        return true;
    } else {
        return x == 1 or prime_flags[x];
    }
    return false;
}

void solve(int _turn) {
    int L, R;
    scanf("%d%d", &L, &R);
    int cnt = 0;
    repr(i, L, R + 1) {
        if (isInteresting(i)) {
            cnt++;
        }
    }
    printf("Case #%d: %d\n", _turn, cnt);
}

// ===== kickstart template =====
int main() {
    init();
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
