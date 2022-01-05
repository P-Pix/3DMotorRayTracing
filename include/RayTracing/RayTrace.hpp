#pragma once

#include "Line.hpp"
#include "Camera.hpp"
#include "Screen.hpp"

namespace RayTracing {
class RayTrace : public RayTracing::Line {
private:
    Camera m_Camera;
    Screen m_Screen;
    };
}