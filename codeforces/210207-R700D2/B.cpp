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
typedef long long int lld;

void solve() {
    lld A, B, n;
    scanf("%lld%lld%lld", &A, &B, &n);

    vector<pair<lld, lld> > ms(n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &ms[i].first);
    }
    for (int i = 0; i < n; i++) {
        scanf("%lld", &ms[i].second);
    }

    sort(ms.begin(), ms.end());
    bool succ = true;
    for (int i = 0; i < n and succ; i++) {
        lld a = ms[i].first, b = ms[i].second;
        lld k = (b % A ? 1 : 0) + b / A;
        B -= a * k;
        if (B <= 0 and (i != n - 1 or B + a <= 0)) {
            succ = false;
        }
    }
    printf(succ ? "YES\n" : "NO\n");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
}
