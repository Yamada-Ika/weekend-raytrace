#include <iostream>

#include "rt_weekend.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

color RayColor(const ray& r, const hittableList& world, int depth) {
    hitRecord rec;

    if (depth <= 0) return color(0, 0, 0);

    if (world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.matPtr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * RayColor(scattered, world, depth-1);
        }
        return color(0, 0, 0);
    }

    // Make Gradation Background Color
    vec3 unitDir = unitVector(r.direction());
    auto t = 0.5*(unitDir.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main(void) {

    // Image

    const auto aspectRatio = 16.0 / 9.0;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixels = 100;
    const int maxDepth = 50;

    // World

    hittableList world;

    auto materialGround = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto materialCenter = std::make_shared<lambertian>(color(0.7, 0.3, 0.3));
    auto materialLeft = std::make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
    auto materialRight = std::make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

    world.add(std::make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, materialGround));
    world.add(std::make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, materialCenter));
    world.add(std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, materialLeft));
    world.add(std::make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, materialRight));

    // Camera

    camera cam;

    // Render

    std::cout << "P3" << std::endl;
    std::cout << imageWidth << " " << imageHeight << std::endl;
    std::cout << "255" << std::endl;

    for (int j = imageHeight - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << " " << std::flush;
        for (int i = 0; i < imageWidth; ++i) {
            color pixel(0, 0, 0);
            for (int s = 0; s < samplesPerPixels; ++s) {
                auto u = static_cast<double>(i + RandomDouble())/(imageWidth-1);
                auto v = static_cast<double>(j + RandomDouble())/(imageHeight-1);
                ray r = cam.getRay(u, v);
                pixel += RayColor(r, world, maxDepth);
            }
            WriteColor(std::cout, pixel, samplesPerPixels);
        }
    }

    std::cerr << std::endl << "Done" << std::endl;
}