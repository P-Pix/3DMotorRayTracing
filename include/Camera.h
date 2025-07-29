#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"
#include "Ray.h"

class Camera {
public:
    Vector3 position;
    Vector3 target;
    Vector3 up;
    float fov;
    float aspectRatio;
    float aperture;
    float focusDistance;

    // Constructors
    Camera();
    Camera(const Vector3& position, const Vector3& target, const Vector3& up, 
           float fov, float aspectRatio, float aperture = 0.0f, float focusDistance = 1.0f);

    // Methods
    Ray getRay(float u, float v) const;
    void lookAt(const Vector3& position, const Vector3& target, const Vector3& up);
    void setFOV(float fov);
    void setAspectRatio(float aspectRatio);

private:
    void updateVectors();
    
    Vector3 lowerLeftCorner;
    Vector3 horizontal;
    Vector3 vertical;
    Vector3 u, v, w;
    float lensRadius;
    
    Vector3 randomInUnitDisk() const;
};

#endif // CAMERA_H
