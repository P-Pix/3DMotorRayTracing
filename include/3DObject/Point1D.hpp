#pragma once

#include <iostream>
#include <cmath>

namespace Object {
    template <typename T>
    class Point1D {
    private:
        T m_X = 0;
    protected:
    public:
        Point1D(void) {

        }
        Point1D(T x) {
            this->m_X = x;
        }
        Point1D(const Object::Point1D<T>& v) {
            this->m_X = v.getX();
        }
        ~Point1D(void) {

        }
        T getX(void) const {
            return this->m_X;
        }
        void setX(T x) {
            this->m_X = x;
        }
        float length(void) const {
            return sqrt(this->m_X * this->m_X);
        }
        void normalize(void) {
            float length = this->length();
            this->setX(this->getX() / length);
        }
        Object::Point1D<T> *copy(void) const {
            return &Point1D<T>(this->m_X);
        }
        Object::Point1D<T>& operator=(const Object::Point1D<T>& v) {
            this->m_X = v.getX();
            return *this;
        }
        Object::Point1D<T>& operator+=(const Object::Point1D<T>& v) {
            this->m_X += v.getX();
            return *this;
        }
        Object::Point1D<T>& operator-=(const Object::Point1D<T>& v) {
            this->m_X -= v.getX();
            return *this;
        }
        Object::Point1D<T>& operator*=(const Object::Point1D<T>& v) {
            this->m_X *= v.getX();
            return *this;
        }
        Object::Point1D<T>& operator/=(const Object::Point1D<T>& v) {
            this->m_X /= v.getX();
            return *this;
        }
        Object::Point1D<T>& operator+=(T x) {
            this->m_X += x;
            return *this;
        }
        Object::Point1D<T>& operator-=(T x) {
            this->m_X -= x;
            return *this;
        }
        Object::Point1D<T>& operator*=(T x) {
            this->m_X *= x;
            return *this;
        }
        Object::Point1D<T>& operator/=(T x) {
            this->m_X /= x;
            return *this;
        }
        bool operator==(const Object::Point1D<T>& v) const {
            return this->m_X == v.getX();
        }
        bool operator!=(const Object::Point1D<T>& v) const {
            return this->m_X != v.getX();
        }
        bool operator<(const Object::Point1D<T>& v) const {
            return this->m_X < v.getX();
        }
        bool operator>(const Object::Point1D<T>& v) const {
            return this->m_X > v.getX();
        }
        bool operator<=(const Object::Point1D<T>& v) const {
            return this->m_X <= v.getX();
        }
        bool operator>=(const Object::Point1D<T>& v) const {
            return this->m_X >= v.getX();
        }
        bool operator==(T x) const {
            return this->m_X == x;
        }
        bool operator!=(T x) const {
            return this->m_X != x;
        }
        bool operator<(T x) const {
            return this->m_X < x;
        }
        bool operator>(T x) const {
            return this->m_X > x;
        }
        bool operator<=(T x) const {
            return this->m_X <= x;
        }
        bool operator>=(T x) const {
            return this->m_X >= x;
        }
        friend std::ostream& operator<<(std::ostream& os, const Point1D<T>& v) {
            os << v.getX();
            return os;
        }
    };
}