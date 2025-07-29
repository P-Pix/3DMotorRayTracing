#ifndef SPHERE_H
#define SPHERE_H

#include "Hitable.h"
#include "Vector3.h"
#include "Material.h"

class Sphere : public Hitable {
public:
    Vector3 center;
    float radius;
    Material material;

    // Constructors
    Sphere() : center(Vector3()), radius(1.0f), material(Material()) {}
    Sphere(const Vector3& center, float radius, const Material& material)
        : center(center), radius(radius), material(material) {}

    // Hitable interface
    bool hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const override;

private:
    Vector3 getNormal(const Vector3& point) const;
};

#endif // SPHERE_H
