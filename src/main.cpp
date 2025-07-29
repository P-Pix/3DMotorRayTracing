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
#include <cmath>

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
    
    // Auto animation mode
    bool autoAnimationMode;
    float animationTime;
    float animationSpeed;
    float orbitRadius;
    Vector3 orbitCenter;
    float orbitHeight;
    
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
          autoAnimationMode(false), animationTime(0.0f), animationSpeed(1.0f),
          orbitRadius(4.0f), orbitCenter(0, 0, -1), orbitHeight(2.0f),
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
        Material silverMetal = Material::metal(Color(0.7f, 0.7f, 0.7f), 0.05f);
        Material glass = Material::dielectric(1.5f);
        Material ground = Material::lambertian(Color(0.5f, 0.5f, 0.5f));
        Material light = Material::emissive(Color::WHITE * 3.0f);
        Material purpleLambertian = Material::lambertian(Color(0.8f, 0.2f, 0.8f));
        Material orangeMetal = Material::metal(Color(1.0f, 0.5f, 0.0f), 0.0f);
        
        // Main spheres in the center
        scene.addObject(std::make_unique<Sphere>(Vector3(0, 0, -1), 0.5f, redLambertian));
        scene.addObject(std::make_unique<Sphere>(Vector3(-1, 0, -1), 0.5f, glass));
        scene.addObject(std::make_unique<Sphere>(Vector3(-1, 0, -1), -0.45f, glass)); // Hollow glass sphere
        scene.addObject(std::make_unique<Sphere>(Vector3(1, 0, -1), 0.5f, blueMetal));
        scene.addObject(std::make_unique<Sphere>(Vector3(0, 1, -1), 0.3f, goldMetal));
        scene.addObject(std::make_unique<Sphere>(Vector3(-0.5f, -0.2f, -0.5f), 0.3f, greenLambertian));
        
        // Additional spheres around the scene for more visual interest
        scene.addObject(std::make_unique<Sphere>(Vector3(2, 0.5f, -2), 0.4f, silverMetal));
        scene.addObject(std::make_unique<Sphere>(Vector3(-2, 0.3f, -1.5f), 0.35f, purpleLambertian));
        scene.addObject(std::make_unique<Sphere>(Vector3(1.5f, -0.1f, 0.5f), 0.3f, orangeMetal));
        scene.addObject(std::make_unique<Sphere>(Vector3(-1.2f, 0.8f, 0.2f), 0.25f, glass));
        
        // Small decorative spheres
        scene.addObject(std::make_unique<Sphere>(Vector3(0.8f, 1.5f, -0.5f), 0.15f, light));
        scene.addObject(std::make_unique<Sphere>(Vector3(-0.3f, 1.8f, -1.2f), 0.12f, goldMetal));
        
        // Ground plane
        scene.addObject(std::make_unique<Plane>(Vector3(0, -0.5f, 0), Vector3(0, 1, 0), ground));
        
        // Light sources
        scene.addObject(std::make_unique<Sphere>(Vector3(2, 2, 0), 0.5f, light));
        scene.addObject(std::make_unique<Sphere>(Vector3(-2, 1.5f, -2), 0.3f, Material::emissive(Color(0.8f, 0.8f, 1.0f) * 2.0f)));
        
        // Add lights
        scene.addLight(Light(Vector3(2, 2, 0), Color::WHITE, 1.0f));
        scene.addLight(Light(Vector3(-2, 2, -2), Color(0.8f, 0.8f, 1.0f), 0.5f));
        scene.addLight(Light(Vector3(0, 3, 1), Color(1.0f, 0.9f, 0.7f), 0.3f));
        
        // Set background
        scene.setBackgroundColor(Color(0.5f, 0.7f, 1.0f));
        
        std::cout << "✅ Enhanced scene setup complete with " << (scene.objects.size()) << " objects" << std::endl;
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
        std::cout << "  A       - 🎬 Toggle AUTO ANIMATION mode (automatic camera orbit)" << std::endl;
        std::cout << "  R       - Toggle real-time rendering" << std::endl;
        std::cout << "  SPACE   - Render single high-quality frame" << std::endl;
        std::cout << "  S       - Save current frame to image" << std::endl;
        std::cout << "  H       - Increase ray tracing quality" << std::endl;
        std::cout << "  L       - Decrease ray tracing quality" << std::endl;
        std::cout << "  WASD    - Move camera (manual mode only)" << std::endl;
        std::cout << "  QE      - Move camera up/down (manual mode only)" << std::endl;
        std::cout << "  Mouse   - Look around (click and drag)" << std::endl;
        std::cout << "  1-3     - Switch quality presets" << std::endl;
        std::cout << "  +/-     - Increase/decrease animation speed" << std::endl;
        std::cout << "\n💡 Quick Start: Press 'A' to start the automatic demo!" << std::endl;
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
            
            // Update auto animation if enabled
            updateAutoAnimation(currentTime);
            
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
        
        // Toggle auto animation mode
        static bool aKeyPressed = false;
        if (glRenderer.isKeyPressed(GLFW_KEY_A) && !aKeyPressed) {
            autoAnimationMode = !autoAnimationMode;
            std::cout << "🎬 Auto animation mode: " << (autoAnimationMode ? "ON" : "OFF") << std::endl;
            
            if (autoAnimationMode) {
                // Activer le mode animation automatique
                std::cout << "   📹 Camera will orbit around the scene automatically" << std::endl;
                
                // Activer automatiquement le mode temps réel avec des paramètres optimisés
                isRealTimeMode = true;
                rayRenderer.setSamples(15);
                rayRenderer.setMaxDepth(6);
                std::cout << "   ⚡ Real-time rendering activated automatically" << std::endl;
                std::cout << "   🎯 Quality optimized for smooth animation (15 samples)" << std::endl;
            } else {
                // Désactiver le mode animation automatique
                std::cout << "   📷 Camera control returned to manual mode" << std::endl;
                std::cout << "   💡 Tip: Use R to toggle real-time rendering if needed" << std::endl;
            }
            aKeyPressed = true;
        } else if (!glRenderer.isKeyPressed(GLFW_KEY_A)) {
            aKeyPressed = false;
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
        
        // Animation speed controls
        handleAnimationControls();
        
        // Camera movement (only if not in auto animation mode)
        if (!autoAnimationMode) {
            handleCameraMovement();
        }
    }
    
    void handleAnimationControls() {
        static bool plusKeyPressed = false, minusKeyPressed = false;
        
        // Increase animation speed
        if (glRenderer.isKeyPressed(GLFW_KEY_EQUAL) && !plusKeyPressed) { // '+' key (without shift)
            animationSpeed = std::min(animationSpeed + 0.2f, 5.0f);
            std::cout << "⏫ Animation speed: " << animationSpeed << "x" << std::endl;
            plusKeyPressed = true;
        } else if (!glRenderer.isKeyPressed(GLFW_KEY_EQUAL)) {
            plusKeyPressed = false;
        }
        
        // Decrease animation speed  
        if (glRenderer.isKeyPressed(GLFW_KEY_MINUS) && !minusKeyPressed) {
            animationSpeed = std::max(animationSpeed - 0.2f, 0.1f);
            std::cout << "⏬ Animation speed: " << animationSpeed << "x" << std::endl;
            minusKeyPressed = true;
        } else if (!glRenderer.isKeyPressed(GLFW_KEY_MINUS)) {
            minusKeyPressed = false;
        }
    }
    
    void updateAutoAnimation(const std::chrono::high_resolution_clock::time_point& currentTime) {
        if (!autoAnimationMode) {
            return;
        }
        
        // Calculate time delta
        static auto lastAnimationTime = currentTime;
        auto deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - lastAnimationTime).count();
        lastAnimationTime = currentTime;
        
        // Update animation time
        animationTime += deltaTime * animationSpeed;
        
        // Calculate new camera position in orbit with varying height for more dynamic movement
        float angle = animationTime;
        float heightVariation = sin(animationTime * 0.5f) * 1.0f; // Slow vertical oscillation
        float radiusVariation = sin(animationTime * 0.3f) * 0.5f; // Slight radius variation
        
        float currentRadius = orbitRadius + radiusVariation;
        float x = orbitCenter.x + currentRadius * cos(angle);
        float z = orbitCenter.z + currentRadius * sin(angle);
        float y = orbitCenter.y + orbitHeight + heightVariation;
        
        // Update camera position and target
        cameraPosition = Vector3(x, y, z);
        cameraTarget = orbitCenter; // Always look at the center of the scene
        
        updateCamera();
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
        // Only allow manual camera movement if auto animation is disabled
        if (autoAnimationMode) {
            return;
        }
        
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
                         << " | Resolution: " << rayRenderer.width << "x" << rayRenderer.height;
                if (autoAnimationMode) {
                    std::cout << " | Animation: " << animationSpeed << "x speed";
                }
                std::cout << std::endl;
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
