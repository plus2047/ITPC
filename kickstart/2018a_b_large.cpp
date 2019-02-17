// ===== programing contest template =========
// ===== using standrod: C++ 14 ==============
// ===== include all posible stl headers =====
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
// #define __TOOLBOX__
// ===== include persional toolbox ======
#ifdef __TOOLBOX__
#include "lib/graph.h"
#include "lib/hash.h"
#include "lib/show.h"
#include "lib/string.h"
using namespace contest;
#endif  // __TOOLBOX__
// for contest, it's okey to use namespace. =====
using namespace std;

// =============================================
// ============= CONTEST ENV BEGIN =============
typedef long long int LL;
typedef long long unsigned LLU;
#define G(_tuple, num) (get<num>(_tuple))
#define FOR(i, N) for (int i = 0, i##_len = (int)(N); i < i##_len; i++)
#define IFOR(i, N) for (int i = (int)(N)-1; i >= 0; i--)

// =============================================
// =============== CONTEST BEGIN ===============
const int VAL_MAX = 20000 + 128, K_MAX = 50000 + 128;
LL val[VAL_MAX], acc[VAL_MAX];
double expected[K_MAX];

int main() {
#ifdef __LOCAL__  // define in build command.
    freopen("_kickstart.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        LL N, K;
        scanf("%lld%lld", &N, &K);
        for (int i = 0; i < N; i++) scanf("%lld", val + i);
        sort(val, val + N);
        acc[N] = 0;
        for (LL i = N - 1; i >= 0; i--) acc[i] = acc[i + 1] + val[i];

        expected[K + 1] = 0;
        LL *bound = val, *val_end = val + N;
        for (LL k = K; k >= 0; k--) {
            bound = upper_bound(bound, val_end, expected[k + 1]);
            LL val_num = val_end - bound;
            double p_accept = double(val_num) / N;
            double aver = val_num == 0 ? 0 : double(acc[bound - val]) / val_num;
            expected[k] = p_accept * aver + (1 - p_accept) * expected[k + 1];
        }
        printf("Case #%d: %lf\n", t, expected[0]);
    }
}
