#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <iostream>

class Vector3 {
public:
    float x, y, z;

    // Constructors
    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z) {}
    Vector3& operator=(const Vector3& other) = default;

    // Basic operations
    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator-() const; // Unary minus
    Vector3 operator*(float scalar) const;
    Vector3 operator/(float scalar) const;
    Vector3& operator+=(const Vector3& other);
    Vector3& operator-=(const Vector3& other);
    Vector3& operator*=(float scalar);
    Vector3& operator/=(float scalar);

    // Vector operations
    float dot(const Vector3& other) const;
    Vector3 cross(const Vector3& other) const;
    float length() const;
    float lengthSquared() const;
    Vector3 normalized() const;
    void normalize();

    // Static methods
    static float distance(const Vector3& a, const Vector3& b);
    static Vector3 reflect(const Vector3& incident, const Vector3& normal);
    static Vector3 refract(const Vector3& incident, const Vector3& normal, float eta);

    // Utility
    friend std::ostream& operator<<(std::ostream& os, const Vector3& v);
};

// Global operators
Vector3 operator*(float scalar, const Vector3& vector);

#endif // VECTOR3_H
