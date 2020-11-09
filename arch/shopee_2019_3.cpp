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

vector<pair<int, int> > res;
string p, t;
int m, n, start;

void dfs(int i, int j) {
    if (i == m) {
        res.push_back({start, j - start});
    } else if (j == n) {
        return;
    } else {
        while (p[i] != '*' and i < m and j < n) {
            if (p[i] != t[j]) {
                return;
            } else {
                i++, j++;
            }
        }
        if (p[i] == '*') {
            dfs(i, j + 1);
            dfs(i + 1, j + 1);
            dfs(i + 1, j);
        } else {
            dfs(i, j);
        }
    }
}

int main() {
    cin >> p >> t;
    m = int(p.size()), n = int(t.size());
    res.clear();
    rep(j, n) {
        start = j;
        dfs(0, j);
    }
    sort(allof(res));
    rep(i, len(res)) {
        if ((i == 0 or res[i] != res[i - 1]) and res[i].second != 0) {
            printf("%d %d\n", res[i].first, res[i].second);
        }
    }
    if (res.empty()) {
        printf("-1 0\n");
    }
}
