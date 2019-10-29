// ===== programing contest template ======
// ===== using standrod: C++ 11 =====

#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>

#include <array>
#include <bitset>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// ===== personal contest env =====

typedef long long int LL;
#define G(_tuple, num) (get<num>(_tuple))
#define len(container) int((container).size())
#define allof(c) (c).begin(), (c).end()
#define frontof(c, k) (c).begin(), (c).begin() + (k)
#define rep(i, N) for (int i = 0; i < int(N); i++)
#define repr(i, begin, end) for (int i = int(begin); i < int(end); i++)
#define repi(i, N) for (int i = int(N) - 1; i >= 0; i--)
#define asmax(m, update) \
    if (m < update) m = update;
#define asmin(m, update) \
    if (m > update) m = update;

template <int group = 20, typename ITER>
void show(const char* note, ITER begin, ITER end) {
#ifdef __LOCAL__
    cout << note;
    for (int i = 1; begin != end; i++) {
        std::cout << *(begin++) << ' ';
        if (i % group == 0 or begin == end) std::cout << std::endl;
    }
#endif  // __LOCAL__
}

#ifdef __LOCAL__
std::clock_t _t0 = 0;
void timer_begin() { _t0 = clock(); }
void timer_end(const char* note) {
    double delta = double(clock() - _t0) / CLOCKS_PER_SEC;
    printf("%s cost: %lf sec.\n", note, delta);
}
#else
#define timer_begin() (void(0))
#define timer_end(note) (void(0))
#endif  // __LOCAL__

// ===== personal contest template =====

// ========== contest code ==========

void solve(int _turn) {

    int N, S;
    scanf("%d%d", &N, &S);
    vector<vector<int>> p2s(N);
    
    const int KEY_SIZE = 10;
    typedef bitset<56> Key;
    unordered_map<Key, int> s2cnt;
    
    rep(i, N) {
        int cnt;
        scanf("%d\n", &cnt);
        rep(j, cnt) {
            int k;
            scanf("%d\n", &k);
            p2s[i].push_back(k);
        }

        sort(allof(p2s[i]));
        Key key;
        for(int n: p2s[i]) {
            key <<= KEY_SIZE;
            key |= Key(n);
        }
        s2cnt[key]++;
    }
    
    LL total = 0;
    rep(i, N) {
        int cnt = len(p2s[i]);
        int subset_cnt = 1 << cnt;
        int unteachable = 0;
        rep(mask, subset_cnt) {
            Key key;
            rep(j, cnt) {
                if((1 << j) & mask) {
                    key <<= KEY_SIZE;
                    key |= Key(p2s[i][j]);
                }
            }
            unteachable += s2cnt[key];
        }
        total += N - unteachable;
    }

    printf("Case #%d: %lld\n", _turn, total);
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
