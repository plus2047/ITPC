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
#define len(c) int((c).size())
#define allof(container) (container).begin(), (container).end()
#define rep(i, N) for (int i = 0; i < int(N); i++)
#define repr(i, begin, end) for (int i = int(begin); i < int(end); i++)
#define repi(i, N) for (int i = int(N) - 1; i >= 0; i--)

template <int group = 16, typename ITER>
void show(const char* note, ITER begin, ITER end) {
#ifdef __LOCAL__
    printf("%s", note);
    int i = 1;
    for (; begin != end; i++) {
        std::cout << *(begin++) << ' ';
        if (i % group == 0) std::cout << std::endl;
    }
    if (i % group != 1) std::cout << std::endl;
#endif  // __LOCAL__
}

// ===== personal contest template =====

// ========== contest code ==========
inline void get_sum(vector<int>& num, vector<int>& group, vector<int>& total) {
    for (int i = 0; i < int(num.size()); i++) {
        total[group[i]] += num[i];
    }
}

void solve(int _turn) {
    int N, N3;
    scanf("%d", &N);
    N3 = N * 3;
    vector<int> A(N3), B(N3);
    rep(i, N3) scanf("%d", &A[i]);
    rep(i, N3) scanf("%d", &B[i]);

    vector<int> groupA(N3);
    rep(i, 3) fill(groupA.begin() + i * N, groupA.begin() + i * N + N, i);
    vector<int> groupB = groupA;

    double best = 0;
    vector<int> sumA(3), sumB(3);
    do {
        int win = 0, lose = 0;
        fill(allof(sumA), 0);
        get_sum(A, groupA, sumA);
        do {
            fill(allof(sumB), 0);
            get_sum(B, groupB, sumB);
            int win_cnt = 0;
            rep(i, 3) if (sumA[i] > sumB[i]) win_cnt++;
            if (win_cnt >= 2) {
                win++;
            } else {
                lose++;
            }
        } while (next_permutation(allof(groupB)));
        best = max(best, double(win) / (win + lose));
    } while (next_permutation(allof(groupA)));

    printf("Case #%d: %lf\n", _turn, best);
    fprintf(stderr, "Case #%d: %lf\n", _turn, best);
}

// ===== kickstart template =====
int main() {
#ifdef __LOCAL__  // define in building command.
    freopen("_kickstart.in", "r", stdin);
    // freopen("_debug.in", "r", stdin);
    freopen("_main_cpp.out", "w", stdout);
#endif
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
