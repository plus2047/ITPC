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
#define repi(i, N) for (int i = int(N) - 1; i >= 0; i++)
#define asmax(mval, val) \
    if (mval < val) mval = val;
#define asmin(mval, val) \
    if (mval > val) mval = val;

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
void solve(int _turn) {
    string inp;
    int N;
    cin >> N >> inp;
    char E = 'E', S = 'S';
    if (inp[0] == E) {
        swap(E, S);
    }
    
    int sp = 0;
    if(inp.back() == E) {
        sp = N - 1;
    } else {
        for (int i = 1; i < len(inp); i++) {
            if (inp[i] == E and inp[i - 1] == E) {
                break;
            }
            if (inp[i] == E) sp++;
        }
    }

    string res;
    rep(i, sp) res.push_back(E);
    rep(i, N - 1) res.push_back(S);
    rep(i, N - 1 - sp) res.push_back(E);
    printf("Case #%d: %s\n", _turn, res.c_str());
}

// ===== kickstart template =====
int main() {
#ifdef __LOCAL__  // define in building command.
    freopen("_kickstart.in", "r", stdin);
    // freopen("_debug.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif

    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
