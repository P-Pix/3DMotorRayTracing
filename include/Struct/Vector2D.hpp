#pragma once

#include "Vector1D.hpp"
#include <iostream>

namespace Structure {
    template<typename T>
    class Vector2D : public Vector1D<T> {
    private:
        T m_Y = 0;
    protected:

    public:
        Vector2D(void) {
        }

        Vector2D(T x, T y) : Vector1D<T>(x) {
            this->setY(y);
        }

        Vector2D(const Vector2D<T> &other) {
            this->setX(other.getX());
            this->setY(other.getY());
        }

        ~Vector2D(void) {
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

        void move(T x, T y) {
            this->setX(this->getX() + x);
            this->setY(this->getY() + y);
        }

        Vector2D<T> &operator=(const Vector2D<T> &other) {
            this->setX(other.getX());
            this->setY(other.getY());
            return *this;
        }

        Vector2D<T> operator+(const Vector2D<T> &other) const {
            return Vector2D<T>(this->getX() + other.getX(), this->getY() + other.getY());
        }

        Vector2D<T> operator-(const Vector2D<T> &other) const {
            return Vector2D<T>(this->getX() - other.getX(), this->getY() - other.getY());
        }

        Vector2D<T> operator*(const Vector2D<T> &other) const {
            return Vector2D<T>(this->getX() * other.getX(), this->getY() * other.getY());
        }

        Vector2D<T> operator/(const Vector2D<T> &other) const {
            return Vector2D<T>(this->getX() / other.getX(), this->getY() / other.getY());
        }
        bool operator==(const Vector2D<T> &other) const {
            return this->getX() == other.getX() && this->getY() == other.getY();
        }
        bool operator!=(const Vector2D<T> &other) const {
            return this->getX() != other.getX() || this->getY() != other.getY();
        }
        bool operator<(const Vector2D<T> &other) const {
            return this->getX() < other.getX() && this->getY() < other.getY();
        }
        bool operator>(const Vector2D<T> &other) const {
            return this->getX() > other.getX() && this->getY() > other.getY();
        }
        bool operator<=(const Vector2D<T> &other) const {
            return this->getX() <= other.getX() && this->getY() <= other.getY();
        }
        bool operator>=(const Vector2D<T> &other) const {
            return this->getX() >= other.getX() && this->getY() >= other.getY();
        }
        Vector2D<T> operator+=(const Vector2D<T> &other) {
            this->setX(this->getX() + other.getX());
            this->setY(this->getY() + other.getY());
            return *this;
        }
        Vector2D<T> operator-=(const Vector2D<T> &other) {
            this->setX(this->getX() - other.getX());
            this->setY(this->getY() - other.getY());
            return *this;
        }
        Vector2D<T> operator*=(const Vector2D<T> &other) {
            this->setX(this->getX() * other.getX());
            this->setY(this->getY() * other.getY());
            return *this;
        }
        Vector2D<T> operator/=(const Vector2D<T> &other) {
            this->setX(this->getX() / other.getX());
            this->setY(this->getY() / other.getY());
            return *this;
        }
        Vector2D<T> operator+=(T other) {
            this->setX(this->getX() + other);
            this->setY(this->getY() + other);
            return *this;
        }
        Vector2D<T> operator-=(T other) {
            this->setX(this->getX() - other);
            this->setY(this->getY() - other);
            return *this;
        }
        Vector2D<T> operator*=(T other) {
            this->setX(this->getX() * other);
            this->setY(this->getY() * other);
            return *this;
        }
        Vector2D<T> operator/=(T other) {
            this->setX(this->getX() / other);
            this->setY(this->getY() / other);
            return *this;
        }
        friend std::ostream &operator<<(std::ostream &os, const Vector2D<T> &vector) {
            os << "(" << vector.getX() << ", " << vector.getY() << ")";
            return os;
        }
    };
}