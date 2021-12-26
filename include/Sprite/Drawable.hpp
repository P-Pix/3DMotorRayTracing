#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>

namespace Motor3D {
    class Drawable {
    private:
    protected:
    public:
        Drawable(void);
        virtual ~Drawable(void);
        virtual void draw(void) = 0;
    };
}