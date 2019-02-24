// for programing contest
// kickstart 2018g_p2

// becare for using int to calculate multiply.
// tips: always using long long int for calculating.
// just use int for loop variable or never use it.

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
typedef long long unsigned llu;

#define MAX_N (7010)

lld nums[MAX_N];

int main() {
    #ifdef __APPLE__
    freopen("_kickstart.in", "r", stdin);
    // freopen("_debug.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
    #endif
    int T; scanf("%d", &T);
    for(int t = 1; t <= T; t ++){
        lld N; scanf("%lld", &N);
        for(int i = 0; i < N; i ++) scanf("%lld", nums + i);
        sort(nums, nums + N);
        lld n0 = upper_bound(nums, nums + N, 0) - nums;
        lld count = 0;
        for(int i = n0; i < N; i ++){
            for(int j = i + 1; j < N; j ++){
                lld prod = nums[i] * nums[j];
                auto range = equal_range(nums + j + 1, nums + N, prod);
                count += range.second - range.first;
                if(prod > nums[N - 1]) break;
            }
        }
        if(n0 >= 3) count += n0 * (n0 - 1l) * (n0 - 2l) / 6l;
        if(n0 >= 2) count += n0 * (n0 - 1l) / 2l * (N - n0);
        printf("Case #%d: %lld\n", t, count);
        fprintf(stderr, "Case #%d: %lld\n", t, count);
    }
}
