#ifndef COLOR_H
#define COLOR_H

#include <algorithm>
#include <iostream>

class Color {
public:
    float r, g, b, a;

    // Constructors
    Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}
    Color(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a) {}
    Color(const Color& other) : r(other.r), g(other.g), b(other.b), a(other.a) {}
    Color& operator=(const Color& other) = default;

    // Operations
    Color operator+(const Color& other) const;
    Color operator-(const Color& other) const;
    Color operator*(const Color& other) const; // Component-wise multiplication
    Color operator*(float scalar) const;
    Color operator/(float scalar) const;
    Color& operator+=(const Color& other);
    Color& operator-=(const Color& other);
    Color& operator*=(const Color& other);
    Color& operator*=(float scalar);
    Color& operator/=(float scalar);

    // Utility methods
    void clamp();
    Color clamped() const;
    void gammaCorrect(float gamma = 2.2f);
    Color gammaCorrected(float gamma = 2.2f) const;

    // Static colors
    static const Color BLACK;
    static const Color WHITE;
    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    static const Color YELLOW;
    static const Color MAGENTA;
    static const Color CYAN;

    // Utility
    friend std::ostream& operator<<(std::ostream& os, const Color& c);
};

// Global operators
Color operator*(float scalar, const Color& color);

#endif // COLOR_H
