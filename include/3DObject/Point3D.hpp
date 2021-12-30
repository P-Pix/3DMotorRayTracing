#pragma once

#include "Point2D.hpp"

namespace Object {
    template<typename T>
    class Point3D : public Object::Point2D<T> {
    private:
        T m_Z = 0;
    protected:
    public:
        Point3D(void) {

        }
        Point3D(T x, T y, T z) {
        this->setX(x);
        this->setY(y);
        this->setZ(z);
        }
        Point3D(const Object::Point3D<T>& Point) {
            this->setX(Point.getX());
            this->setY(Point.getY());
            this->setZ(Point.getZ());
        }
        Point3D(const Object::Point2D<T>& Point) {
            this->setX(Point.getX());
            this->setY(Point.getY());
            this->setZ(0);
        }
        ~Point3D(void) {

        }
        T getZ(void) const {
            return this->m_Z;
        }
        void setZ(T z) {
            this->m_Z = z;
        }
        void set(T x, T y, T z) {
            this->setX(x);
            this->setY(y);
            this->setZ(z);
        }
        float length(void) const {
            return sqrt(this->m_X * this->m_X + this->m_Y * this->m_Y + this->m_Z * this->m_Z);
        }
        void normalize(void) {
            float length = this->length();
            if (length != 0) {
                this->setX(this->getX() / length);
                this->setY(this->getY() / length);
                this->setZ(this->getZ() / length);
            }
        }
        Object::Point3D<T> *copy(void) const {
            return new Object::Point3D<T>(this->getX(), this->getY(), this->getZ());
        }
        Object::Point3D<T>& operator=(const Object::Point3D<T>& Point) {
            this->setX(Point.getX());
            this->setY(Point.getY());
            this->setZ(Point.getZ());
            return *this;
        }
        Object::Point3D<T> operator+(const Object::Point3D<T>& Point) const {
            return Object::Point3D<T>(this->getX() + Point.getX(), this->getY() + Point.getY(), this->getZ() + Point.getZ());
        }
        Object::Point3D<T> operator-(const Object::Point3D<T>& Point) const {
            return Object::Point3D<T>(this->getX() - Point.getX(), this->getY() - Point.getY(), this->getZ() - Point.getZ());
        }
        Object::Point3D<T> operator*(const Object::Point3D<T>& Point) const {
            return Object::Point3D<T>(this->getX() * Point.getX(), this->getY() * Point.getY(), this->getZ() * Point.getZ());
        }
        Object::Point3D<T> operator/(const Object::Point3D<T>& Point) const {
            return Object::Point3D<T>(this->getX() / Point.getX(), this->getY() / Point.getY(), this->getZ() / Point.getZ());
        }
        Object::Point3D<T> operator+(const T& value) const {
            return Object::Point3D<T>(this->getX() + value, this->getY() + value, this->getZ() + value);
        }
        Object::Point3D<T> operator-(const T& value) const {
            return Object::Point3D<T>(this->getX() - value, this->getY() - value, this->getZ() - value);
        }
        Object::Point3D<T> operator*(const T& value) const {
            return Object::Point3D<T>(this->getX() * value, this->getY() * value, this->getZ() * value);
        }
        Object::Point3D<T> operator/(const T& value) const {
            return Object::Point3D<T>(this->getX() / value, this->getY() / value, this->getZ() / value);
        }
    };
}