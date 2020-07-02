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
    llu u, v;
    while (scanf("%llu%llu", &u, &v) != EOF) {
        if (u > v or (u & 1llu) != (v & 1llu)) {
            printf("-1\n");
            continue;
        }
        vector<int> cnt(65);
        rep(i, 64) {
            llu u_ = u & (1llu << i), v_ = v & (1llu << i);
            if (u_ and v_) {
                cnt[i]++;
            } else if (v_) {  // sum
                cnt[i - 1] += 2;
            } else if (u_) {  // xor
                cnt[i]++;
                cnt[i - 1] -= 2;
            }
        }
        rep(i, 64) {
            while (cnt[i] < 0) {
                cnt[i + 1] -= 2;
                cnt[i] += 4;
            }
            cnt[i + 1] += (cnt[i] / 4) * 2;
            cnt[i] %= 4;
        }
        if (cnt[64] >= 0) {
            vector<llu> res(*max_element(allof(cnt)));
            inv(i, 64) {
                rep(j, cnt[i]) { res[j] |= 1llu << i; }
            }
            printf("%d\n", len(res));
            for (llu n : res) {
                printf("%llu ", n);
            }
            printf("\n");
        } else {
            printf("-1\n");
        }
    }
}
