#pragma once

#include "Point2D.hpp"

namespace Point {
    template<typename T>
    class D3 : public Point::D2<T> {
    private:
        T m_Z = 0;
    protected:
    public:
        D3(void) {

        }

        D3(T x, T y, T z) {
            this->setX(x);
            this->setY(y);
            this->setZ(z);
        }

        D3(const Point::D3<T> &Point) {
            this->setX(Point.getX());
            this->setY(Point.getY());
            this->setZ(Point.getZ());
        }

        D3(const Point::D2<T> &Point) {
            this->setX(Point.getX());
            this->setY(Point.getY());
            this->setZ(0);
        }

        ~D3(void) {

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

        Point::D3<T> *copy(void) const {
            return new Point::D3<T>(this->getX(), this->getY(), this->getZ());
        }

        Point::D3<T> &operator=(const Point::D3<T> &Point) {
            this->setX(Point.getX());
            this->setY(Point.getY());
            this->setZ(Point.getZ());
            return *this;
        }

        Point::D3<T> operator+(const Point::D3<T> &Point) const {
            return Point::D3<T>(this->getX() + Point.getX(), this->getY() + Point.getY(), this->getZ() + Point.getZ());
        }

        Point::D3<T> operator-(const Point::D3<T> &Point) const {
            return Point::D3<T>(this->getX() - Point.getX(), this->getY() - Point.getY(), this->getZ() - Point.getZ());
        }

        Point::D3<T> operator*(const Point::D3<T> &Point) const {
            return Point::D3<T>(this->getX() * Point.getX(), this->getY() * Point.getY(), this->getZ() * Point.getZ());
        }

        Point::D3<T> operator/(const Point::D3<T> &Point) const {
            return Point::D3<T>(this->getX() / Point.getX(), this->getY() / Point.getY(), this->getZ() / Point.getZ());
        }

        Point::D3<T> operator+(const T &value) const {
            return Point::D3<T>(this->getX() + value, this->getY() + value, this->getZ() + value);
        }

        Point::D3<T> operator-(const T &value) const {
            return Point::D3<T>(this->getX() - value, this->getY() - value, this->getZ() - value);
        }

        Point::D3<T> operator*(const T &value) const {
            return Point::D3<T>(this->getX() * value, this->getY() * value, this->getZ() * value);
        }

        Point::D3<T> operator/(const T &value) const {
            return Point::D3<T>(this->getX() / value, this->getY() / value, this->getZ() / value);
        }
    };
}