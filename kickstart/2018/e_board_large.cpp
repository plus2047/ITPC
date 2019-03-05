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
#define repi(i, N) for (int i = int(N) - 1; i >= 0; i++)

#ifdef __LOCAL__
#define printf(args...) (fprintf(stderr, args), printf(args))
std::clock_t _t0 = 0;
void timer() { _t0 = clock(); }
void timer(const char* note) {
    double delta = double(clock() - _t0) / CLOCKS_PER_SEC;
    printf("%s cost: %lf sec.\n", note, delta);
}
#endif  // __LOCAL__

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

// ===== personal contest template =====
template <typename NUM>
struct FenwickTree2D {
    std::vector<std::vector<NUM>> tree;
    int SIZE0, SIZE1;
    FenwickTree2D(int size0, int size1)
        : SIZE0(size0 + 1),
          SIZE1(size1 + 1),
          tree(size0 + 2, std::vector<NUM>(size1 + 2)) {}

    inline void add(int idx0, int idx1, NUM val) {
        assert(idx0 >= 0 and idx0 <= SIZE0);
        assert(idx1 >= 0 and idx1 <= SIZE1);
        for (int i = idx0 + 1; i <= SIZE0; i += (i & -i)) {
            for (int j = idx1 + 1; j <= SIZE1; j += (j & -j)) {
                tree[i][j] += val;
            }
        }
    }

    inline NUM prefix_sum(int last0, int last1) {
        if (last0 < 0 or last1 < 0) return 0;
        if (last0 > SIZE0) last0 = SIZE0;
        if (last1 > SIZE1) last1 = SIZE1;
        NUM res = 0;
        for (int i = last0 + 1; i > 0; i -= (i & -i)) {
            for (int j = last1 + 1; j > 0; j -= (j & -j)) {
                res += tree[i][j];
            }
        }
        return res;
    }
};

// ========== contest code ==========
int N, N3;
vector<int> A, B;

typedef array<int, 3> Sum;
vector<Sum> sumA, sumB;
int n_sum;
void get_sum(vector<int>& nums, vector<Sum>& sum_array) {
    vector<int> idx(N3);
    rep(i, N3) idx[i] = i / N;
    sum_array.clear();
    do {
        Sum _sum = {0, 0, 0};
        rep(i, N3) { _sum[idx[i]] += nums[i]; }
        sum_array.push_back(_sum);
    } while (next_permutation(allof(idx)));
    n_sum = len(sum_array);
}

vector<int> B_vals;
int num_B_vals;
void get_B_vals() {
    B_vals.clear();
    set<int> sums;
    rep(i, sumB.size()) { sums.insert(sumB[i][0]); }
    B_vals.insert(B_vals.end(), allof(sums));
    num_B_vals = len(B_vals);
}
int great_eq(int val) {
    return lower_bound(allof(B_vals), val) - B_vals.begin();
}

vector<int> cnt2[3], cnt3;
void get_cnt3() {
    cnt3.resize(n_sum);
    FenwickTree2D<int> ft(num_B_vals, num_B_vals);
    for (int idxA = 0, idxB = 0; idxA < n_sum; idxA++) {
        while (idxB < n_sum and sumB[idxB][0] < sumA[idxA][0]) {
            int i1 = great_eq(sumB[idxB][1]), i2 = great_eq(sumB[idxB][2]);
            ft.add(i1, i2, 1);
            idxB++;
        }
        int j1 = great_eq(sumA[idxA][1]) - 1, j2 = great_eq(sumA[idxA][2]) - 1;
        cnt3[idxA] = ft.prefix_sum(j1, j2);
    }
}
void get_cnt2(int c1, int c2, int res) {
    FenwickTree2D<int> ft(num_B_vals, num_B_vals);
    for (int idxB = 0; idxB < n_sum; idxB++) {
        int i1 = great_eq(sumB[idxB][c1]), i2 = great_eq(sumB[idxB][c2]);
        ft.add(i1, i2, 1);
    }
    cnt2[res].resize(n_sum);
    for (int idxA = 0; idxA < n_sum; idxA++) {
        int j1 = great_eq(sumA[idxA][c1]) - 1,
            j2 = great_eq(sumA[idxA][c2]) - 1;
        cnt2[res][idxA] = ft.prefix_sum(j1, j2);
    }
}

void solve(int _turn) {
    scanf("%d", &N);
    N3 = N * 3;

    A.resize(N3), B.resize(N3);
    rep(i, N3) scanf("%d", &A[i]);
    rep(i, N3) scanf("%d", &B[i]);

    get_sum(A, sumA), get_sum(B, sumB);
    sort(allof(sumA)), sort(allof(sumB));

    get_B_vals();

    get_cnt3();
    get_cnt2(0, 1, 0), get_cnt2(0, 2, 1), get_cnt2(1, 2, 2);

    double best = 0;

    for (int i = 0; i < n_sum; i++) {
        int win_num = -2 * cnt3[i];
        rep(j, 3) win_num += cnt2[j][i];
        best = max(best, double(win_num) / n_sum);
    }

    printf("Case #%d: %lf\n", _turn, best);
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
