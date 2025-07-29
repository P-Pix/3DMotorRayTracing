#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"
#include "Vector3.h"

enum class MaterialType {
    LAMBERTIAN,
    METAL,
    DIELECTRIC,
    EMISSIVE
};

class Material {
public:
    MaterialType type;
    Color albedo;
    Color emission;
    float roughness;
    float refractiveIndex;

    // Constructors
    Material() : type(MaterialType::LAMBERTIAN), albedo(Color::WHITE), emission(Color::BLACK), roughness(0.0f), refractiveIndex(1.0f) {}
    
    // Lambertian material
    Material(const Color& albedo) 
        : type(MaterialType::LAMBERTIAN), albedo(albedo), emission(Color::BLACK), roughness(0.0f), refractiveIndex(1.0f) {}
    
    // Metal material
    Material(const Color& albedo, float roughness) 
        : type(MaterialType::METAL), albedo(albedo), emission(Color::BLACK), roughness(roughness), refractiveIndex(1.0f) {}
    
    // Dielectric material
    Material(float refractiveIndex) 
        : type(MaterialType::DIELECTRIC), albedo(Color::WHITE), emission(Color::BLACK), roughness(0.0f), refractiveIndex(refractiveIndex) {}
    
    // Emissive material
    Material(const Color& emission, bool /*isEmissive*/) 
        : type(MaterialType::EMISSIVE), albedo(Color::BLACK), emission(emission), roughness(0.0f), refractiveIndex(1.0f) {}

    // Static factory methods
    static Material lambertian(const Color& albedo);
    static Material metal(const Color& albedo, float roughness = 0.0f);
    static Material dielectric(float refractiveIndex);
    static Material emissive(const Color& emission);

    // Scatter calculation
    bool scatter(const Vector3& incident, const Vector3& normal, const Vector3& hitPoint, 
                Vector3& scattered, Color& attenuation) const;

private:
    Vector3 randomInUnitSphere() const;
    Vector3 randomUnitVector() const;
    Vector3 randomInHemisphere(const Vector3& normal) const;
    float reflectance(float cosine, float refIdx) const;
};

#endif // MATERIAL_H
