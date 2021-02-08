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

const int N = 1024;
char mp[N][N];

// copy from froggyzhang
void solve() {
    int m, n;
    scanf("%d%d", &n, &m);
    m++;
    for (int i = 1; i <= n; ++i) {
        scanf("%s", mp[i] + 1);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j) continue;
            if (mp[i][j] == mp[j][i]) {
                printf("YES\n");
                int tp = i;
                while (m--) {
                    printf("%d ", tp), tp ^= i ^ j;
                }
                printf("\n");
                return;
            }
        }
    }
    if (m & 1) {
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i == j || i + 1 == j) continue;
                int tp, o, z;
                if (mp[j][i] == mp[i][i + 1])
                    o = i, z = i + 1;
                else if (mp[j][i + 1] == mp[i + 1][i])
                    o = i + 1, z = i;
                else
                    continue;
                printf("YES\n");
                if ((m >> 1) & 1)
                    tp = z;
                else
                    tp = o;
                for (int k = 0; k < (m >> 1); ++k) {
                    printf("%d ", tp), tp ^= o ^ z;
                }
                for (int k = 0; k < (m >> 1); ++k) {
                    printf("%d ", tp), tp ^= o ^ j;
                }
                printf("%d\n", ((m >> 1) & 1) ? j : o);
                return;
            }
        }
        printf("NO\n");
        return;
    }
    printf("YES\n");
    int tp = 1;
    while (m--) {
        printf("%d ", tp), tp ^= 1 ^ 2;
    }
    printf("\n");
}

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        solve();
    }
}
