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

const int LEN = 20;
LLU exp9[LEN];
void init(){
    exp9[0] = 1;
    for(int i = 1; i < LEN; i ++){
        exp9[i] = exp9[i - 1] * 9;
    }
}

bool valid(LLU num) {
    bool _valid = num % 9 != 0;
    while (_valid and num > 0) {
        if (num % 10 == 9) {
            _valid = false;
        }
        num /= 10;
    }
    return _valid;
}

LLU get_cnt(LLU right) {
    LLU cnt = 0;
    for(LLU n = right - right % 10; n <= right; n ++){
        if(valid(n)){
            cnt ++;
        }
    }
    for(int idx = 1; right > 0; idx ++){
        right /= 10;
        cnt += exp9[idx] * (right % 10) / 9 * 8;
    }
    return cnt;
}

int main() {
#ifdef __LOCAL__  // define in build command.
    freopen("_kickstart.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
    init();
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        LLU F, L;
        scanf("%llu%llu", &F, &L);
        LLU res = get_cnt(L) - get_cnt(F) + 1;
        echo("Case #%d: %llu\n", t, res);
    }
}
