#ifndef CAMERA_H
# define CAMERA_H

#include "rt_weekend.h"

class camera {
 public:
    camera() {
        auto aspectRatio = 16.0 / 9.0;
        auto viewPortHeight = 2.0;
        auto viewPortWidth = aspectRatio * viewPortHeight;
        auto focalLength = 1.0;

        origin = point3(0, 0, 0);
        horizontal = vec3(viewPortWidth, 0.0, 0.0);
        vertical = vec3(0.0, viewPortHeight, 0.0);
        lowerLeftCorner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focalLength);
    }

    ray getRay(double u, double v) const {
        return ray(origin, lowerLeftCorner + u*horizontal + v*vertical - origin);
    }

 private:
    point3 origin;
    point3 lowerLeftCorner;
    vec3 horizontal;
    vec3 vertical;
};

#endif
