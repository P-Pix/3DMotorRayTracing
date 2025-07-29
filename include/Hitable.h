#ifndef HITABLE_H
#define HITABLE_H

#include "Ray.h"
#include "Material.h"
#include "Vector3.h"

struct HitRecord {
    Vector3 point;
    Vector3 normal;
    Material material;
    float t;
    bool frontFace;
    
    void setFaceNormal(const Ray& ray, const Vector3& outwardNormal) {
        frontFace = ray.direction.dot(outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -1.0f * outwardNormal;
    }
};

class Hitable {
public:
    virtual ~Hitable() = default;
    virtual bool hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const = 0;
};

#endif // HITABLE_H
