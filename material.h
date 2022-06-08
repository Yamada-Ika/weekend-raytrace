#ifndef MATERIAL_H
# define MATERIAL_H

struct hitRecord;

class material {
 public:
    virtual bool scatter(
        const ray& rIn, const hitRecord& rec, color& attenuation, ray &scattered
        ) const = 0;
};

class lambertian : public material {
 public:
    lambertian(const color& a) : albedo(a) {}

    virtual bool scatter(
        const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered
    ) const override {
        auto scatterDir = rec.normal + randomUnitVector();

        if (scatterDir.nearZero()) scatterDir = rec.normal;

        scattered = ray(rec.pos, scatterDir);
        attenuation = albedo;
        return true;
    }

 private:
    color albedo;
};

class metal : public material {
 private:
    color albedo;
    double fuzz;

 public:
    metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    virtual bool scatter(
        const ray& rayIn, const hitRecord& rec, color& attenuation, ray& scattered) const override {
        vec3 reflected = reflect(unitVector(rayIn.direction()), rec.normal);
        scattered = ray(rec.pos, reflected + fuzz*randomInUnitSphere());
        attenuation = albedo;
        return dot(scattered.direction(), rec.normal) > 0;
    }
};

#endif
