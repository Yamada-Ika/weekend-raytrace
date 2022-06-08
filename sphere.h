#ifndef SPHERE_H
# define SPHERE_H

#include "rt_weekend.h"
#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
 private:
    point3 center;
    double radius;
    std::shared_ptr<material> matPtr;

 public:
    sphere() {}
    sphere(point3 cen, double r, std::shared_ptr<material> m) : center(cen), radius(r), matPtr(m) {}
    virtual bool hit(const ray& r, double tMin, double tMax, hitRecord& rec) const override;
};

bool sphere::hit(const ray& r, double tMin, double tMax, hitRecord& rec) const {
    vec3 originToCenter = r.origin() - center;
    auto a = r.direction().lengthSquared();
    auto halfB = dot(originToCenter, r.direction());
    auto c = originToCenter.lengthSquared() - radius*radius;

    auto discriminant = halfB*halfB - a*c;
    if (discriminant < 0) {
        return false;
    }
    auto sqrtD = std::sqrt(discriminant);

    auto t = (-halfB - sqrtD) / a;
    if (t < tMin || tMax < t) {
        t = (-halfB + sqrtD) / a;
        if (t < tMin || tMax < t) {
            return false;
        }
    }

    rec.t = t;
    rec.pos = r.at(rec.t);
    vec3 outwardNormal = (rec.pos - center) / radius;
    rec.setFaceNormal(r, outwardNormal);
    rec.matPtr = matPtr;

    return true;
}

#endif
