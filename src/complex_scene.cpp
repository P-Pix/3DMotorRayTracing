#include "Renderer.h"
#include "Scene.h"
#include "Camera.h"
#include "Sphere.h"
#include "Plane.h"
#include "Material.h"
#include "Vector3.h"
#include "Color.h"
#include "ImageWriter.h"

#include <iostream>
#include <chrono>
#include <memory>
#include <random>

class ComplexSceneEngine {
private:
    Renderer rayRenderer;
    Scene scene;
    Camera camera;
    
public:
    ComplexSceneEngine() : rayRenderer(1200, 800, 50, 15, 8) { // Résolution plus haute
        setupComplexScene();
        setupCamera();
    }
    
    void setupComplexScene() {
        std::cout << "Setting up complex scene..." << std::endl;
        
        // Materials
        Material ground = Material::lambertian(Color(0.5f, 0.5f, 0.5f));
        Material centerSphere = Material::lambertian(Color(0.1f, 0.2f, 0.5f));
        Material leftSphere = Material::dielectric(1.5f);
        Material leftSphereInner = Material::dielectric(1.5f);
        Material rightSphere = Material::metal(Color(0.8f, 0.6f, 0.2f), 0.0f);
        
        // Different materials for random spheres
        Material redMetal = Material::metal(Color::RED, 0.2f);
        Material blueLambertian = Material::lambertian(Color::BLUE);
        Material greenGlass = Material::dielectric(1.8f);
        Material yellowEmissive = Material::emissive(Color::YELLOW * 2.0f);
        Material cyanMetal = Material::metal(Color::CYAN, 0.1f);
        Material magentaLambertian = Material::lambertian(Color::MAGENTA);
        
        // Ground
        scene.addObject(std::make_unique<Plane>(Vector3(0, -0.5f, 0), Vector3(0, 1, 0), ground));
        
        // Main spheres
        scene.addObject(std::make_unique<Sphere>(Vector3(0, 0, -1), 0.5f, centerSphere));
        scene.addObject(std::make_unique<Sphere>(Vector3(-1, 0, -1), 0.5f, leftSphere));
        scene.addObject(std::make_unique<Sphere>(Vector3(-1, 0, -1), -0.45f, leftSphereInner)); // Hollow
        scene.addObject(std::make_unique<Sphere>(Vector3(1, 0, -1), 0.5f, rightSphere));
        
        // Create a grid of smaller spheres
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(-0.4f, 0.4f);
        std::uniform_int_distribution<int> matChoice(0, 5);
        
        for (int a = -3; a < 3; a++) {
            for (int b = -3; b < 3; b++) {
                float x = a + 0.9f * dis(gen);
                float z = b + 0.9f * dis(gen);
                Vector3 center(x, -0.3f, z - 3);
                
                if ((center - Vector3(4, 0.2f, 0)).length() > 0.9f) {
                    Material sphereMat;
                    int matType = matChoice(gen);
                    
                    switch (matType) {
                        case 0: sphereMat = redMetal; break;
                        case 1: sphereMat = blueLambertian; break;
                        case 2: sphereMat = greenGlass; break;
                        case 3: sphereMat = yellowEmissive; break;
                        case 4: sphereMat = cyanMetal; break;
                        default: sphereMat = magentaLambertian; break;
                    }
                    
                    scene.addObject(std::make_unique<Sphere>(center, 0.15f, sphereMat));
                }
            }
        }
        
        // Large light source
        Material lightMaterial = Material::emissive(Color::WHITE * 3.0f);
        scene.addObject(std::make_unique<Sphere>(Vector3(4, 4, -1), 1.0f, lightMaterial));
        
        // Additional light sources
        Material orangeLight = Material::emissive(Color(1.0f, 0.5f, 0.1f) * 2.0f);
        scene.addObject(std::make_unique<Sphere>(Vector3(-3, 2, 1), 0.3f, orangeLight));
        
        // Add directional lights
        scene.addLight(Light(Vector3(4, 4, -1), Color::WHITE, 1.5f));
        scene.addLight(Light(Vector3(-3, 2, 1), Color(1.0f, 0.5f, 0.1f), 0.8f));
        scene.addLight(Light(Vector3(0, 5, 0), Color(0.8f, 0.8f, 1.0f), 0.3f));
        
        // Sky gradient background
        scene.setBackgroundColor(Color(0.5f, 0.7f, 1.0f));
        
        std::cout << "Complex scene setup complete!" << std::endl;
    }
    
    void setupCamera() {
        Vector3 lookFrom(13, 2, 3);
        Vector3 lookAt(0, 0, 0);
        Vector3 vup(0, 1, 0);
        float distToFocus = 10.0f;
        float aperture = 0.1f;
        float fov = 20.0f;
        
        camera.lookAt(lookFrom, lookAt, vup);
        camera.setFOV(fov);
        camera.setAspectRatio(1200.0f / 800.0f);
        camera.aperture = aperture;
        camera.focusDistance = distToFocus;
    }
    
    void render() {
        std::cout << "=== Complex 3D Ray Tracing Scene ===" << std::endl;
        std::cout << "High-quality rendering..." << std::endl;
        std::cout << "Resolution: " << rayRenderer.width << "x" << rayRenderer.height << std::endl;
        std::cout << "Samples per pixel: " << rayRenderer.samples << std::endl;
        std::cout << "Max ray depth: " << rayRenderer.maxDepth << std::endl;
        std::cout << "Threads: " << rayRenderer.numThreads << std::endl;
        std::cout << "This may take several minutes..." << std::endl << std::endl;
        
        auto start = std::chrono::high_resolution_clock::now();
        
        // Render the scene
        std::vector<Color> pixels = rayRenderer.render(scene, camera);
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        
        std::cout << std::endl;
        std::cout << "Rendering completed in " << duration.count() << " seconds" << std::endl;
        
        // Save the image
        std::string filename = "complex_scene.ppm";
        if (ImageWriter::savePPM(filename, rayRenderer.width, rayRenderer.height, pixels)) {
            std::cout << "High-quality complex scene saved to " << filename << std::endl;
        }
        
        // Performance stats
        long long totalRays = static_cast<long long>(rayRenderer.width) * rayRenderer.height * rayRenderer.samples;
        double raysPerSecond = static_cast<double>(totalRays) / duration.count();
        
        std::cout << std::endl;
        std::cout << "Performance Statistics:" << std::endl;
        std::cout << "  Total rays cast: " << totalRays << std::endl;
        std::cout << "  Rays per second: " << static_cast<long long>(raysPerSecond) << std::endl;
        std::cout << "  Image size: " << rayRenderer.width << "x" << rayRenderer.height << " pixels" << std::endl;
    }
};

int main() {
    try {
        ComplexSceneEngine engine;
        engine.render();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}
