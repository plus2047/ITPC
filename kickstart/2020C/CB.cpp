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
int R, C;
bool check(vector<string>& pic, vector<char>& put, int ci) {
    int c = ci + 'A';
    rep(i, R) rep(j, C) {
        if (pic[i][j] == c) {
            if (i != R - 1 and pic[i + 1][j] != c and
                not put[pic[i + 1][j] - 'A']) {
                return false;
            }
        }
    }
    return true;
}

void solve(int _turn) {
    scanf("%d%d", &R, &C);
    vector<string> pic(R);
    static char buff[64];
    rep(i, R) {
        scanf("%s", buff);
        pic[i] = buff;
    }
    int N = 0;
    vector<char> seen(26, false);
    rep(i, R) rep(j, C) {
        int ci = pic[i][j] - 'A';
        if (not seen[ci]) {
            N++;
            seen[ci] = true;
        }
    }

    string res;
    vector<char> put(26, false);
    rep(t, 26) {
        bool change = false;
        rep(ci, 26) {
            if (not seen[ci] or put[ci]) continue;
            if (check(pic, put, ci)) {
                put[ci] = true;
                change = true;
                res.push_back(ci + 'A');
            }
        }
        if (not change) break;
    }

    if (len(res) != N) res = "-1";

    printf("Case #%d: %s\n", _turn + 1, res.c_str());
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
