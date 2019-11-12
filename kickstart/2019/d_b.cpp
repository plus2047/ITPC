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
#define vec2d(type, name, m, n, v) \
    vector<vector<type>> name = vector<vector<type>>(m, vector<type>(n, v))

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
const int MAXN = 1E5 + 8;
int N, G, M;

inline int dist(int left, int right) { return (right - left + N) % N; }

inline int move(int start, int delta) { return ((start + delta) % N + N) % N; }

void solve(int _turn) {
    scanf("%d%d%d", &N, &G, &M);

    vector<vector<int>> a(N), s(N);

    int H;
    char buff[16];
    rep(i, G) {
        scanf("%d%s\n", &H, buff);
        H = move(H - 1, buff[0] == 'A' ? -M : M);  // H - 1 for 0-index
        (buff[0] == 'A' ? a : s)[H].push_back(i);
    }

    vector<int> ap, sp;
    rep(i, N) {
        if (a[i].size()) ap.push_back(i);
        if (s[i].size()) sp.push_back(i);
    }

    vector<int> res(G);

    vector<int> s_next(N);
    if (sp.size()) {
        for (int n = 0, i = 0; n < N; n++) {
            while (sp[i] < n and i < len(sp)) i++;
            s_next[n] = i == len(sp) ? sp[0] : sp[i];
        }
    }

    vector<int> a_prev(N);
    if (ap.size()) {
        for (int n = N - 1, i = len(ap) - 1; n >= 0; n--) {
            while (ap[i] > n and i >= 0) i--;
            a_prev[n] = i == -1 ? ap.back() : ap[i];
        }
    }

    vector<int> a_cnt(N), s_cnt(N);
    rep(n, N) {
        int INF = N + 1;
        int da = ap.empty() ? INF : dist(a_prev[n], n);
        int ds = sp.empty() ? INF : dist(n, s_next[n]);

        if (min(da, ds) > M) continue;

        if (da <= ds) {
            a_cnt[a_prev[n]]++;
        }
        if (ds <= da) {
            s_cnt[s_next[n]]++;
        }
    }

    rep(n, N) {
        if (a_cnt[n]) {
            for (int g : a[n]) res[g] += a_cnt[n];
        }
        if (s_cnt[n]) {
            for (int g : s[n]) res[g] += s_cnt[n];
        }
    }

    printf("Case #%d:", _turn);
    for (int n : res) printf(" %d", n);
    printf("\n");
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
