#ifndef HITTABLE_LIST_H
# define HITTABLE_LIST_H

#include "hittable.h"
#include <memory>
#include <vector>

class hittableList : hittable {
 public:
    hittableList() {}
    explicit hittableList(std::shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(std::shared_ptr<hittable> object) { objects.push_back(object); }

    virtual bool hit(const ray& r, double tMin, double tMax, hitRecord& rec) const override;

 private:
    std::vector< std::shared_ptr<hittable> > objects;
};

bool hittableList::hit(const ray& r, double tMin, double tMax, hitRecord& rec) const {
    hitRecord tmpRec;
    bool hitAnything = false;
    auto closestSoFar = tMax;

    for (const auto& object : objects) {
        if (object->hit(r, tMin, closestSoFar, tmpRec)) {
            hitAnything = true;
            closestSoFar = tmpRec.t;
            rec = tmpRec;
        }
    }

    return hitAnything;
}

#endif
