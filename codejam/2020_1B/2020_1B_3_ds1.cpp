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
    int R, S;
    scanf("%d%d", &R, &S);
    int N = R * S;

    string start, stop;
    rep(i, S) {
        rep(j, R) { start.push_back('1' + j); }
    }
    rep(j, R) {
        rep(i, S) { stop.push_back('1' + j); }
    }
    // cout << start << endl << stop << endl;

    map<string, tuple<string, int, int> > seen;
    queue<string> que;
    que.push(start);

    while (que.size()) {
        string s = que.front();
        que.pop();

        for (int i = 1; i < N; i++) {
            for (int j = 1; i + j <= N; j++) {
                string _s = s.substr(i, j) + s.substr(0, i) +
                            s.substr(i + j, N - i - j);
                if (seen.count(_s)) continue;
                seen[_s] = {s, i, j};
                if (_s == stop) break;
                que.push(_s);
            }
        }
    }

    vector<pair<int, int>> act;
    while(stop != start) {
        string s;
        int i, j;
        tie(s, i, j) = seen[stop];
        act.push_back({i, j});
        stop = s;
    }
    reverse(allof(act));

    printf("Case #%d: %d\n", _turn + 1, len(act));
    for(auto& p: act) {
        printf("%d %d\n", p.first, p.second);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    rep(t, T) { solve(t); }
}
