#pragma once
#include <cmath>

namespace contest {

template <typename num>
struct Vec2D {
    num x, y;
    Vec2D operator+(Vec2D& v) { return Vec2D{x + v.x, y + v.y}; }
    Vec2D operator-(Vec2D& v) { return Vec2D{x - v.x, y - v.y}; }
    Vec2D operator*(num t) { return Vec2D{x * t, y * t}; }
    num abs() { return sqrt(x * x + y * y); }
    Vec2D norm() { return (*this) * (1 / this->abs()); }
    num dot(Vec2D& v) { return x * v.x + y * v.y; }
    num det(Vec2D& v) { return x * v.y - y * v.x; }
};

template <typename num>
struct Vec3D {
    num x, y, z;
    Vec3D operator+(Vec3D& v) { return Vec3D{x + v.x, y + v.y, z + v.z}; }
    Vec3D operator-(Vec3D& v) { return Vec3D{x - v.x, y - v.y, z - v.z}; }
    Vec3D operator*(num t) { return Vec3D{x * t, y * t, z * t}; }
    num abs() { return sqrt(x * x + y * y + z * z); }
    Vec3D norm() { return (*this) * (1 / this->abs()); }
    num dot(Vec3D& v) { return x * v.x + y * v.y + z * v.z; }
    Vec3D det(Vec3D& v) {
        return Vec3D{y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
    }
};

template <typename num>
inline double angle(const Vec2D<num> p) {
    return atan2(double(p.y), double(p.x));
}

}  // namespace contest