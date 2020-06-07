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
    int M, N;
    scanf("%d%d", &M, &N);
    vector<int> K(N), L(N);
    vector<vector<int> > A(N), C(N);
    rep(i, N) {
        scanf("%d%d", &K[i], &L[i]);
        int t;
        rep(j, K[i]) {
            scanf("%d", &t);
            A[i].push_back(t);
        }
        rep(j, K[i] - 1) {
            scanf("%d", &t);
            C[i].push_back(t);
        }
    }

    const int C_MAX = 1024;
    vector<int> att(C_MAX);
    rep(i, N) {
        inv(j, C_MAX) {
            int cost = 0;
            for(int lv = L[i]; lv <= K[i]; lv++) {
                int delta = A[i][lv - 1];
                if(cost <= j) {
                    att[j] = max(att[j], att[j - cost] + delta);
                } else {
                    break;
                }
                if(lv != K[i]) {
                    cost += C[i][lv - 1];
                }
            }
        }
    }

    int res = *max_element(frontof(att, M + 1));
    printf("Case #%d: %d\n", _turn + 1, res);
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
