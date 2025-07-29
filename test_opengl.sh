#!/bin/bash

echo "🔍 Testing OpenGL Ray Tracing Engine Build"
echo "=========================================="

# Check if we're in the right directory
if [ ! -f "Makefile" ]; then
    echo "❌ Error: Not in project root directory"
    exit 1
fi

# Test OpenGL availability
echo "📋 Checking OpenGL dependencies..."
if pkg-config --exists glfw3 glew; then
    echo "✅ GLFW3 and GLEW found"
    echo "   GLFW3 version: $(pkg-config --modversion glfw3)"
    echo "   GLEW version: $(pkg-config --modversion glew)"
else
    echo "❌ OpenGL dependencies not found"
    echo "   Install with: sudo apt-get install libglfw3-dev libglew-dev"
    echo "   Or on other systems, install GLFW3 and GLEW development packages"
    exit 1
fi

# Clean previous builds
echo ""
echo "🧹 Cleaning previous builds..."
make clean >/dev/null 2>&1

# Try to build OpenGL version
echo ""
echo "🔨 Building OpenGL ray tracer..."
if make opengl; then
    echo ""
    echo "✅ OpenGL build successful!"
    
    # Check if executable exists
    if [ -f "raytracer_opengl" ]; then
        echo "✅ Executable 'raytracer_opengl' created"
        ls -lh raytracer_opengl
        
        echo ""
        echo "🎮 Ready to run interactive ray tracing!"
        echo "   To start: ./raytracer_opengl"
        echo ""
        echo "   Controls once running:"
        echo "   - ESC: Exit"
        echo "   - R: Toggle real-time rendering"
        echo "   - SPACE: Render high-quality frame"
        echo "   - S: Save current frame"
        echo "   - 1-3: Quality presets"
        echo "   - WASD: Move camera"
        echo "   - QE: Move up/down"
        echo "   - H/L: Increase/decrease quality"
        
    else
        echo "❌ Build succeeded but executable not found"
        exit 1
    fi
else
    echo ""
    echo "❌ OpenGL build failed"
    echo "   Trying CPU-only fallback..."
    
    if make cpu; then
        echo "✅ CPU-only version built successfully: raytracer_cpu"
        echo "   Your system may not support OpenGL, but CPU version works"
    else
        echo "❌ Both OpenGL and CPU builds failed"
        exit 1
    fi
fi

echo ""
echo "🏁 Build test complete!"
