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

const int N = 102400;
int a[N], b[N], c[N];
int last[N], before[N], pos[N];

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) scanf("%d", &a[i]);
        for (int i = 0; i < n; i++) scanf("%d", &b[i]);

        for (int i = 0; i <= n; i++) last[i] = before[i] = -1;
        for (int i = 0; i < m; i++) {
            scanf("%d", &c[i]);
            before[i] = last[c[i]];
            last[c[i]] = i;
            pos[i] = -1;
        }

        bool succ = true;
        for (int i = 0; i < n and succ; i++) {
            if (a[i] != b[i]) {
                int x = b[i];
                if (last[x] != -1) {
                    pos[last[x]] = i;
                    last[x] = before[last[x]];
                } else {
                    succ = false;
                }
            }
        }
        for (int i = 0; i < n and succ; i++) {
            if (a[i] == b[i]) {
                int x = b[i];
                if (last[x] != -1) {
                    pos[last[x]] = i;
                    last[x] = before[last[x]];
                }
            }
        }

        if (not succ or pos[m - 1] == -1) {
            printf("NO\n");
        } else {
            printf("YES\n");
            for (int i = 0; i < m; i++) {
                if (pos[i] == -1) {
                    printf("%d ", pos[m - 1] + 1);
                } else {
                    printf("%d ", pos[i] + 1);
                }
            }
            printf("\n");
        }
    }
}
