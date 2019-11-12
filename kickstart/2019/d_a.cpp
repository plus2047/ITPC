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
vector<int> A, P, V;
set<int> odd_idx;
int N, Q;

inline bool is_odd(int n) {
    return bitset<32>(n).count() % 2;
}

inline int get_longest_range() {
    return odd_idx.size() % 2 == 0
               ? N
               : max(N - 1 - *odd_idx.begin(), *odd_idx.rbegin());
}

void solve(int _turn) {
    scanf("%d%d", &N, &Q);
    A.resize(N);
    P.resize(Q);
    V.resize(Q);
    rep(i, N) { scanf("%d", &A[i]); }
    rep(i, Q) { scanf("%d%d", &P[i], &V[i]); }

    odd_idx.clear();
    rep(i, N) {
        if (is_odd(A[i])) {
            odd_idx.insert(i);
        }
    }
    printf("Case #%d:", _turn);

    rep(i, Q) {
        if(is_odd(V[i])) {
            odd_idx.insert(P[i]);
        } else {
            odd_idx.erase(P[i]);
        }
        printf(" %d", get_longest_range());
    }
    printf("\n");
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
