// for programing contest
#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
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

#include "snips/finite_field.h"

using namespace std;

typedef long long int lld;
typedef long long unsigned llu;

const lld MOD = 1000000007;
const lld MAX = 100000 + 10;
lld fact[2 * MAX];
lld inv_fact[2 * MAX];

int main() {
    #ifdef __APPLE__
    freopen("_in_large.in", "r", stdin);
    freopen("_out_cpp.txt", "w", stdout);
    #endif

    get_factorial_mod(fact, 2 * MAX, MOD);
    for(int i = 0; i < 2 * MAX; i ++){
        inv_fact[i] = inv_mod(fact[i], MOD);
    }

    int T; scanf("%d", &T);
    for(int t = 1; t <= T; t ++){
        lld N, M; scanf("%lld%lld", &N, &M);
        lld sum = 0;
        lld sign = 1;
        for(lld k = 0; k <= M; k ++){
            lld prod = fact[2 * N - k];
            prod = prod * power_mod(lld(2), k, MOD) % MOD;
            prod = prod * combinations_mod(M, k, MOD, fact, inv_fact) % MOD;
            prod *= sign;
            sign *= -1;
            sum = (sum + prod + MOD) % MOD;
        }
        printf("Case #%d: %lld\n", t, sum);
    }
}
