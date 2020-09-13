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
const int V_NUM = 512, V_LEN = 32, S_LEN = 4096, S_NUM = 8;
char words[V_NUM][V_LEN], sents[S_NUM][S_LEN];
int wsize[V_NUM], ssize[S_NUM];

inline bool eq(char* w, char* s) {
    static int8_t cnt[26];
    memset(cnt, 0, sizeof(cnt));
    int size = 0;
    while (*w) {
        size++;
        cnt[*w++ - 'a']++;
    }
    while (size-- and *s) {
        cnt[*s++ - 'a']--;
    }
    for (int8_t *_c = cnt, i = 0; i < 26; i++, _c++) {
        if (*_c != 0) return false;
    }
    return true;
}

void solve(int _turn) {
    int V, S;
    scanf("%d%d", &V, &S);
    rep(i, V) {
        scanf("%s", words[i]);
        wsize[i] = strlen(words[i]);
    }
    rep(i, S) {
        scanf("%s", sents[i]);
        ssize[i] = strlen(sents[i]);
    }

    const lld MOD = 1E9 + 7;
    vector<lld> dp, res;
    rep(i, S) {
        char* s = sents[i];
        int N = ssize[i];
        dp.clear(), dp.resize(N + 1);
        dp[N] = 1;
        for (int j = N - 1; j >= 0; j--) {
            rep(k, V) {
                if (eq(words[k], s + j)) {
                    dp[j] = (dp[j] + dp[j + wsize[k]]) % MOD;
                }
            }
        }
        res.push_back(dp[0]);
    }

    printf("Case #%d:", _turn + 1);
    for (auto v : res) printf(" %lld", v);
    printf("\n");
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
