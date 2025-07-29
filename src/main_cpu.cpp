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

class RayTracingEngine {
private:
    Renderer rayRenderer;
    Scene scene;
    Camera camera;
    
public:
    RayTracingEngine() : rayRenderer(800, 600, 100, 10, 4) { // Plus d'échantillons pour meilleure qualité
        setupScene();
        setupCamera();
    }
    
    void setupScene() {
        // Create materials
        Material redLambertian = Material::lambertian(Color::RED);
        Material greenLambertian = Material::lambertian(Color::GREEN);
        Material blueMetal = Material::metal(Color::BLUE, 0.1f);
        Material goldMetal = Material::metal(Color(1.0f, 0.8f, 0.2f), 0.0f);
        Material glass = Material::dielectric(1.5f);
        Material ground = Material::lambertian(Color(0.5f, 0.5f, 0.5f));
        Material light = Material::emissive(Color::WHITE * 5.0f);
        
        // Add objects to scene
        scene.addObject(std::make_unique<Sphere>(Vector3(0, 0, -1), 0.5f, redLambertian));
        scene.addObject(std::make_unique<Sphere>(Vector3(-1, 0, -1), 0.5f, glass));
        scene.addObject(std::make_unique<Sphere>(Vector3(-1, 0, -1), -0.45f, glass)); // Hollow glass sphere
        scene.addObject(std::make_unique<Sphere>(Vector3(1, 0, -1), 0.5f, blueMetal));
        scene.addObject(std::make_unique<Sphere>(Vector3(0, 1, -1), 0.3f, goldMetal));
        scene.addObject(std::make_unique<Sphere>(Vector3(-0.5f, -0.2f, -0.5f), 0.3f, greenLambertian));
        
        // Ground plane
        scene.addObject(std::make_unique<Plane>(Vector3(0, -0.5f, 0), Vector3(0, 1, 0), ground));
        
        // Light source
        scene.addObject(std::make_unique<Sphere>(Vector3(2, 2, 0), 0.5f, light));
        
        // Add lights
        scene.addLight(Light(Vector3(2, 2, 0), Color::WHITE, 1.0f));
        scene.addLight(Light(Vector3(-2, 2, -2), Color(0.8f, 0.8f, 1.0f), 0.5f));
        
        // Set background
        scene.setBackgroundColor(Color(0.5f, 0.7f, 1.0f));
    }
    
    void setupCamera() {
        Vector3 position(3, 2, 2);
        Vector3 target(0, 0, -1);
        Vector3 up(0, 1, 0);
        float fov = 20.0f;
        float aspectRatio = 800.0f / 600.0f;
        
        camera.lookAt(position, target, up);
        camera.setFOV(fov);
        camera.setAspectRatio(aspectRatio);
    }
    
    void render() {
        std::cout << "=== 3D Ray Tracing Engine ===" << std::endl;
        std::cout << "Rendering scene..." << std::endl;
        std::cout << "Resolution: " << rayRenderer.width << "x" << rayRenderer.height << std::endl;
        std::cout << "Samples per pixel: " << rayRenderer.samples << std::endl;
        std::cout << "Max ray depth: " << rayRenderer.maxDepth << std::endl;
        std::cout << "Threads: " << rayRenderer.numThreads << std::endl;
        std::cout << std::endl;
        
        auto start = std::chrono::high_resolution_clock::now();
        
        // Render the scene
        std::vector<Color> pixels = rayRenderer.render(scene, camera);
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        std::cout << std::endl;
        std::cout << "Rendering completed in " << duration.count() << "ms" << std::endl;
        
        // Save the image
        std::string filename = "raytraced_scene.ppm";
        if (ImageWriter::savePPM(filename, rayRenderer.width, rayRenderer.height, pixels)) {
            std::cout << "You can view the image with any PPM viewer or convert it with ImageMagick:" << std::endl;
            std::cout << "  convert " << filename << " raytraced_scene.png" << std::endl;
        }
        
        // Performance stats
        long long totalRays = static_cast<long long>(rayRenderer.width) * rayRenderer.height * rayRenderer.samples;
        double raysPerSecond = static_cast<double>(totalRays) / (duration.count() / 1000.0);
        
        std::cout << std::endl;
        std::cout << "Performance Statistics:" << std::endl;
        std::cout << "  Total rays cast: " << totalRays << std::endl;
        std::cout << "  Rays per second: " << static_cast<long long>(raysPerSecond) << std::endl;
    }
    
    void renderMultipleAngles() {
        std::cout << "Rendering scene from multiple angles..." << std::endl;
        
        std::vector<Vector3> positions = {
            Vector3(3, 2, 2),    // Vue d'angle
            Vector3(0, 3, 3),    // Vue du dessus
            Vector3(-3, 1, 0),   // Vue latérale
            Vector3(0, 0, 3)     // Vue frontale
        };
        
        for (size_t i = 0; i < positions.size(); ++i) {
            std::cout << "Rendering view " << (i + 1) << "/" << positions.size() << "..." << std::endl;
            
            camera.lookAt(positions[i], Vector3(0, 0, -1), Vector3(0, 1, 0));
            
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<Color> pixels = rayRenderer.render(scene, camera);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            
            std::string filename = "raytraced_view_" + std::to_string(i + 1) + ".ppm";
            ImageWriter::savePPM(filename, rayRenderer.width, rayRenderer.height, pixels);
            
            std::cout << "  View " << (i + 1) << " completed in " << duration.count() << "ms" << std::endl;
        }
    }
};

int main(int argc, char* argv[]) {
    try {
        RayTracingEngine engine;
        
        if (argc > 1 && std::string(argv[1]) == "--multiple") {
            engine.renderMultipleAngles();
        } else {
            engine.render();
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}
