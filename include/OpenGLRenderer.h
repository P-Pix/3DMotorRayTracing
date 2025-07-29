#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

class OpenGLRenderer {
public:
    GLFWwindow* window;
    int windowWidth;
    int windowHeight;
    
    OpenGLRenderer(int width = 800, int height = 600, const std::string& title = "3D Ray Tracing Engine");
    ~OpenGLRenderer();

    // Initialization and cleanup
    bool initialize();
    void cleanup();

    // Rendering
    bool shouldClose() const;
    void swapBuffers();
    void pollEvents();
    void clear();
    
    // Texture operations
    GLuint createTexture(int width, int height, const unsigned char* data);
    void updateTexture(GLuint textureId, int width, int height, const unsigned char* data);
    void renderTexture(GLuint textureId);

    // Shader operations
    GLuint loadShader(const std::string& vertexSource, const std::string& fragmentSource);
    void useShader(GLuint shaderProgram);

    // Input handling
    bool isKeyPressed(int key) const;
    void getMousePosition(float& x, float& y) const;
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void errorCallback(int error, const char* description);

private:
    GLuint quadVAO, quadVBO;
    GLuint shaderProgram;
    
    void setupQuad();
    GLuint compileShader(const std::string& source, GLenum type);
    bool checkShaderCompile(GLuint shader);
    bool checkProgramLink(GLuint program);
    
    static bool keys[1024];
    static float mouseX, mouseY;
    static bool firstMouse;
    static float sensitivity;
};

#endif // OPENGL_RENDERER_H
