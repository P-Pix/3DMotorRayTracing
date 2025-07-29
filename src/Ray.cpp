#include "Ray.h"

Vector3 Ray::pointAt(float t) const {
    return origin + t * direction;
}

Vector3 Ray::pointAt(float t, const Vector3& origin, const Vector3& direction) const {
    return origin + t * direction;
}
