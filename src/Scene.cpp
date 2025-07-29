#include "Scene.h"
#include "Ray.h"
#include <algorithm>

void Scene::addObject(std::unique_ptr<Hitable> object) {
    objects.push_back(std::move(object));
}

void Scene::addLight(const Light& light) {
    lights.push_back(light);
}

void Scene::setBackgroundColor(const Color& color) {
    backgroundColor = color;
}

bool Scene::hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const {
    HitRecord tempRecord;
    bool hitAnything = false;
    float closestSoFar = tMax;

    for (const auto& object : objects) {
        if (object->hit(ray, tMin, closestSoFar, tempRecord)) {
            hitAnything = true;
            closestSoFar = tempRecord.t;
            record = tempRecord;
        }
    }

    return hitAnything;
}

Color Scene::rayColor(const Ray& ray, int depth, int maxDepth) const {
    if (depth >= maxDepth) {
        return Color::BLACK;
    }

    HitRecord record;
    if (hit(ray, 0.001f, 1000.0f, record)) {
        // Handle emissive materials
        if (record.material.type == MaterialType::EMISSIVE) {
            return record.material.emission;
        }

        // Calculate direct lighting
        Color directLight = calculateLighting(record, -ray.direction);

        // Calculate indirect lighting (recursive ray tracing)
        Vector3 scattered;
        Color attenuation;
        if (record.material.scatter(-ray.direction, record.normal, record.point, scattered, attenuation)) {
            Ray scatteredRay(record.point, scattered);
            Color indirectLight = rayColor(scatteredRay, depth + 1, maxDepth);
            return directLight + attenuation * indirectLight;
        }

        return directLight;
    }

    // Background gradient
    Vector3 unitDirection = ray.direction.normalized();
    float t = 0.5f * (unitDirection.y + 1.0f);
    return (1.0f - t) * Color::WHITE + t * backgroundColor;
}

Color Scene::calculateLighting(const HitRecord& record, const Vector3& viewDirection) const {
    Color totalLight = Color::BLACK;

    for (const auto& light : lights) {
        Vector3 lightDir = (light.position - record.point).normalized();
        float distance = Vector3::distance(light.position, record.point);

        // Check for shadows
        Ray shadowRay(record.point, lightDir, 0.001f, distance - 0.001f);
        HitRecord shadowRecord;
        if (hit(shadowRay, 0.001f, distance - 0.001f, shadowRecord)) {
            continue; // In shadow
        }

        // Lambertian shading
        float lambertian = std::max(0.0f, record.normal.dot(lightDir));
        
        // Attenuation based on distance
        float attenuation = 1.0f / (1.0f + 0.09f * distance + 0.032f * distance * distance);
        
        Color diffuse = record.material.albedo * light.color * lambertian * light.intensity * attenuation;
        totalLight += diffuse;

        // Specular reflection for metal materials
        if (record.material.type == MaterialType::METAL) {
            Vector3 reflectDir = Vector3::reflect(-lightDir, record.normal);
            float spec = pow(std::max(0.0f, viewDirection.dot(reflectDir)), 32.0f);
            Color specular = light.color * spec * (1.0f - record.material.roughness) * light.intensity * attenuation;
            totalLight += specular;
        }
    }

    // Ambient lighting
    Color ambient = record.material.albedo * 0.1f;
    totalLight += ambient;

    return totalLight;
}
