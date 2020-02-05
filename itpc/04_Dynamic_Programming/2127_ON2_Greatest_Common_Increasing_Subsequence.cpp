#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
using namespace std;
const int N = 512;
int n, m;
int s[N], t[N];
int dp[N][N];

int main() {
    scanf("%d\n", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &s[i]);
    scanf("%d\n", &m);
    for (int i = 1; i <= m; i++) scanf("%d", &t[i]);
    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= n; i++) {
        for (int j = 1, now = 0; j <= m; j++) {
            dp[i][j] = s[i] == t[j] ? now + 1 : dp[i - 1][j];
            if (t[j] < s[i]) now = max(now, dp[i - 1][j]);
        }
    }
    int tail = 1;
    for (int i = 2; i <= m; i++)
        if (dp[n][i] > dp[n][tail]) tail = i;
    printf("%d\n", dp[n][tail]);

    vector<int> trace;
    for (int i = n, j = tail; dp[i][j] > 0;) {
        if (s[i] == t[j]) {
            trace.push_back(s[i]);
            if (dp[i][j] == 1) break;
            for (int _j = j - 1;; _j--) {
                if (t[_j] < t[j] and dp[i][_j] == dp[i][j] - 1) {
                    j = _j;
                    break;
                }
            }
        } else {
            i--;
        }
    }

    while (trace.size()) {
        printf("%d ", trace.back());
        trace.pop_back();
    }
    printf("\n");

    return 0;
}
