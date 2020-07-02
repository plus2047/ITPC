#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <functional>
#include <iostream>
#include <random>

#include <array>
#include <bitset>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

typedef long long int lld;
typedef unsigned long long int llu;

#define frontof(c, k) (c).begin(), (c).begin() + (k)
#define allof(c) (c).begin(), (c).end()
#define len(container) int((container).size())
#define asmin(var, val) var = min(var, val)
#define asmax(var, val) var = max(var, val)

#define iter(i, begin, end) \
    for (int i = begin, d = begin < end ? 1 : -1; i != end; i += d)
#define each(i, first, last) \
    for (int i = first, d = first < last ? 1 : -1; i != last + d; i += d)

#define rep(i, N) for (int i = 0; i < int(N); ++i)
#define inv(i, N) for (int i = int(N) - 1; i >= 0; --i)

int main() {
    const lld MOD = 998244353ll;
    lld N, K;
    while (scanf("%lld%lld", &N, &K) != EOF) {
        vector<pair<lld, int> > nums(N);
        rep(i, N) {
            scanf("%lld", &nums[i].first);
            nums[i].second = i;
        }
        sort(allof(nums));
        reverse(allof(nums));
        vector<int> idx(K);
        lld total = 0;
        rep(i, K) {
            total += nums[i].first;
            idx[i] = nums[i].second;
        }
        sort(allof(idx));
        lld cnt = 1;
        rep(i, K - 1) {
            cnt *= idx[i + 1] - idx[i];
            cnt %= MOD;
        }
        printf("%lld %lld\n", total, cnt);
    }
}
