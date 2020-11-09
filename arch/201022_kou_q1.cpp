#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
    typedef long long int lld;       // int32 may overflow
    const lld NINF = INT64_MIN / 2;  // used to mark invalid state
    lld N, K, A, B;

    // read input
    while (scanf("%lld%lld%lld%lld", &N, &K, &A, &B) != EOF) {
        vector<lld> S(N);
        for (int i = 0; i < N; i++) scanf("%lld", &S[i]);

        vector<lld> dp(N, NINF), _dp(N, NINF);
        lld res = 0;
        for (lld k = 1; k <= K; k++) {
            // in the k epoch,
            // dp[i] means the max score to place on point i
            // and all points taken is less then or equal to k
            // _dp is the memory for (k - 1) step

            lld max_pre = NINF, max_inc = NINF;
            // max_pre is the max score seen on the last epoch before this point
            // max_inc is the max score + A * i

            for (lld i = 0; i < N; i++) {
                dp[i] = S[i];
                dp[i] += max({max_pre, max_inc + (B - i) * A, 0LL});
                max_pre = max(max_pre, _dp[i]);
                max_inc = max(max_inc, _dp[i] + i * A);
                res = max(res, dp[i]);
            }
            swap(dp, _dp);
        }

        printf("%lld\n", res);
    }
}
