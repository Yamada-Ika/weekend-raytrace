#ifndef COLOR_H
# define COLOR_H

#include "vec3.h"
#include <iostream>

void WriteColor(std::ostream &out, color pixel, int samplesPerPixel) {
    auto r = pixel.x();
    auto g = pixel.y();
    auto b = pixel.z();

    auto scale = 1.0 / samplesPerPixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << std::endl;
}

#endif
