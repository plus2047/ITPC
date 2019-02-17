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
int main() {
#ifdef __LOCAL__  // define in build command.
    freopen("_kickstart.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        LL N;
        scanf("%lld", &N);

        LL less_val = N, greater_val = N;
        for (LL mask = 1E16; mask >= 1; mask /= 10) {
            if (less_val / mask % 2 == 1) {
                less_val -= mask;
                LL tail = 0;
                for (LL i = 1; i < mask; i *= 10) tail += 8 * i;
                less_val = (less_val / mask) * mask + tail;
                break;
            }
        }
        for (LL mask = 1E16; mask >= 1; mask /= 10) {
            if (greater_val / mask % 2 == 1) {
                greater_val = (greater_val / mask) * mask;
                while ((greater_val / mask) % 2 == 1) {
                    greater_val += mask;
                    while (greater_val % (mask * 10) == 0) mask *= 10;
                }
                break;
            }
        }
        
        // printf("N: %lld, less: %lld, greater: %lld\n", N, less_val, greater_val);
        printf("Case #%d: %lld\n", t, min(greater_val - N, N - less_val));
    }
}
