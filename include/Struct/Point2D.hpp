#pragma once

#include "Point1D.hpp"
#include <iostream>

namespace Point {
    template<typename T>
class D2 : public Point::D1<T> {
    private:
        T m_Y = 0;
    protected:

    public:
        D2(void) {
        }

        D2(T x, T y) {
            this->setX(x);
            this->setY(y);
        }

        D2(const Point::D2<T> &other) {
            this->setX(other.getX());
            this->setY(other.getY());
        }

        ~D2(void) {
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

        Point::D2<T> *copy(void) const {
            return new Point::D2<T>(this->getX(), this->getY());
        }

        void move(T x, T y) {
            this->setX(this->getX() + x);
            this->setY(this->getY() + y);
        }

        Point::D2<T> &operator=(const Point::D2<T> &other) {
            this->setX(other.getX());
            this->setY(other.getY());
            return *this;
        }

        Point::D2<T> operator+(const Point::D2<T> &other) const {
            return Point::D2<T>(this->getX() + other.getX(), this->getY() + other.getY());
        }

        Point::D2<T> operator-(const Point::D2<T> &other) const {
            return Point::D2<T>(this->getX() - other.getX(), this->getY() - other.getY());
        }

        Point::D2<T> operator*(const Point::D2<T> &other) const {
            return Point::D2<T>(this->getX() * other.getX(), this->getY() * other.getY());
        }

        Point::D2<T> operator/(const Point::D2<T> &other) const {
            return Point::D2<T>(this->getX() / other.getX(), this->getY() / other.getY());
        }
        bool operator==(const Point::D2<T> &other) const {
            return this->getX() == other.getX() && this->getY() == other.getY();
        }
        bool operator!=(const Point::D2<T> &other) const {
            return this->getX() != other.getX() || this->getY() != other.getY();
        }
        bool operator<(const Point::D2<T> &other) const {
            return this->getX() < other.getX() && this->getY() < other.getY();
        }
        bool operator>(const Point::D2<T> &other) const {
            return this->getX() > other.getX() && this->getY() > other.getY();
        }
        bool operator<=(const Point::D2<T> &other) const {
            return this->getX() <= other.getX() && this->getY() <= other.getY();
        }
        bool operator>=(const Point::D2<T> &other) const {
            return this->getX() >= other.getX() && this->getY() >= other.getY();
        }
        Point::D2<T> operator+=(const Point::D2<T> &other) {
            this->setX(this->getX() + other.getX());
            this->setY(this->getY() + other.getY());
            return *this;
        }
        Point::D2<T> operator-=(const Point::D2<T> &other) {
            this->setX(this->getX() - other.getX());
            this->setY(this->getY() - other.getY());
            return *this;
        }
        Point::D2<T> operator*=(const Point::D2<T> &other) {
            this->setX(this->getX() * other.getX());
            this->setY(this->getY() * other.getY());
            return *this;
        }
        Point::D2<T> operator/=(const Point::D2<T> &other) {
            this->setX(this->getX() / other.getX());
            this->setY(this->getY() / other.getY());
            return *this;
        }
        Point::D2<T> operator+=(T other) {
            this->setX(this->getX() + other);
            this->setY(this->getY() + other);
            return *this;
        }
        Point::D2<T> operator-=(T other) {
            this->setX(this->getX() - other);
            this->setY(this->getY() - other);
            return *this;
        }
        Point::D2<T> operator*=(T other) {
            this->setX(this->getX() * other);
            this->setY(this->getY() * other);
            return *this;
        }
        Point::D2<T> operator/=(T other) {
            this->setX(this->getX() / other);
            this->setY(this->getY() / other);
            return *this;
        }
        friend std::ostream &operator<<(std::ostream &os, const Point::D2<T> &Point) {
            os << "(" << Point.getX() << ", " << Point.getY() << ")";
            return os;
        }
    };
}