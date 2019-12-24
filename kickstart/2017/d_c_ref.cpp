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
#define REP(i, n) for (int i = 0; i < int(n); ++i)
#define REPE(i, a, b) for (int i = (a); i <= int(b); ++i)
#define SZ(x) ((int)(x).size())
#define ALL(x) x.begin(), x.end()
#define PB push_back
#define EB emplace_back
using LL = long long;
using PII = pair<int, int>;
#define F first
#define S second

using CD = complex<double>;

inline CD point(double p, double a, double x) { return CD(x, a * x * (x - p)); }

double search(double p, double a, double x, double y, double l, double r) {
    double ret = 1e9;
    REP(i, 50) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        CD p1 = point(p, a, m1);
        CD p2 = point(p, a, m2);
        double d1 = abs(p1 - CD(x, y)), d2 = abs(p2 - CD(x, y));
        if (d1 > d2)
            l = m1;
        else
            r = m2;
        ret = min(ret, min(d1, d2));
    }
    return ret;
}

double dis(double p, double a, double x, double y) {
    return min(search(p, a, x, y, 0, p / 2), search(p, a, x, y, p / 2, p));
}

double ub;

double ans;

int n;
double p, h;
double x[10], y[10];

double eval(double a) {
    if (a > 0) a = 0;
    double top = a * p * p / -4;
    double r = h - top;
    REP(i, n) r = min(r, dis(p, a, x[i], y[i]));
    ans = max(ans, r);
    return r;
}

void go(double a, double step) {
    if (step < 1e-9) return;
    if (a > 0) a = 0;
    double na = a;
    double v = eval(a);
    while (abs(step) > 1E-9) {
        REP(i, 10) {
            double del = (2.0 * rand() / RAND_MAX - 1.0) * step;
            double ta = a + del;
            double tv = eval(ta);
            if (tv > v) {
                v = tv;
                na = ta;
            }
        }
        a = na;
        step *= 0.9;
    }
}

void solve() {
    scanf("%d%lf%lf", &n, &p, &h);
    REP(i, n) scanf("%lf%lf", &x[i], &y[i]);
    ub = -h * 4 / (p * p);
    ans = 0;
    REP(j, 64) go(ub / j, -ub * 4);
    printf("%.12f\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; ++kase) {
        printf("Case #%d: ", kase);
        solve();
    }
    return 0;
}
