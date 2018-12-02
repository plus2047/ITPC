// for programing contest
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <climits>
#include <vector>
#include <sstream>
#include <iostream>
#include <set>
#include <unordered_set>
#include <random>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <unordered_map>
#include <map>
#include <stdexcept>

using namespace std;

typedef long long int lld;

const lld MOD = 1000000007;

lld N, M;

lld beta(lld x){
    lld res = x;
    while(-- x){
        res *= x;
        res %= MOD;
    }
    return res;
}
lld exp2(lld m){
    lld res = 1;
    while(m --){
        res *= 2;
        res %= MOD;
    }
    return res;
}

lld near(lld k){
    return beta(2 * N - k) * exp2(k);
}

lld nCr(lld m, lld k){
    lld res = 1;
    for(lld i = 0; i < k; i ++){
        res *= (m - i);
        res /= (i + 1);
        res %= MOD;
    }
    return res;
}

int main() {
    #ifdef __APPLE__
    freopen("_in_small.txt", "r", stdin);
    freopen("_out_cpp.txt", "w", stdout);
    #endif

    lld T; scanf("%lld", &T);
    for(lld t = 1; t <= T; t ++){
        scanf("%lld%lld", &N, &M);
        lld n_neg = 0;

        lld s[M + 1];
        for(lld near_c = M; near_c >= 1; near_c --){
            lld _t = nCr(M, near_c);
            lld n = _t * near(near_c);
            for(lld k = near_c + 1; k <= M; k ++){
                n -= nCr(k, near_c) * s[k];
                n %= MOD;
                if(n < 0){
                    n += MOD;
                }
            }
            s[near_c] = n;
        }

        lld neg = 0;
        for(int i = 1; i <= M; i ++){
            neg += s[i];
            neg %= MOD;
        }
        lld total = beta(2 * N);
        total -= neg;
        total %= MOD;
        if(total < 0){
            total += MOD;
        }

        printf("Case #%lld: %lld\n", t, total);
    }
}
