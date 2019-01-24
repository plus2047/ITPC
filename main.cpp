// ===== programing contest template =========
// ===== using standrod: C++ 14 ==============

#include <algorithm>
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
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// ===== if using persional toolbox =====
#define __TOOLBOX__

// ===== include persional toolbox ======
#ifdef __TOOLBOX__
#include "lib/graph.h"
#include "lib/iotools.h"
#include "lib/math.h"
#include "lib/structure.h"
using namespace contest;
#endif  // __TOOLBOX__

// for contest, it's okey to use namespace. =====
using namespace std;

// ============= CONTEST ENV BEGIN =============

typedef long long int LL;
typedef long long unsigned LLU;
typedef long double LD;
#define G(_tuple, num) (get<num>(_tuple))
#define popcount(x) __builtin_popcount(x)
#define popcountll(x) __builtin_popcountll(x)
#define len(c) int((c).size())
#define allof(container) (container).begin(), (container).end()
#define frontof(container, N) (container).begin(), (container).begin() + (N)
#define rep(i, N) for (int i = 0; i < int(N); i++)
#define range(i, begin, end) for (int i = int(begin); i < int(end); i++)
#define irep(i, N) for (int i = int(N) - 1; i >= 0; i--)
#define irange(i, begin, end) for (int i = int(end) - 1; i >= int(begin); i--)

// =============== CONTEST BEGIN ===============

// const ===

// algorithm functions =====
void solve(int _turn) {
    LL res = 0;
    echo("Case #%d: %lld\n", _turn, res);
}

// kickstart turn template =====
int main() {
#ifdef __LOCAL__  // define in build command.
    freopen("_kickstart.in", "r", stdin);
    freopen("_debug.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
