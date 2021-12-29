#pragma once

#include "Vector2D.hpp"

namespace Structure {
    template<typename T>
    class Vector3D : public Structure::Vector2D<T> {
    private:
        T m_Z = 0;
    protected:
    public:
        Vector3D(void) {

        }
        Vector3D(T x, T y, T z) {
        this->setX(x);
        this->setY(y);
        this->setZ(z);
        }
        Vector3D(const Vector3D<T>& vector) {
            this->setX(vector.getX());
            this->setY(vector.getY());
            this->setZ(vector.getZ());
        }
        Vector3D(const Structure::Vector2D<T>& vector) {
            this->setX(vector.getX());
            this->setY(vector.getY());
            this->setZ(0);
        }
        ~Vector3D(void) {

        }
        T getZ(void) const {
            return this->m_Z;
        }
        void setZ(T z) {
            this->m_Z = z;
        }
        Vector3D<T>& operator=(const Vector3D<T>& vector) {
            this->setX(vector.getX());
            this->setY(vector.getY());
            this->setZ(vector.getZ());
            return *this;
        }
        Vector3D<T> operator+(const Vector3D<T>& vector) const {
            return Vector3D<T>(this->getX() + vector.getX(), this->getY() + vector.getY(), this->getZ() + vector.getZ());
        }
        Vector3D<T> operator-(const Vector3D<T>& vector) const {
            return Vector3D<T>(this->getX() - vector.getX(), this->getY() - vector.getY(), this->getZ() - vector.getZ());
        }
        Vector3D<T> operator*(const Vector3D<T>& vector) const {
            return Vector3D<T>(this->getX() * vector.getX(), this->getY() * vector.getY(), this->getZ() * vector.getZ());
        }
        Vector3D<T> operator/(const Vector3D<T>& vector) const {
            return Vector3D<T>(this->getX() / vector.getX(), this->getY() / vector.getY(), this->getZ() / vector.getZ());
        }
        Vector3D<T> operator+(const T& value) const {
            return Vector3D<T>(this->getX() + value, this->getY() + value, this->getZ() + value);
        }
        Vector3D<T> operator-(const T& value) const {
            return Vector3D<T>(this->getX() - value, this->getY() - value, this->getZ() - value);
        }
        Vector3D<T> operator*(const T& value) const {
            return Vector3D<T>(this->getX() * value, this->getY() * value, this->getZ() * value);
        }
        Vector3D<T> operator/(const T& value) const {
            return Vector3D<T>(this->getX() / value, this->getY() / value, this->getZ() / value);
        }
    };
}