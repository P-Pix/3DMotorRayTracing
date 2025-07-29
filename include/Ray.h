#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

class Ray {
public:
    Vector3 origin;
    Vector3 direction;
    float tMin, tMax;

    // Constructors
    Ray() : origin(Vector3()), direction(Vector3(0, 0, 1)), tMin(0.001f), tMax(1000.0f) {}
    Ray(const Vector3& origin, const Vector3& direction, float tMin = 0.001f, float tMax = 1000.0f)
        : origin(origin), direction(direction.normalized()), tMin(tMin), tMax(tMax) {}

    // Methods
    Vector3 pointAt(float t) const;
    Vector3 pointAt(float t, const Vector3& origin, const Vector3& direction) const;
};

#endif // RAY_H
