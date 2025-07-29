#include "Renderer.h"
#include <random>
#include <iostream>
#include <algorithm>

Renderer::Renderer(int width, int height, int samples, int maxDepth, int numThreads)
    : width(width), height(height), samples(samples), maxDepth(maxDepth), numThreads(numThreads) {}

std::vector<Color> Renderer::render(const Scene& scene, const Camera& camera) {
    std::vector<Color> pixels(width * height);
    
    std::vector<std::thread> threads;
    int sectionHeight = height / numThreads;
    
    for (int t = 0; t < numThreads; ++t) {
        int startY = t * sectionHeight;
        int endY = (t == numThreads - 1) ? height : (t + 1) * sectionHeight;
        
        threads.emplace_back(&Renderer::renderSection, this, std::cref(scene), std::cref(camera),
                           std::ref(pixels), startY, endY, width, height, samples, maxDepth);
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    return pixels;
}

std::vector<unsigned char> Renderer::renderToBytes(const Scene& scene, const Camera& camera) {
    std::vector<Color> pixels = render(scene, camera);
    std::vector<unsigned char> bytes(width * height * 3);
    
    for (int i = 0; i < pixels.size(); ++i) {
        Color corrected = gammaCorrect(pixels[i].clamped());
        bytes[i * 3] = static_cast<unsigned char>(corrected.r * 255);
        bytes[i * 3 + 1] = static_cast<unsigned char>(corrected.g * 255);
        bytes[i * 3 + 2] = static_cast<unsigned char>(corrected.b * 255);
    }
    
    return bytes;
}

void Renderer::setResolution(int width, int height) {
    this->width = width;
    this->height = height;
}

void Renderer::setSamples(int samples) {
    this->samples = samples;
}

void Renderer::setMaxDepth(int maxDepth) {
    this->maxDepth = maxDepth;
}

void Renderer::setNumThreads(int numThreads) {
    this->numThreads = numThreads;
}

void Renderer::renderSection(const Scene& scene, const Camera& camera, std::vector<Color>& pixels,
                            int startY, int endY, int width, int height, int samples, int maxDepth) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    
    for (int y = startY; y < endY; ++y) {
        for (int x = 0; x < width; ++x) {
            Color pixelColor = Color::BLACK;
            
            for (int s = 0; s < samples; ++s) {
                float u = (float(x) + dis(gen)) / float(width);
                float v = (float(height - 1 - y) + dis(gen)) / float(height);
                
                Ray ray = camera.getRay(u, v);
                pixelColor += scene.rayColor(ray, 0, maxDepth);
            }
            
            pixelColor /= float(samples);
            pixels[y * width + x] = pixelColor;
        }
        
        // Progress indicator
        if (y % 10 == 0) {
            float progress = float(y - startY) / float(endY - startY) * 100.0f;
            std::cout << "Thread rendering: " << progress << "% complete\r" << std::flush;
        }
    }
}

Color Renderer::gammaCorrect(const Color& color, float gamma) {
    return Color(
        pow(color.r, 1.0f / gamma),
        pow(color.g, 1.0f / gamma),
        pow(color.b, 1.0f / gamma),
        color.a
    );
}
