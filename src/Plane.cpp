#include "Plane.h"
#include <cmath>

bool Plane::hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const {
    float denom = normal.dot(ray.direction);
    
    // Check if ray is parallel to plane
    if (abs(denom) < 1e-6f) {
        return false;
    }
    
    float t = (point - ray.origin).dot(normal) / denom;
    
    if (t < tMin || t > tMax) {
        return false;
    }
    
    record.t = t;
    record.point = ray.pointAt(t);
    record.setFaceNormal(ray, normal);
    record.material = material;
    
    return true;
}
