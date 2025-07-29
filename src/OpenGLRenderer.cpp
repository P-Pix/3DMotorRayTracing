#include "OpenGLRenderer.h"
#include <iostream>
#include <sstream>

// Static member definitions
bool OpenGLRenderer::keys[1024] = {false};
float OpenGLRenderer::mouseX = 0.0f;
float OpenGLRenderer::mouseY = 0.0f;
bool OpenGLRenderer::firstMouse = true;
float OpenGLRenderer::sensitivity = 0.1f;

OpenGLRenderer::OpenGLRenderer(int width, int height, const std::string& title)
    : window(nullptr), windowWidth(width), windowHeight(height), quadVAO(0), quadVBO(0), shaderProgram(0) {
    
    // Set error callback before initialization
    glfwSetErrorCallback(errorCallback);
    
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "❌ Failed to initialize GLFW" << std::endl;
        return;
    }

    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x MSAA

    // Create window
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "❌ Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    
    // Set callbacks
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    
    // Enable v-sync
    glfwSwapInterval(1);
    
    std::cout << "✅ GLFW window created successfully" << std::endl;
}
}

OpenGLRenderer::~OpenGLRenderer() {
    cleanup();
}

bool OpenGLRenderer::initialize() {
    if (!window) {
        return false;
    }

    // Initialize GLEW
    glewExperimental = GL_TRUE; // Enable experimental features
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        std::cerr << "❌ Failed to initialize GLEW: " << glewGetErrorString(glewError) << std::endl;
        return false;
    }
    
    // Clear any GLEW initialization errors
    glGetError();

    // Print OpenGL information
    std::cout << "✅ OpenGL initialized successfully" << std::endl;
    std::cout << "   Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "   Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "   Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "   GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    // Set viewport
    glViewport(0, 0, windowWidth, windowHeight);

    // Setup rendering state
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_MULTISAMPLE); // Enable MSAA
    
    // Setup quad for rendering
    setupQuad();
    
    // Create shader program
    std::string vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec2 aPos;
        layout (location = 1) in vec2 aTexCoord;

        out vec2 TexCoord;

        void main() {
            gl_Position = vec4(aPos, 0.0, 1.0);
            TexCoord = aTexCoord;
        }
    )";
    
    std::string fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;

        in vec2 TexCoord;
        uniform sampler2D ourTexture;
        uniform float gamma = 2.2;

        void main() {
            vec3 color = texture(ourTexture, TexCoord).rgb;
            // Gamma correction
            color = pow(color, vec3(1.0/gamma));
            FragColor = vec4(color, 1.0);
        }
    )";
    
    shaderProgram = loadShader(vertexShaderSource, fragmentShaderSource);
    if (shaderProgram == 0) {
        return false;
    }

    std::cout << "✅ OpenGL Renderer initialized successfully" << std::endl;
    return true;
}

void OpenGLRenderer::cleanup() {
    if (quadVAO) {
        glDeleteVertexArrays(1, &quadVAO);
        quadVAO = 0;
    }
    if (quadVBO) {
        glDeleteBuffers(1, &quadVBO);
        quadVBO = 0;
    }
    if (shaderProgram) {
        glDeleteProgram(shaderProgram);
        shaderProgram = 0;
    }
    if (window) {
        glfwDestroyWindow(window);
        window = nullptr;
    }
    glfwTerminate();
}

bool OpenGLRenderer::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void OpenGLRenderer::swapBuffers() {
    glfwSwapBuffers(window);
}

void OpenGLRenderer::pollEvents() {
    glfwPollEvents();
}

void OpenGLRenderer::clear() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

GLuint OpenGLRenderer::createTexture(int width, int height, const unsigned char* data) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    
    return texture;
}

void OpenGLRenderer::updateTexture(GLuint textureId, int width, int height, const unsigned char* data) {
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
}

void OpenGLRenderer::renderTexture(GLuint textureId) {
    useShader(shaderProgram);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

// Input handling methods
bool OpenGLRenderer::isKeyPressed(int key) const {
    if (key >= 0 && key < 1024) {
        return keys[key];
    }
    return false;
}

void OpenGLRenderer::getMousePosition(float& x, float& y) const {
    x = mouseX;
    y = mouseY;
}

GLuint OpenGLRenderer::loadShader(const std::string& vertexSource, const std::string& fragmentSource) {
    GLuint vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);
    
    if (vertexShader == 0 || fragmentShader == 0) {
        return 0;
    }
    
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    
    if (!checkProgramLink(program)) {
        glDeleteProgram(program);
        return 0;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return program;
}

void OpenGLRenderer::useShader(GLuint shaderProgram) {
    glUseProgram(shaderProgram);
}

void OpenGLRenderer::setupQuad() {
    float quadVertices[] = {
        // Positions   // Texture coords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
        
        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
    
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindVertexArray(0);
}

GLuint OpenGLRenderer::compileShader(const std::string& source, GLenum type) {
    GLuint shader = glCreateShader(type);
    const char* sourceCStr = source.c_str();
    glShaderSource(shader, 1, &sourceCStr, nullptr);
    glCompileShader(shader);
    
    if (!checkShaderCompile(shader)) {
        glDeleteShader(shader);
        return 0;
    }
    
    return shader;
}

bool OpenGLRenderer::checkShaderCompile(GLuint shader) {
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        std::cerr << "Shader compilation error: " << infoLog << std::endl;
        return false;
    }
    return true;
}

bool OpenGLRenderer::checkProgramLink(GLuint program) {
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetProgramInfoLog(program, 1024, nullptr, infoLog);
        std::cerr << "Program linking error: " << infoLog << std::endl;
        return false;
    }
    return true;
}

// Callback functions
void OpenGLRenderer::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            keys[key] = true;
        } else if (action == GLFW_RELEASE) {
            keys[key] = false;
        }
    }
}

void OpenGLRenderer::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        mouseX = xpos;
        mouseY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - mouseX;
    float yoffset = mouseY - ypos; // Reversed since y-coordinates go from bottom to top
    
    mouseX = xpos;
    mouseY = ypos;
    
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    
    // Here you can implement camera rotation based on mouse movement
}

void OpenGLRenderer::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    // Here you can implement zoom functionality
}

void OpenGLRenderer::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void OpenGLRenderer::errorCallback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}
