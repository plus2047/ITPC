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
#include "lib/hash.h"
#include "lib/show.h"
#include "lib/string.h"
using namespace contest;
#endif  // __TOOLBOX__

// for contest, it's okey to use namespace. =====
using namespace std;

// ============= CONTEST ENV BEGIN =============

typedef long long int LL;
typedef long long unsigned LLU;
#define G(_tuple, num) (get<num>(_tuple))
#define rep(i, N) for (int i = 0, _len_ = int(N); i < _len_; i++)
#define aord(a) ((a) - 'a')
#define achr(a) ((a) + 'a')
#define fillc(c, v) (fill((c).begin(), (c).end(), v))

// =============== CONTEST BEGIN ===============

int T;

int main() {
#ifdef __LOCAL__  // define in build command.
    freopen("_kickstart.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        LLU N, K, P;
        scanf("%llu%llu%llu", &N, &K, &P);
        string str(N, '-');
        rep(i, K) {
            int A, B, C;
            scanf("%d%d%d", &A, &B, &C);
            str[A - 1] = (C == 1 ? '1' : '0');
        }
        P--;
        int idx = N - 1;
        for(int idx = N - 1; idx >= 0; idx --){
            if(str[idx] == '-'){
                str[idx] = P % 2 ? '1' : '0';
                P >>= 1;
            }
        }
        printf("Case #%d: %s\n", t, str.c_str());
    }
}
