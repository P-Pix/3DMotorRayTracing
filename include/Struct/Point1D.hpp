#pragma once

#include <iostream>
#include <cmath>

namespace Point {
    template <typename T>
    class D1 {
    private:
        T m_X = 0;
    protected:
    public:
        D1(void) {

        }
        D1(T x) {
            this->m_X = x;
        }
        D1(const Point::D1<T>& v) {
            this->m_X = v.getX();
        }
        ~D1(void) {

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
        Point::D1<T> *copy(void) const {
            return &D1<T>(this->m_X);
        }
        Point::D1<T>& operator=(const Point::D1<T>& v) {
            this->m_X = v.getX();
            return *this;
        }
        Point::D1<T>& operator+=(const Point::D1<T>& v) {
            this->m_X += v.getX();
            return *this;
        }
        Point::D1<T>& operator-=(const Point::D1<T>& v) {
            this->m_X -= v.getX();
            return *this;
        }
        Point::D1<T>& operator*=(const Point::D1<T>& v) {
            this->m_X *= v.getX();
            return *this;
        }
        Point::D1<T>& operator/=(const Point::D1<T>& v) {
            this->m_X /= v.getX();
            return *this;
        }
        Point::D1<T>& operator+=(T x) {
            this->m_X += x;
            return *this;
        }
        Point::D1<T>& operator-=(T x) {
            this->m_X -= x;
            return *this;
        }
        Point::D1<T>& operator*=(T x) {
            this->m_X *= x;
            return *this;
        }
        Point::D1<T>& operator/=(T x) {
            this->m_X /= x;
            return *this;
        }
        bool operator==(const Point::D1<T>& v) const {
            return this->m_X == v.getX();
        }
        bool operator!=(const Point::D1<T>& v) const {
            return this->m_X != v.getX();
        }
        bool operator<(const Point::D1<T>& v) const {
            return this->m_X < v.getX();
        }
        bool operator>(const Point::D1<T>& v) const {
            return this->m_X > v.getX();
        }
        bool operator<=(const Point::D1<T>& v) const {
            return this->m_X <= v.getX();
        }
        bool operator>=(const Point::D1<T>& v) const {
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
        friend std::ostream& operator<<(std::ostream& os, const D1<T>& v) {
            os << v.getX();
            return os;
        }
    };
}