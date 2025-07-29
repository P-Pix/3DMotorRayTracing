#include "Material.h"
#include <random>
#include <cmath>

// Static factory methods
Material Material::lambertian(const Color& albedo) {
    return Material(albedo);
}

Material Material::metal(const Color& albedo, float roughness) {
    return Material(albedo, roughness);
}

Material Material::dielectric(float refractiveIndex) {
    return Material(refractiveIndex);
}

Material Material::emissive(const Color& emission) {
    return Material(emission, true);
}

// Scatter calculation
bool Material::scatter(const Vector3& incident, const Vector3& normal, const Vector3& /*hitPoint*/, 
                      Vector3& scattered, Color& attenuation) const {
    switch (type) {
        case MaterialType::LAMBERTIAN: {
            Vector3 target = normal + randomUnitVector();
            if (target.lengthSquared() < 1e-8f) {
                target = normal;
            }
            scattered = target.normalized();
            attenuation = albedo;
            return true;
        }
        
        case MaterialType::METAL: {
            Vector3 reflected = Vector3::reflect(incident.normalized(), normal);
            scattered = (reflected + roughness * randomInUnitSphere()).normalized();
            attenuation = albedo;
            return scattered.dot(normal) > 0;
        }
        
        case MaterialType::DIELECTRIC: {
            attenuation = Color::WHITE;
            float refractionRatio = normal.dot(incident) < 0 ? (1.0f / refractiveIndex) : refractiveIndex;
            
            Vector3 unitDirection = incident.normalized();
            float cosTheta = std::min(-unitDirection.dot(normal), 1.0f);
            float sinTheta = sqrt(1.0f - cosTheta * cosTheta);
            
            bool cannotRefract = refractionRatio * sinTheta > 1.0f;
            
            if (cannotRefract || reflectance(cosTheta, refractionRatio) > static_cast<float>(rand()) / RAND_MAX) {
                scattered = Vector3::reflect(unitDirection, normal);
            } else {
                scattered = Vector3::refract(unitDirection, normal, refractionRatio);
            }
            
            return true;
        }
        
        case MaterialType::EMISSIVE: {
            // Emissive materials don't scatter light
            return false;
        }
    }
    
    return false;
}

// Helper methods
Vector3 Material::randomInUnitSphere() const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dis(-1.0f, 1.0f);
    
    Vector3 p;
    do {
        p = Vector3(dis(gen), dis(gen), dis(gen));
    } while (p.lengthSquared() >= 1.0f);
    
    return p;
}

Vector3 Material::randomUnitVector() const {
    return randomInUnitSphere().normalized();
}

Vector3 Material::randomInHemisphere(const Vector3& normal) const {
    Vector3 inUnitSphere = randomInUnitSphere();
    if (inUnitSphere.dot(normal) > 0.0f) {
        return inUnitSphere;
    } else {
        return -1.0f * inUnitSphere;
    }
}

float Material::reflectance(float cosine, float refIdx) const {
    // Use Schlick's approximation for reflectance
    float r0 = (1 - refIdx) / (1 + refIdx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}
