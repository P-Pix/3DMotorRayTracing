#include "Camera.h"
#include <cmath>
#include <random>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Camera::Camera() 
    : position(Vector3(0, 0, 0)), target(Vector3(0, 0, -1)), up(Vector3(0, 1, 0)),
      fov(45.0f), aspectRatio(16.0f/9.0f), aperture(0.0f), focusDistance(1.0f) {
    updateVectors();
}

Camera::Camera(const Vector3& position, const Vector3& target, const Vector3& up, 
               float fov, float aspectRatio, float aperture, float focusDistance)
    : position(position), target(target), up(up), fov(fov), aspectRatio(aspectRatio),
      aperture(aperture), focusDistance(focusDistance) {
    updateVectors();
}

Ray Camera::getRay(float s, float t) const {
    Vector3 rd = lensRadius * randomInUnitDisk();
    Vector3 offset = u * rd.x + v * rd.y;
    
    Vector3 rayOrigin = position + offset;
    Vector3 rayDirection = lowerLeftCorner + s * horizontal + t * vertical - position - offset;
    
    return Ray(rayOrigin, rayDirection.normalized());
}

void Camera::lookAt(const Vector3& position, const Vector3& target, const Vector3& up) {
    this->position = position;
    this->target = target;
    this->up = up;
    updateVectors();
}

void Camera::setFOV(float fov) {
    this->fov = fov;
    updateVectors();
}

void Camera::setAspectRatio(float aspectRatio) {
    this->aspectRatio = aspectRatio;
    updateVectors();
}

void Camera::updateVectors() {
    lensRadius = aperture / 2.0f;
    
    float theta = fov * M_PI / 180.0f;
    float halfHeight = tan(theta / 2.0f);
    float halfWidth = aspectRatio * halfHeight;
    
    w = (position - target).normalized();
    u = up.cross(w).normalized();
    v = w.cross(u);
    
    lowerLeftCorner = position - halfWidth * focusDistance * u - halfHeight * focusDistance * v - focusDistance * w;
    horizontal = 2.0f * halfWidth * focusDistance * u;
    vertical = 2.0f * halfHeight * focusDistance * v;
}

Vector3 Camera::randomInUnitDisk() const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dis(-1.0f, 1.0f);
    
    Vector3 p;
    do {
        p = Vector3(dis(gen), dis(gen), 0);
    } while (p.lengthSquared() >= 1.0f);
    
    return p;
}
