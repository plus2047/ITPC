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

// for contest, it's okey to use namespace. =====
using namespace std;

// ============= CONTEST ENV BEGIN =============

typedef long long int LL;
typedef long long unsigned LLU;
typedef long double LD;
#define G(_tuple, num) (get<num>(_tuple))
#define len(c) int((c).size())
#define allof(container) (container).begin(), (container).end()
#define frontof(container, N) (container).begin(), (container).begin() + (N)
#define rep(i, N) for (int i = 0; i < int(N); i++)
#define repr(i, begin, end) for (int i = int(begin); i < int(end); i++)
#define irep(i, N) for (int i = int(N) - 1; i >= 0; i--)
#define irepr(i, begin, end) for (int i = int(end) - 1; i >= int(begin); i--)

// =============== CONTEST BEGIN ===============

void solve(int _turn) {
    LL N, L, res;
    printf("%lld\n", res);
}

// kickstart turn template =====
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
