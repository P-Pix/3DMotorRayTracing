#pragma once

#include "Point1D.hpp"
#include <iostream>

namespace Object {
    template<typename T>
class Point2D : public Object::Point1D<T> {
    private:
        T m_Y = 0;
    protected:

    public:
        Point2D(void) {
        }

        Point2D(T x, T y) {
            this->setX(x);
            this->setY(y);
        }

        Point2D(const Object::Point2D<T> &other) {
            this->setX(other.getX());
            this->setY(other.getY());
        }

        ~Point2D(void) {
        }

        T getY(void) const {
            return this->m_Y;
        }

        void setY(T y) {
            this->m_Y = y;
        }

        void set(T x, T y) {
            this->setX(x);
            this->setY(y);
        }

        float length(void) const {
            return sqrt(this->getX() * this->getX() + this->getY() * this->getY());
        }

        void normalize(void) {
            float length = this->length();
            this->setX(this->getX() / length);
            this->setY(this->getY() / length);
        }

        Object::Point2D<T> *copy(void) const {
            return new Object::Point2D<T>(this->getX(), this->getY());
        }

        void move(T x, T y) {
            this->setX(this->getX() + x);
            this->setY(this->getY() + y);
        }

        Object::Point2D<T> &operator=(const Object::Point2D<T> &other) {
            this->setX(other.getX());
            this->setY(other.getY());
            return *this;
        }

        Object::Point2D<T> operator+(const Object::Point2D<T> &other) const {
            return Object::Point2D<T>(this->getX() + other.getX(), this->getY() + other.getY());
        }

        Object::Point2D<T> operator-(const Object::Point2D<T> &other) const {
            return Object::Point2D<T>(this->getX() - other.getX(), this->getY() - other.getY());
        }

        Object::Point2D<T> operator*(const Object::Point2D<T> &other) const {
            return Object::Point2D<T>(this->getX() * other.getX(), this->getY() * other.getY());
        }

        Object::Point2D<T> operator/(const Object::Point2D<T> &other) const {
            return Object::Point2D<T>(this->getX() / other.getX(), this->getY() / other.getY());
        }
        bool operator==(const Object::Point2D<T> &other) const {
            return this->getX() == other.getX() && this->getY() == other.getY();
        }
        bool operator!=(const Object::Point2D<T> &other) const {
            return this->getX() != other.getX() || this->getY() != other.getY();
        }
        bool operator<(const Object::Point2D<T> &other) const {
            return this->getX() < other.getX() && this->getY() < other.getY();
        }
        bool operator>(const Object::Point2D<T> &other) const {
            return this->getX() > other.getX() && this->getY() > other.getY();
        }
        bool operator<=(const Object::Point2D<T> &other) const {
            return this->getX() <= other.getX() && this->getY() <= other.getY();
        }
        bool operator>=(const Object::Point2D<T> &other) const {
            return this->getX() >= other.getX() && this->getY() >= other.getY();
        }
        Object::Point2D<T> operator+=(const Object::Point2D<T> &other) {
            this->setX(this->getX() + other.getX());
            this->setY(this->getY() + other.getY());
            return *this;
        }
        Object::Point2D<T> operator-=(const Object::Point2D<T> &other) {
            this->setX(this->getX() - other.getX());
            this->setY(this->getY() - other.getY());
            return *this;
        }
        Object::Point2D<T> operator*=(const Object::Point2D<T> &other) {
            this->setX(this->getX() * other.getX());
            this->setY(this->getY() * other.getY());
            return *this;
        }
        Object::Point2D<T> operator/=(const Object::Point2D<T> &other) {
            this->setX(this->getX() / other.getX());
            this->setY(this->getY() / other.getY());
            return *this;
        }
        Object::Point2D<T> operator+=(T other) {
            this->setX(this->getX() + other);
            this->setY(this->getY() + other);
            return *this;
        }
        Object::Point2D<T> operator-=(T other) {
            this->setX(this->getX() - other);
            this->setY(this->getY() - other);
            return *this;
        }
        Object::Point2D<T> operator*=(T other) {
            this->setX(this->getX() * other);
            this->setY(this->getY() * other);
            return *this;
        }
        Object::Point2D<T> operator/=(T other) {
            this->setX(this->getX() / other);
            this->setY(this->getY() / other);
            return *this;
        }
        friend std::ostream &operator<<(std::ostream &os, const Object::Point2D<T> &Point) {
            os << "(" << Point.getX() << ", " << Point.getY() << ")";
            return os;
        }
    };
}