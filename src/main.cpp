#include "OpenGLRenderer.h"
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
#include <thread>

class InteractiveRayTracingEngine {
private:
    OpenGLRenderer glRenderer;
    Renderer rayRenderer;
    Scene scene;
    Camera camera;
    GLuint frameTexture;
    
    bool isRealTimeMode;
    bool needsRerender;
    std::vector<unsigned char> frameData;
    
    // Camera control
    Vector3 cameraPosition;
    Vector3 cameraTarget;
    float cameraYaw, cameraPitch;
    float cameraSpeed;
    
    // Performance tracking
    std::chrono::high_resolution_clock::time_point lastFrameTime;
    int frameCount;
    float fps;
    
public:
    InteractiveRayTracingEngine() 
        : glRenderer(1200, 800, "Interactive 3D Ray Tracing Engine"), 
          rayRenderer(600, 400, 25, 8, 4), // Lower resolution for real-time
          frameTexture(0), isRealTimeMode(false), needsRerender(true),
          cameraYaw(-90.0f), cameraPitch(0.0f), cameraSpeed(0.05f),
          frameCount(0), fps(0.0f) {
        
        setupScene();
        setupCamera();
        lastFrameTime = std::chrono::high_resolution_clock::now();
    }
    
    void setupScene() {
        // Create materials
        Material redLambertian = Material::lambertian(Color::RED);
        Material greenLambertian = Material::lambertian(Color::GREEN);
        Material blueMetal = Material::metal(Color::BLUE, 0.1f);
        Material goldMetal = Material::metal(Color(1.0f, 0.8f, 0.2f), 0.0f);
        Material glass = Material::dielectric(1.5f);
        Material ground = Material::lambertian(Color(0.5f, 0.5f, 0.5f));
        Material light = Material::emissive(Color::WHITE * 3.0f);
        
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
        
        std::cout << "✅ Scene setup complete" << std::endl;
    }
    
    void setupCamera() {
        cameraPosition = Vector3(3, 2, 2);
        cameraTarget = Vector3(0, 0, -1);
        updateCamera();
        
        std::cout << "✅ Camera setup complete" << std::endl;
    }
    
    void updateCamera() {
        camera.lookAt(cameraPosition, cameraTarget, Vector3(0, 1, 0));
        camera.setFOV(45.0f);
        camera.setAspectRatio(static_cast<float>(rayRenderer.width) / rayRenderer.height);
        needsRerender = true;
    }
    
    bool initialize() {
        if (!glRenderer.initialize()) {
            std::cerr << "❌ Failed to initialize OpenGL renderer" << std::endl;
            return false;
        }
        
        // Create initial frame texture
        frameData.resize(rayRenderer.width * rayRenderer.height * 3, 0);
        frameTexture = glRenderer.createTexture(rayRenderer.width, rayRenderer.height, frameData.data());
        
        std::cout << "✅ Interactive Ray Tracing Engine initialized!" << std::endl;
        printControls();
        
        return true;
    }
    
    void printControls() {
        std::cout << "\n🎮 Controls:" << std::endl;
        std::cout << "  ESC     - Exit application" << std::endl;
        std::cout << "  R       - Toggle real-time rendering" << std::endl;
        std::cout << "  SPACE   - Render single high-quality frame" << std::endl;
        std::cout << "  S       - Save current frame to image" << std::endl;
        std::cout << "  H       - Increase ray tracing quality" << std::endl;
        std::cout << "  L       - Decrease ray tracing quality" << std::endl;
        std::cout << "  WASD    - Move camera" << std::endl;
        std::cout << "  QE      - Move camera up/down" << std::endl;
        std::cout << "  Mouse   - Look around (click and drag)" << std::endl;
        std::cout << "  1-3     - Switch quality presets" << std::endl;
        std::cout << std::endl;
    }
    
    void run() {
        if (!initialize()) {
            return;
        }
        
        // Render initial frame
        renderFrame();
        
        while (!glRenderer.shouldClose()) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            
            glRenderer.pollEvents();
            handleInput();
            
            // Render frame if needed
            if (isRealTimeMode || needsRerender) {
                renderFrame();
                needsRerender = false;
            }
            
            // Display frame
            glRenderer.clear();
            glRenderer.renderTexture(frameTexture);
            glRenderer.swapBuffers();
            
            // Update FPS
            updateFPS(currentTime);
        }
        
