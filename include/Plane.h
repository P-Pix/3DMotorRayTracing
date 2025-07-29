#ifndef PLANE_H
#define PLANE_H

#include "Hitable.h"
#include "Vector3.h"
#include "Material.h"

class Plane : public Hitable {
public:
    Vector3 point;
    Vector3 normal;
    Material material;

    // Constructors
    Plane() : point(Vector3()), normal(Vector3(0, 1, 0)), material(Material()) {}
    Plane(const Vector3& point, const Vector3& normal, const Material& material)
        : point(point), normal(normal.normalized()), material(material) {}

    // Hitable interface
    bool hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const override;
};

#endif // PLANE_H
