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

lld N, K, D;
const int N_LIM = 204, S_LIM = 604;
const lld INF = INT64_MAX / 3;

lld dp[N_LIM][N_LIM][S_LIM];

int main() {
    while (scanf("%lld%lld%lld", &N, &K, &D) != EOF) {
        vector<lld> A(N), C(N), S(N);
        for (int i = 0; i < N; i++) scanf("%lld", &A[i]);
        for (int i = 0; i < N; i++) scanf("%lld", &C[i]);
        for (int i = 0; i < N; i++) scanf("%lld", &S[i]);

        // init range with size == 1
        for (int i = 0; i < N; i++) {
            dp[i][i][0] = 0;
            for (int s = 1; s < S_LIM; s++) {
                dp[i][i][s] = INF;
            }
            dp[i][i][S[i]] = 0;
        }

        // init range with size == 2
        for (int i = 0; i < N; i++) {
            dp[i - 1][i][0] = 0;
            for (int s = 1; s < S_LIM; s++) {
                dp[i - 1][i][s] = INF;
            }
            dp[i - 1][i][S[i - 1]] = 0;
            dp[i - 1][i][S[i]] = 0;
            dp[i - 1][i][S[i] + S[i - 1]] =
                abs(A[i] - A[i - 1]) <= D ? 0 : min(C[i], C[i - 1]);
        }

        for (int size = 3; size <= N; size++) {
            for (int i = 0, j = size - 1; j < N; i++, j++) {
                dp[i][j][0] = 0;
                for (int s = 1; s < S_LIM; s++) {
                    dp[i][j][s] = min(dp[i + 1][j][s], dp[i][j - 1][s]);
                    if (S[i] + S[j] > s) continue;
                    lld x = dp[i + 1][j - 1][s - S[i] - S[j]];
                    x += abs(A[i] - A[j]) <= D ? 0 : min(C[i], C[j]);
                    dp[i][j][s] = min(dp[i][j][s], x);
                }
            }
        }

        lld res = 0, k = -1;
        for (lld s = 0; s < S_LIM; s++) {
            if (dp[0][N - 1][s] <= K and s > res) {
                res = s;
                k = dp[0][N - 1][s];
            }
        }
        vector<pair<int, lld> > modify;
        vector<int> select;
        for (lld i = 0, j = N - 1, s = res; s > 0;) {
            if (i == j) {
                s = 0;
                select.push_back(i);
            } else if (dp[i][j][s] == dp[i + 1][j][s]) {
                i++;
            } else if (dp[i][j][s] == dp[i][j - 1][s]) {
                j--;
            } else {
                select.push_back(i), select.push_back(j);
                s -= S[i] + S[j];
                if (abs(A[i] - A[j]) > D) {
                    if (C[i] > C[j]) {
                        modify.push_back({j, A[i]});
                    } else {
                        modify.push_back({i, A[j]});
                    }
                }
                i++, j--;
            }
        }
        sort(modify.begin(), modify.end());
        sort(select.begin(), select.end());

        printf("%lld\n", res);
        printf("%d\n", int(modify.size()));
        for (auto& p : modify) {
            printf("%d %lld\n", p.first + 1, p.second);
        }
        printf("%d\n", int(select.size()));
        for (int i : select) {
            printf("%d ", i + 1);
        }
        printf("\n");
    }
}