        std::cout << "👋 Thank you for using the Interactive Ray Tracing Engine!" << std::endl;
    }
    
private:
    void renderFrame() {
        auto start = std::chrono::high_resolution_clock::now();
        
        frameData = rayRenderer.renderToBytes(scene, camera);
        glRenderer.updateTexture(frameTexture, rayRenderer.width, rayRenderer.height, frameData.data());
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        if (!isRealTimeMode) {
            std::cout << "🎨 Frame rendered in " << duration.count() << "ms" << std::endl;
        }
    }
    
    void handleInput() {
        // Toggle real-time rendering
        static bool rKeyPressed = false;
        if (glRenderer.isKeyPressed(GLFW_KEY_R) && !rKeyPressed) {
            isRealTimeMode = !isRealTimeMode;
            std::cout << "⚡ Real-time rendering: " << (isRealTimeMode ? "ON" : "OFF") << std::endl;
            if (isRealTimeMode) {
                // Switch to lower quality for real-time
                rayRenderer.setSamples(10);
                rayRenderer.setMaxDepth(5);
                std::cout << "   Quality: Low (for real-time)" << std::endl;
            }
            rKeyPressed = true;
        } else if (!glRenderer.isKeyPressed(GLFW_KEY_R)) {
            rKeyPressed = false;
        }
        
        // Render single high-quality frame
        static bool spaceKeyPressed = false;
        if (glRenderer.isKeyPressed(GLFW_KEY_SPACE) && !spaceKeyPressed) {
            if (!isRealTimeMode) {
                std::cout << "🎯 Rendering high-quality frame..." << std::endl;
                int oldSamples = rayRenderer.samples;
                int oldDepth = rayRenderer.maxDepth;
                rayRenderer.setSamples(100);
                rayRenderer.setMaxDepth(15);
                renderFrame();
                rayRenderer.setSamples(oldSamples);
                rayRenderer.setMaxDepth(oldDepth);
            }
            spaceKeyPressed = true;
        } else if (!glRenderer.isKeyPressed(GLFW_KEY_SPACE)) {
            spaceKeyPressed = false;
        }
        
        // Save frame
        static bool sKeyPressed = false;
        if (glRenderer.isKeyPressed(GLFW_KEY_S) && !sKeyPressed) {
            saveCurrentFrame();
            sKeyPressed = true;
        } else if (!glRenderer.isKeyPressed(GLFW_KEY_S)) {
            sKeyPressed = false;
        }
        
        // Quality presets
        handleQualityKeys();
        
        // Camera movement
        handleCameraMovement();
    }
    
    void handleQualityKeys() {
        static bool key1Pressed = false, key2Pressed = false, key3Pressed = false;
        static bool hKeyPressed = false, lKeyPressed = false;
        
        // Preset 1: Low quality (real-time)
        if (glRenderer.isKeyPressed(GLFW_KEY_1) && !key1Pressed) {
            rayRenderer.setResolution(400, 300);
            rayRenderer.setSamples(5);
            rayRenderer.setMaxDepth(3);
            std::cout << "📺 Quality: Low (400x300, 5 samples)" << std::endl;
            needsRerender = true;
            key1Pressed = true;
        } else if (!glRenderer.isKeyPressed(GLFW_KEY_1)) {
            key1Pressed = false;
        }
        
        // Preset 2: Medium quality
        if (glRenderer.isKeyPressed(GLFW_KEY_2) && !key2Pressed) {
            rayRenderer.setResolution(600, 400);
            rayRenderer.setSamples(25);
            rayRenderer.setMaxDepth(8);
            std::cout << "📺 Quality: Medium (600x400, 25 samples)" << std::endl;
            needsRerender = true;
            key2Pressed = true;
        } else if (!glRenderer.isKeyPressed(GLFW_KEY_2)) {
            key2Pressed = false;
        }
        
        // Preset 3: High quality
        if (glRenderer.isKeyPressed(GLFW_KEY_3) && !key3Pressed) {
            rayRenderer.setResolution(800, 600);
            rayRenderer.setSamples(50);
            rayRenderer.setMaxDepth(12);
            std::cout << "📺 Quality: High (800x600, 50 samples)" << std::endl;
            needsRerender = true;
            key3Pressed = true;
        } else if (!glRenderer.isKeyPressed(GLFW_KEY_3)) {
            key3Pressed = false;
        }
        
        // Increase quality
        if (glRenderer.isKeyPressed(GLFW_KEY_H) && !hKeyPressed) {
            int newSamples = std::min(rayRenderer.samples + 10, 200);
            rayRenderer.setSamples(newSamples);
            std::cout << "⬆️ Quality increased: " << newSamples << " samples" << std::endl;
            needsRerender = true;
            hKeyPressed = true;
        } else if (!glRenderer.isKeyPressed(GLFW_KEY_H)) {
            hKeyPressed = false;
        }
        
        // Decrease quality
        if (glRenderer.isKeyPressed(GLFW_KEY_L) && !lKeyPressed) {
            int newSamples = std::max(rayRenderer.samples - 10, 1);
            rayRenderer.setSamples(newSamples);
            std::cout << "⬇️ Quality decreased: " << newSamples << " samples" << std::endl;
            needsRerender = true;
            lKeyPressed = true;
        } else if (!glRenderer.isKeyPressed(GLFW_KEY_L)) {
            lKeyPressed = false;
        }
    }
    
    void handleCameraMovement() {
        bool moved = false;
        Vector3 forward = (cameraTarget - cameraPosition).normalized();
        Vector3 right = forward.cross(Vector3(0, 1, 0)).normalized();
        Vector3 up = Vector3(0, 1, 0);
        
        // WASD movement
        if (glRenderer.isKeyPressed(GLFW_KEY_W)) {
            cameraPosition += forward * cameraSpeed;
            cameraTarget += forward * cameraSpeed;
            moved = true;
        }
        if (glRenderer.isKeyPressed(GLFW_KEY_S)) {
            cameraPosition -= forward * cameraSpeed;
            cameraTarget -= forward * cameraSpeed;
            moved = true;
        }
        if (glRenderer.isKeyPressed(GLFW_KEY_A)) {
            cameraPosition -= right * cameraSpeed;
            cameraTarget -= right * cameraSpeed;
            moved = true;
        }
        if (glRenderer.isKeyPressed(GLFW_KEY_D)) {
            cameraPosition += right * cameraSpeed;
            cameraTarget += right * cameraSpeed;
            moved = true;
        }
        if (glRenderer.isKeyPressed(GLFW_KEY_Q)) {
            cameraPosition += up * cameraSpeed;
            cameraTarget += up * cameraSpeed;
            moved = true;
        }
        if (glRenderer.isKeyPressed(GLFW_KEY_E)) {
            cameraPosition -= up * cameraSpeed;
            cameraTarget -= up * cameraSpeed;
            moved = true;
        }
        
        if (moved) {
            updateCamera();
        }
    }
    
    void saveCurrentFrame() {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        auto tm = *std::localtime(&time_t);
        
        char filename[100];
        std::strftime(filename, sizeof(filename), "raytraced_%Y%m%d_%H%M%S.ppm", &tm);
        
        std::vector<Color> pixels = rayRenderer.render(scene, camera);
        if (ImageWriter::savePPM(filename, rayRenderer.width, rayRenderer.height, pixels)) {
            std::cout << "💾 Frame saved to " << filename << std::endl;
        } else {
            std::cout << "❌ Failed to save frame" << std::endl;
        }
    }
    
    void updateFPS(const std::chrono::high_resolution_clock::time_point& currentTime) {
        frameCount++;
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastFrameTime);
        
        if (duration.count() >= 1000) { // Update every second
            fps = static_cast<float>(frameCount) / (duration.count() / 1000.0f);
            
            if (isRealTimeMode) {
                std::cout << "🎥 FPS: " << static_cast<int>(fps) 
                         << " | Quality: " << rayRenderer.samples << " samples"
                         << " | Resolution: " << rayRenderer.width << "x" << rayRenderer.height << std::endl;
            }
            
            frameCount = 0;
            lastFrameTime = currentTime;
        }
    }
};

int main() {
    try {
        InteractiveRayTracingEngine engine;
        engine.run();
    } catch (const std::exception& e) {
        std::cerr << "❌ Error: " << e.what() << std::endl;
        return -1;
    }
    
    return 0;
}
