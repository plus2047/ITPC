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
const int N_MAX = 1E4 + 8;
const double POS_MAX = 1000., POS_MIN = -1000.;

int N;
double X[N_MAX], Y[N_MAX], W[N_MAX];
double A[N_MAX], B[N_MAX];

double solve1d(double P[]) {

    vector<pair<double, double>> points(N);
    rep(i, N) { points[i] = {P[i], W[i]}; }
    sort(allof(points));

    double w_left = 0, w_right = 0, s_left = 0, s_right = 0;
    repr(i, 1, N) {
        w_right += points[i].second;
        s_right += points[i].second * (points[i].first - points[0].first);
    }

    double res = s_left + s_right;
    repr(i, 1, N) {
        double delta = points[i].first - points[i - 1].first;

        w_left += points[i - 1].second;
        s_left += w_left * delta;
        s_right -= w_right * delta;
        w_right -= points[i].second;
        
        res = min(res, s_left + s_right);
    }

    return res;
}

void solve(int _turn) {
    scanf("%d", &N);
    rep(i, N) { scanf("%lf%lf%lf", &X[i], &Y[i], &W[i]); }
    rep(i, N) { A[i] = (X[i] + Y[i]) / 2, B[i] = (X[i] - Y[i]) / 2; }
    
    double res = solve1d(A) + solve1d(B);

    printf("Case #%d: %lf\n", _turn, res);
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
