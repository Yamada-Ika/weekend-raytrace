#ifndef RTWEEKEND_H
# define RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double DegreesToRadians(double deg) { return deg * pi / 180.0; }
inline double RandomDouble(void) { return rand() / (RAND_MAX / 1.0); }
inline double RandomDouble(double min, double max) { return min + (max-min)*RandomDouble(); }
inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

// Uncomment you want to use othrer randome number generator
// #include <random>
// inline double RandomeDouble(void) {
//     static std::uniform_real_distribution<double> distribution(0.0, 1.0);
//     static std::mt19937 generator;
//     return distribution(generator);
// }

// Common Headers

#include "ray.h"
#include "vec3.h"

#endif
