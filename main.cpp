// ===== programing contest template ======
// ===== using standrod: C++ 11 =====

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

// ===== persional contest toolbox =====
// #include "lib/basic_math.h"
// #include "lib/bit.h"
// #include "lib/linear_algebra.h"
// #include "lib/mod_p.h"
// #include "lib/perime_num.h"

// #include "lib/graph_max_flow.h"
// #include "lib/graph_shortest_path.h"
// #include "lib/graph_spaning_tree.h"
// #include "lib/graph_strong_connect.h"

// #include "lib/interval_tree.h"
// #include "lib/merge_find.h"
// #include "lib/segment_tree.h"
// #include "lib/tree.h"
// #include "lib/trie.h"

// #include "lib/hash.h"
// #include "lib/kmp.h"
// #include "lib/tuple.h"

// #include "lib/iotools.h"
// #include "lib/thread_map.h"

// using namespace contest;
// persional contest toolbox finished =====

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
#define irep(i, N) for (int i = int(N) - 1; i >= 0; i--)

// ========== contest code ==========

void solve(int _turn) { printf("helloWorld!!!\n"); }

// ===== kickstart template =====
int main() {
#ifdef __LOCAL__  // define in build command.
    freopen("_kickstart.in", "r", stdin);
    freopen("_debug.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
    int T = 1;
    // scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
