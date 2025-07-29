#include "Color.h"
#include <cmath>

// Static colors
const Color Color::BLACK(0.0f, 0.0f, 0.0f);
const Color Color::WHITE(1.0f, 1.0f, 1.0f);
const Color Color::RED(1.0f, 0.0f, 0.0f);
const Color Color::GREEN(0.0f, 1.0f, 0.0f);
const Color Color::BLUE(0.0f, 0.0f, 1.0f);
const Color Color::YELLOW(1.0f, 1.0f, 0.0f);
const Color Color::MAGENTA(1.0f, 0.0f, 1.0f);
const Color Color::CYAN(0.0f, 1.0f, 1.0f);

// Operations
Color Color::operator+(const Color& other) const {
    return Color(r + other.r, g + other.g, b + other.b, a + other.a);
}

Color Color::operator-(const Color& other) const {
    return Color(r - other.r, g - other.g, b - other.b, a - other.a);
}

Color Color::operator*(const Color& other) const {
    return Color(r * other.r, g * other.g, b * other.b, a * other.a);
}

Color Color::operator*(float scalar) const {
    return Color(r * scalar, g * scalar, b * scalar, a);
}

Color Color::operator/(float scalar) const {
    return Color(r / scalar, g / scalar, b / scalar, a);
}

Color& Color::operator+=(const Color& other) {
    r += other.r;
    g += other.g;
    b += other.b;
    a += other.a;
    return *this;
}

Color& Color::operator-=(const Color& other) {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    a -= other.a;
    return *this;
}

Color& Color::operator*=(const Color& other) {
    r *= other.r;
    g *= other.g;
    b *= other.b;
    a *= other.a;
    return *this;
}

Color& Color::operator*=(float scalar) {
    r *= scalar;
    g *= scalar;
    b *= scalar;
    return *this;
}

Color& Color::operator/=(float scalar) {
    r /= scalar;
    g /= scalar;
    b /= scalar;
    return *this;
}

// Utility methods
void Color::clamp() {
    r = std::clamp(r, 0.0f, 1.0f);
    g = std::clamp(g, 0.0f, 1.0f);
    b = std::clamp(b, 0.0f, 1.0f);
    a = std::clamp(a, 0.0f, 1.0f);
}

Color Color::clamped() const {
    Color result = *this;
    result.clamp();
    return result;
}

void Color::gammaCorrect(float gamma) {
    r = pow(r, 1.0f / gamma);
    g = pow(g, 1.0f / gamma);
    b = pow(b, 1.0f / gamma);
}

Color Color::gammaCorrected(float gamma) const {
    Color result = *this;
    result.gammaCorrect(gamma);
    return result;
}

// Utility
std::ostream& operator<<(std::ostream& os, const Color& c) {
    os << "RGBA(" << c.r << ", " << c.g << ", " << c.b << ", " << c.a << ")";
    return os;
}

// Global operators
Color operator*(float scalar, const Color& color) {
    return color * scalar;
}
