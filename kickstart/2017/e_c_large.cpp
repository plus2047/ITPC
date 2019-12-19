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
typedef double num;

const num DELTA = 1E-9;

inline int sign(num x) { return (x > DELTA) - (x < -DELTA); }

inline int compare(num x1, num x2) { return sign(x1 - x2); }

struct Vec2D {
    num x, y;
    Vec2D operator+(const Vec2D& v) { return Vec2D{x + v.x, y + v.y}; }
    Vec2D operator-(const Vec2D& v) { return Vec2D{x - v.x, y - v.y}; }
    Vec2D operator*(num t) { return Vec2D{x * t, y * t}; }
    num dot(const Vec2D& v) { return x * v.x + y * v.y; }
    num det(const Vec2D& v) { return x * v.y - y * v.x; }
    num abs() { return sqrt(x * x + y * y); }
    Vec2D norm() { return (*this) * (1 / this->abs()); }
};

struct Vec3D {
    num x, y, z;
    Vec3D operator+(const Vec3D& v) { return Vec3D{x + v.x, y + v.y, z + v.z}; }
    Vec3D operator-(const Vec3D& v) { return Vec3D{x - v.x, y - v.y, z - v.z}; }
    Vec3D operator*(num t) { return Vec3D{x * t, y * t, z * t}; }
    num dot(const Vec3D& v) { return x * v.x + y * v.y + z * v.z; }
    Vec3D det(const Vec3D& v) {
        return Vec3D{y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
    }
    num abs() { return sqrt(x * x + y * y + z * z); }
    Vec3D norm() { return (*this) * (1 / this->abs()); }
};

inline num angle(const Vec2D p) { return atan2(p.y, p.x); }

Vec3D center3D[3];
Vec2D center[3];
num radius[3];
Vec2D intersection_points[2];

inline bool inside(Vec2D p, Vec2D C, num R) {
    return compare((p - C).abs(), R) <= 0;
}

inline bool inside_all(Vec2D p, Vec2D* circle_center, num* circle_radius,
                       int circle_num) {
    rep(i, circle_num) {
        if (not inside(p, circle_center[i], circle_radius[i])) {
            return false;
        }
    }
    return true;
}

inline Vec2D circle_point(Vec2D C, num R, num angle) {
    return Vec2D{C.x + R * cos(angle), C.y + R * sin(angle)};
}

inline bool get_intersection(int circle_idx1, int circle_idx2) {
    num r1 = radius[circle_idx1], r2 = radius[circle_idx2];
    Vec2D& p1 = center[circle_idx1];
    Vec2D& p2 = center[circle_idx2];

    auto v12 = p2 - p1;
    num d12 = v12.abs();
    if (compare(d12, r1 + r2) == 1) {
        return false;
    } else if (compare(d12, fabs(r1 - r2)) <= 0) {
        intersection_points[0] = p1;
        intersection_points[1] = p2;
        return true;
    }

    num a = angle(v12);
    num d = acos((r1 * r1 + d12 * d12 - r2 * r2) / (2 * r1 * d12));

    intersection_points[0] = circle_point(p1, r1, a + d);
    intersection_points[1] = circle_point(p1, r1, a - d);

    return true;
}

bool circle_intersection() {
    rep(i, 3) repr(j, i + 1, 3) {
        if (get_intersection(i, j)) {
            rep(k, 2) {
                if (inside_all(intersection_points[k], center, radius, 3)) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool check(num r) {
    radius[0] = radius[1] = r, radius[2] = 5 * r;
    if (circle_intersection()) return true;
    radius[0] = radius[2] = r, radius[1] = 5 * r;
    if (circle_intersection()) return true;
    radius[1] = radius[2] = r, radius[0] = 5 * r;
    if (circle_intersection()) return true;
    radius[0] = radius[1] = 3 * r, radius[2] = r;
    if (circle_intersection()) return true;
    radius[0] = radius[2] = 3 * r, radius[1] = r;
    if (circle_intersection()) return true;
    radius[1] = radius[2] = 3 * r, radius[0] = r;
    if (circle_intersection()) return true;
    return false;
}

void solve(int _turn) {
    rep(i, 3) {
        num x, y, z;
        scanf("%lf%lf%lf", &x, &y, &z);
        center3D[i] = Vec3D{x, y, z};
    }

    auto vec_ab = center3D[1] - center3D[0];
    auto vec_ac = center3D[2] - center3D[0];

    auto vec_normal = vec_ab.det(vec_ac);
    if (sign(vec_normal.abs()) == 0) {
        auto max_dist = max(
            {vec_ab.abs(), vec_ac.abs(), (center3D[1] - center3D[2]).abs()});
        printf("Case #%d: %lf\n", _turn, max_dist / 6);
        return;
    }

    auto basis1 = vec_ab * (1 / vec_ab.abs());
    auto basis2 = vec_normal.det(vec_ab);
    basis2 = basis2 * (1 / basis2.abs());

    rep(i, 3) {
        center[i] = Vec2D{center3D[i].dot(basis1), center3D[i].dot(basis2)};
        // printf("point: %lf, %lf\n", center[i].x, center[i].y);
    }

    num left = 0, right = 1E4;
    while (right - left > DELTA) {
        num mid = (left + right) / 2;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }

    printf("Case #%d: %lf\n", _turn, left);
}

// ===== kickstart template =====
int main() {
    int T = 1;
    scanf("%d", &T);
    rep(t, T) { solve(t + 1); }
}
