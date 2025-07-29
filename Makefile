# 3D Ray Tracing Engine Makefile

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O3 -pthread
INCLUDES = -Iinclude
OPENGL_LIBS = -lGL -lGLEW -lglfw -lm
CPU_LIBS = -pthread

# Directories
SRCDIR = src
INCDIR = include
BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj

# Common source files (without main files)
COMMON_SOURCES = $(SRCDIR)/Vector3.cpp $(SRCDIR)/Color.cpp $(SRCDIR)/Ray.cpp \
                 $(SRCDIR)/Material.cpp $(SRCDIR)/Sphere.cpp $(SRCDIR)/Plane.cpp \
                 $(SRCDIR)/Scene.cpp $(SRCDIR)/Camera.cpp $(SRCDIR)/Renderer.cpp \
                 $(SRCDIR)/ImageWriter.cpp

# OpenGL specific sources
OPENGL_SOURCES = $(COMMON_SOURCES) $(SRCDIR)/OpenGLRenderer.cpp $(SRCDIR)/main.cpp

# CPU only sources
CPU_SOURCES = $(COMMON_SOURCES) $(SRCDIR)/main_cpu.cpp

# Object files
OPENGL_OBJECTS = $(OPENGL_SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
CPU_OBJECTS = $(CPU_SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Target executables
OPENGL_TARGET = $(BUILDDIR)/raytracer_opengl
CPU_TARGET = $(BUILDDIR)/raytracer_cpu

# Default target (try OpenGL first, fallback to CPU)
all: check-opengl

# Check OpenGL availability and build accordingly
check-opengl:
	@echo "Checking OpenGL availability..."
	@if pkg-config --exists glfw3 && pkg-config --exists glew; then \
		echo "✅ OpenGL libraries found, building OpenGL version..."; \
		$(MAKE) opengl; \
	else \
		echo "⚠️  OpenGL libraries not found, building CPU-only version..."; \
		$(MAKE) cpu; \
	fi

# Create build directories
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Compile object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Build OpenGL version
opengl: $(OPENGL_TARGET)

$(OPENGL_TARGET): $(OPENGL_OBJECTS) | $(BUILDDIR)
	$(CXX) $(OPENGL_OBJECTS) -o $@ $(OPENGL_LIBS)
	@echo "✅ OpenGL Ray Tracer build complete: $(OPENGL_TARGET)"

# Build CPU-only version
cpu: $(CPU_TARGET)

$(CPU_TARGET): $(CPU_OBJECTS) | $(BUILDDIR)
	$(CXX) $(CPU_OBJECTS) -o $@ $(CPU_LIBS)
	@echo "✅ CPU Ray Tracer build complete: $(CPU_TARGET)"

# Build both versions
both: $(OPENGL_TARGET) $(CPU_TARGET)

# Run the appropriate version
run: all
	@if [ -f "$(OPENGL_TARGET)" ]; then \
		echo "🚀 Running OpenGL version..."; \
		./$(OPENGL_TARGET); \
	elif [ -f "$(CPU_TARGET)" ]; then \
		echo "🚀 Running CPU version..."; \
		./$(CPU_TARGET); \
	else \
		echo "❌ No executable found. Build first with 'make all'"; \
	fi

# Run OpenGL version specifically
run-opengl: $(OPENGL_TARGET)
	./$(OPENGL_TARGET)

# Run CPU version specifically  
run-cpu: $(CPU_TARGET)
	./$(CPU_TARGET)

# Debug build
debug: CXXFLAGS = -std=c++17 -Wall -Wextra -g -pthread -DDEBUG
debug: all

# Clean build files
clean:
	rm -rf $(BUILDDIR)
	rm -f *.ppm output/*.png 2>/dev/null || true
	@echo "🧹 Clean complete"

# Install dependencies (Ubuntu/Debian)
install-deps:
	@echo "📦 Installing dependencies..."
	sudo apt-get update
	sudo apt-get install -y build-essential cmake pkg-config
	sudo apt-get install -y libgl1-mesa-dev libglew-dev libglfw3-dev
	@echo "✅ Dependencies installed"

# Check OpenGL installation
check-deps:
	@echo "🔍 Checking OpenGL dependencies..."
	@if command -v pkg-config >/dev/null 2>&1; then \
		echo "✅ pkg-config found"; \
	else \
		echo "❌ pkg-config not found"; \
	fi
	@if pkg-config --exists glfw3; then \
		echo "✅ GLFW3 found: $$(pkg-config --modversion glfw3)"; \
	else \
		echo "❌ GLFW3 not found"; \
	fi
	@if pkg-config --exists glew; then \
		echo "✅ GLEW found: $$(pkg-config --modversion glew)"; \
	else \
		echo "❌ GLEW not found"; \
	fi

# Help
help:
	@echo "🎯 3D Ray Tracing Engine - Available targets:"
	@echo ""
	@echo "Build targets:"
	@echo "  all          - Auto-detect and build appropriate version"
	@echo "  opengl       - Build OpenGL version (requires OpenGL libraries)"
	@echo "  cpu          - Build CPU-only version"
	@echo "  both         - Build both versions"
	@echo ""
	@echo "Run targets:"
	@echo "  run          - Run the available version"
	@echo "  run-opengl   - Run OpenGL version specifically"
	@echo "  run-cpu      - Run CPU version specifically"
	@echo ""
	@echo "Utility targets:"
	@echo "  debug        - Build with debug symbols"
	@echo "  clean        - Remove build files and generated images"
	@echo "  install-deps - Install required dependencies (Ubuntu/Debian)"
	@echo "  check-deps   - Check if OpenGL dependencies are available"
	@echo "  help         - Show this help message"

.PHONY: all check-opengl opengl cpu both run run-opengl run-cpu debug clean install-deps check-deps help