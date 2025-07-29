#ifndef SCENE_H
#define SCENE_H

#include "Hitable.h"
#include "Vector3.h"
#include "Color.h"
#include <vector>
#include <memory>

class Light {
public:
    Vector3 position;
    Color color;
    float intensity;

    Light(const Vector3& position, const Color& color, float intensity = 1.0f)
        : position(position), color(color), intensity(intensity) {}
};

class Scene {
public:
    std::vector<std::unique_ptr<Hitable>> objects;
    std::vector<Light> lights;
    Color backgroundColor;

    Scene() : backgroundColor(Color(0.7f, 0.8f, 1.0f)) {} // Sky blue

    // Object management
    void addObject(std::unique_ptr<Hitable> object);
    void addLight(const Light& light);
    void setBackgroundColor(const Color& color);

    // Ray tracing
    bool hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const;
    Color rayColor(const Ray& ray, int depth = 0, int maxDepth = 10) const;

private:
    Color calculateLighting(const HitRecord& record, const Vector3& viewDirection) const;
};

#endif // SCENE_H
