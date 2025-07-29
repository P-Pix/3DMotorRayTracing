#include "Vector3.h"

// Basic operations
Vector3 Vector3::operator+(const Vector3& other) const {
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other) const {
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator-() const {
    return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator*(float scalar) const {
    return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 Vector3::operator/(float scalar) const {
    return Vector3(x / scalar, y / scalar, z / scalar);
}

Vector3& Vector3::operator+=(const Vector3& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector3& Vector3::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector3& Vector3::operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

// Vector operations
float Vector3::dot(const Vector3& other) const {
    return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::cross(const Vector3& other) const {
    return Vector3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

float Vector3::length() const {
    return sqrt(x * x + y * y + z * z);
}

float Vector3::lengthSquared() const {
    return x * x + y * y + z * z;
}

Vector3 Vector3::normalized() const {
    float len = length();
    if (len > 0.0f) {
        return *this / len;
    }
    return Vector3(0.0f, 0.0f, 0.0f);
}

void Vector3::normalize() {
    float len = length();
    if (len > 0.0f) {
        *this /= len;
    }
}

// Static methods
float Vector3::distance(const Vector3& a, const Vector3& b) {
    return (a - b).length();
}

Vector3 Vector3::reflect(const Vector3& incident, const Vector3& normal) {
    return incident - 2.0f * incident.dot(normal) * normal;
}

Vector3 Vector3::refract(const Vector3& incident, const Vector3& normal, float eta) {
    float cosI = -normal.dot(incident);
    float sinT2 = eta * eta * (1.0f - cosI * cosI);
    if (sinT2 > 1.0f) {
        return Vector3(0.0f, 0.0f, 0.0f); // Total internal reflection
    }
    float cosT = sqrt(1.0f - sinT2);
    return eta * incident + (eta * cosI - cosT) * normal;
}

// Utility
std::ostream& operator<<(std::ostream& os, const Vector3& v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

// Global operators
Vector3 operator*(float scalar, const Vector3& vector) {
    return vector * scalar;
}
