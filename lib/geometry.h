#pragma once
#include <cmath>

namespace contest {

template <typename num>
struct Vec2D {
    num x, y;
    Vec2D operator+(const Vec2D& v) const { return Vec2D{x + v.x, y + v.y}; }
    Vec2D operator-(const Vec2D& v) const { return Vec2D{x - v.x, y - v.y}; }
    Vec2D operator*(num t) const { return Vec2D{x * t, y * t}; }
    num abs() const { return sqrt(x * x + y * y); }
    Vec2D norm() const { return (*this) * (1 / this->abs()); }
    num dot(const Vec2D& v) const { return x * v.x + y * v.y; }
    num det(const Vec2D& v) const { return x * v.y - y * v.x; }
};

template <typename num>
struct Vec3D {
    num x, y, z;
    Vec3D operator+(const Vec3D& v) const { return Vec3D{x + v.x, y + v.y, z + v.z}; }
    Vec3D operator-(const Vec3D& v) const { return Vec3D{x - v.x, y - v.y, z - v.z}; }
    Vec3D operator*(num t) const { return Vec3D{x * t, y * t, z * t}; }
    num abs() const { return sqrt(x * x + y * y + z * z); }
    Vec3D norm() const { return (*this) * (1 / this->abs()); }
    num dot(const Vec3D& v) const { return x * v.x + y * v.y + z * v.z; }
    Vec3D det(const Vec3D& v) const {
        return Vec3D{y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
    }
};

template <typename num>
inline double angle(const Vec2D<num> p) {
    return atan2(double(p.y), double(p.x));
}

// get quadrant
// return 1,2,3,4
// WARN this function would assign quadrant for points on axes
// y = 0 and x > 0 return 1
// x = 0 and y > 0 return 2
// y = 0 and x < 0 return 3
// x = 0 and y < 0 return 4 
// x = 0 and y = 0 return 0
template <typename num>
inline int quadrant(Vec2D<num> p) {
    if((p.x > 0 and p.y > 0) or (p.x > 0 and p.y == 0)) return 1;
    if((p.x < 0 and p.y > 0) or (p.x == 0 and p.y > 0)) return 2;
    if((p.x < 0 and p.y < 0) or (p.x < 0 and p.y == 0)) return 3;
    if((p.x > 0 and p.y < 0) or (p.x == 0 and p.y < 0)) return 4;
    return 0;  // only for (0, 0)
}

template<typename num>
void polar_sort(std::vector<Vec2D<num>>& vec) {
    sort(vec.begin(), vec.end(), [](const Vec2D<num>& a, const Vec2D<num>& b) {
        int qa = quadrant(a), qb = quadrant(b);
        return qa == qb ? a.det(b) > 0 : qa < qb;
    });
}

}  // namespace contest