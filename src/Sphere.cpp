#include "Sphere.h"
#include <cmath>

bool Sphere::hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const {
    Vector3 oc = ray.origin - center;
    float a = ray.direction.lengthSquared();
    float halfB = oc.dot(ray.direction);
    float c = oc.lengthSquared() - radius * radius;
    
    float discriminant = halfB * halfB - a * c;
    if (discriminant < 0) {
        return false;
    }
    
    float sqrtd = sqrt(discriminant);
    
    // Find the nearest root that lies in the acceptable range
    float root = (-halfB - sqrtd) / a;
    if (root < tMin || tMax < root) {
        root = (-halfB + sqrtd) / a;
        if (root < tMin || tMax < root) {
            return false;
        }
    }
    
    record.t = root;
    record.point = ray.pointAt(record.t);
    Vector3 outwardNormal = getNormal(record.point);
    record.setFaceNormal(ray, outwardNormal);
    record.material = material;
    
    return true;
}

Vector3 Sphere::getNormal(const Vector3& point) const {
    return (point - center) / radius;
}
