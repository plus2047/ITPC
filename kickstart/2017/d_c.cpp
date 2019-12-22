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
const int N_MAX = 32;
int N;
double P, H;
double X[N_MAX], Y[N_MAX];
double PI = 3.1415926535;
double delta = 1E-12;

double get_a(double x, double y) { return y / (x * (x - P)); }
int sign(double x) { return (x > delta) - (x < -delta); }

int sign_da(double x, double y, double r, double theta) {
    double c = cos(theta), s = sin(theta);
    double x_ = x - r * c, y_ = y + r * s;
    double dx_ = r * s, dy_ = r * c;
    return sign(dy_ * (x_ * x_ - P * x_) - (2 * x_ - P) * dx_ * y_);
}

template <typename FUNC>
double binary_solve(FUNC func, double left, double right) {
    int sign_left = func(left), sign_right = func(right);
    while (right - left > delta) {
        double mid = (left + right) / 2;
        int sig = func(mid);
        (sig * sign_left > 0 ? left : right) = mid;
    }
    return left;
}

inline pair<double, double> get_block(int obs_idx, double r) {
    double x = X[obs_idx], y = Y[obs_idx];
    // always has x < P / 2
    double min_a, max_a;
    double ceil_a = get_a(P / 2, H - r);
    if (y + r > H or x - r < 0) {
        min_a = ceil_a - 1;
    } else {
        double theta = binary_solve(
            [&](double theta) { return sign_da(x, y, r, theta); }, 0, PI / 2);
        min_a = get_a(x - r * cos(theta), y + r * sin(theta));
    }
    if (y - r < 0) {
        max_a = 1;
    } else {
        double theta_min = r + x > P ? PI * 3 / 2 - asin((P - x) / r) : PI;
        theta_min += 1E-6;  // avoid NaN
        double theta =
            binary_solve([&](double theta) { return sign_da(x, y, r, theta); },
                         theta_min, PI * 3 / 2);
        double _x = x - r * cos(theta), _y = y + r * sin(theta);
        max_a = get_a(_x, _y);
    }
    return {min_a, max_a};
}

inline bool valid(vector<pair<double, double>>& block, double left,
                  double right) {
    sort(allof(block));
    double min_left = block[0].first, max_right = block[0].second;
    double curr_right = block[0].second;
    int n = len(block);
    range(i, 1, n - 1) {
        double i_left = block[i].first, i_right = block[i].second;
        min_left = min(min_left, i_left);
        max_right = max(max_right, i_right);
        if (i_left > curr_right and i_left > left and i_left < right) {
            echo("%d left: %lf, right: %lf\n", i, i_left, curr_right);
            return true;
        }
        curr_right = max(curr_right, i_right);
    }
    echo("min_left: %lf, left: %lf, max_right: %lf, right: %lf\n", min_left,
         left, max_right, right);
    return min_left > left - delta or max_right < right + delta;
}

void solve(int _turn) {
    scanf("%d%lf%lf", &N, &P, &H);
    rep(i, N) {
        scanf("%lf%lf", &X[i], &Y[i]);
        X[i] = min(X[i], P - X[i]);  // mirror to "left side"
    }

    double left = 0, right = H;
    vector<pair<double, double>> block;

    while (right - left > delta) {
        double r = (left + right) / 2;
        double ceil_a = get_a(P / 2, H - r);
        block.clear();
        rep(i, N) { block.push_back(get_block(i, r)); }
        bool succ = valid(block, ceil_a, 0);
        echo("r: %lf, ceil_a: %lf, succ: %d \n", r, ceil_a, int(succ));
        rep(i, N) {
            echo("block: (%lf, %lf)\n", block[i].first, block[i].second);
        }
        (succ ? left : right) = r;
    }

    printf("Case #%d: %.12lf\n", _turn, left);
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
