#ifndef RENDERER_H
#define RENDERER_H

#include "Scene.h"
#include "Camera.h"
#include "Color.h"
#include <vector>
#include <thread>

class Renderer {
public:
    int width;
    int height;
    int samples;
    int maxDepth;
    int numThreads;

    Renderer(int width = 800, int height = 600, int samples = 100, int maxDepth = 10, int numThreads = 8);

    // Rendering methods
    std::vector<Color> render(const Scene& scene, const Camera& camera);
    std::vector<unsigned char> renderToBytes(const Scene& scene, const Camera& camera);
    
    // Settings
    void setResolution(int width, int height);
    void setSamples(int samples);
    void setMaxDepth(int maxDepth);
    void setNumThreads(int numThreads);

private:
    void renderSection(const Scene& scene, const Camera& camera, std::vector<Color>& pixels,
                      int startY, int endY, int width, int height, int samples, int maxDepth);
    
    Color gammaCorrect(const Color& color, float gamma = 2.2f);
};

#endif // RENDERER_H
