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
#include <complex>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// ===== personal contest env =====

typedef long long int lld;
#define len(container) int((container).size())
#define allof(c) (c).begin(), (c).end()
#define frontof(c, k) (c).begin(), (c).begin() + (k)
#define rep(i, N) for (int i = 0; i < int(N); ++i)
#define range(i, left, right) for (int i = int(left); i <= int(right); ++i)
#define irange(i, left, right) for (int i = int(right); i >= int(left); --i)

#undef __LOCAL__

template <typename ITER>
void show(const char* note, ITER begin, ITER end) {
#ifdef __LOCAL__
    std::cout << note;
    for (; begin != end; begin++) std::cout << *begin << ' ';
    cout << endl;
#endif  // __LOCAL__
}

void echo(const char* fmt, ...) {
#ifdef __LOCAL__
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
#endif  // __LOCAL__
}

// ===== personal contest template =====

// ========== contest code ==========
bool debug = false;

template <typename FUNC>
double triple_search(FUNC loss_func, double left, double right) {
    // triple search the MIN point of func.
    // the func must has only one min point in [left, right]
    // and it must be monotonicity in each side of this min point.
    const double DELTA = 1E-9;

    while (right - left > DELTA) {
        double t = (right - left) / 3;
        double m1 = left + t, m2 = right - t;
        double loss1 = loss_func(m1), loss2 = loss_func(m2);
        if (loss1 > loss2) {
            left = m1;
        } else {
            right = m2;
        }
    }
    return (left + right) / 2;
}

template <typename FUNC>
double anneal(FUNC loss_func, double left, double right) {
    // using annealing algorithm to find the min point of func.
    // set those values carefully. when it's possible, set them big enough.
    const int EPOCH_NUM = 8, RAND_SEARCH_NUM = 16;
    // and set this small enough.
    const double MIN_STEP = 1E-8, STEP_REDUCE = 0.8;

    double global_x = left;
    double global_min_loss = loss_func(left);

    for (int i = 0; i < EPOCH_NUM; i++) {
        double step = right - left;
        double x = left + step * rand() / RAND_MAX;
        double loss = loss_func(x);
        while (step > MIN_STEP) {
            double x1 = x, loss1 = loss_func(x);
            for (int j = 0; j < RAND_SEARCH_NUM; j++) {
                double x2 = x + (2.0 * rand() / RAND_MAX - 1.0) * step;
                double loss2 = loss_func(x2);
                if (loss2 < loss1) {
                    x1 = x2, loss1 = loss2;
                }
            }
            x = x1, loss = loss1;
            step *= STEP_REDUCE;
        }
        if (loss < global_min_loss) {
            global_x = x, global_min_loss = loss;
        }
    }

    return global_x;
}

typedef complex<double> Point;
const int N_MAX = 16;
int N;
double P, H;
Point obstacles[N_MAX];

double dist(double a, Point obstacle) {
    auto point_dist = [&](double x) {
        return abs(obstacle - Point(x, a * x * (x - P)));
    };
    double x1 = triple_search(point_dist, 0, P / 2);
    double x2 = triple_search(point_dist, P / 2, P);
    return min(point_dist(x1), point_dist(x2));
}

double loss(double a) {
    // return -radius
    a = min(a, 0.0);
    double min_dist = H + a * P * P / 4;
    rep(i, N) {
        min_dist = min(min_dist, dist(a, obstacles[i]));
    }
    return -min_dist;
}

void solve(int _turn) {
    scanf("%d%lf%lf", &N, &P, &H);
    rep(i, N) {
        double x, y;
        scanf("%lf%lf", &x, &y);
        obstacles[i] = Point(x, y);
    }

    double min_a = -H * 4 / (P * P);
    double best_a = anneal(loss, min_a, 0);
    double best_r = -loss(best_a);

    printf("Case #%d: %.10lf\n", _turn, best_r);
    fflush(stdout);
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
