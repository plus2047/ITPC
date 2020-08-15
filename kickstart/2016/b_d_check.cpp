// ===== programing contest template ======

#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <bitset>
#include <functional>
#include <random>
#include <unordered_map>
#include <unordered_set>
#endif  // C++11

using namespace std;

typedef long long int lld;
#define frontof(c, k) (c).begin(), (c).begin() + (k)
#define allof(c) (c).begin(), (c).end()
#define len(container) int((container).size())
#define asmin(var, val) var = min(var, val)
#define asmax(var, val) var = max(var, val)
#define rep(i, N) for (int i = 0; i < int(N); ++i)
#define inv(i, N) for (int i = int(N) - 1; i >= 0; --i)

// ========== contest code ==========

void solve(int _turn) {
    lld N, M;
    scanf("%lld%lld", &N, &M);

    vector<int> nums(N);
    for(int i = 1; i <= N; i++) {
        nums[i - 1] = i;
    }

    lld res = 0;
    do {
        int pre_max = 0;
        int chunk = 0;
        for(int i = 0; i < N; i++) {
            pre_max = max(pre_max, nums[i]);
            if(pre_max == i + 1) {
                chunk++;
            }
        }
        res = (res + lld(chunk) * lld(chunk)) % M;
    } while(next_permutation(allof(nums)));

    printf("Case #%d: %lld\n", _turn + 1, res);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
