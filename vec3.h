#ifndef VEC3_H
# define VEC3_H

#include <cmath>
#include <iostream>

class vec3 {
 private:
    double e[3];

 public:
    vec3() : e{0, 0, 0} {}
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }
    vec3& operator+=(const vec3 &v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }
    vec3& operator*=(const double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }
    vec3& operator/=(const double t) {
        return *this *= 1 / t;
    }

    inline static vec3 random(void) { return vec3(RandomDouble(), RandomDouble(), RandomDouble()); }
    inline static vec3 random(double min, double max) {
        return vec3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max));
    }

    double length() const { return std::sqrt(lengthSquared()); }
    double lengthSquared() const { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }
    bool nearZero(void) const {
        const auto s = 1e-8;
        return (fabs(x()) < s) && (fabs(y()) < s) && (fabs(z()) < s);
    }
};

// Type aliases
using point3 = vec3;
using color = vec3;

// utility

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

inline vec3 operator*(const vec3 &v, double t) {
    return vec3(v.x() * t, v.y() * t, v.z() * t);
}

inline vec3 operator*(double t, const vec3 &v) {
    return v * t;
}

inline vec3 operator/(const vec3 &v, double t) {
    return v * (1/t);
}

inline double dot(const vec3 &u, const vec3 &v) {
    return u.x()*v.x() + u.y()*v.y() + u.z()*v.z();
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(
        u.y()*v.z() - u.z()*v.z(),
        u.z()*v.x() - u.x()*v.z(),
        u.x()*v.y() - u.y()*v.x());
}

inline vec3 unitVector(vec3 v) {
    return v / v.length();
}

vec3 randomInUnitSphere(void) {
    auto p = vec3::random(-1, 1);
    return unitVector(p);
}

vec3 randomUnitVector(void) { return randomInUnitSphere(); }

vec3 randomInHemiSphere(const vec3& normal) {
    vec3 inUnitSphere = randomInUnitSphere();
    if (dot(inUnitSphere, normal) > 0.0) return inUnitSphere;
    return -inUnitSphere;
}

vec3 reflect(const vec3& v, const vec3& n) { return v - 2*dot(v, n)*n; }

#endif
