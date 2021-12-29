#pragma once

#include <iostream>

namespace Structure {
    template <typename T>
    class Vector1D {
    private:
        T m_X = 0;
    protected:
    public:
        Vector1D(void) {

        }
        Vector1D(T x) {
            this->m_X = x;
        }
        Vector1D(const Vector1D<T>& v) {
            this->m_X = v.getX();
        }
        ~Vector1D(void) {

        }
        T getX(void) const {
            return this->m_X;
        }
        void setX(T x) {
            this->m_X = x;
        }
        Vector1D<T>& operator=(const Vector1D<T>& v) {
            this->m_X = v.getX();
            return *this;
        }
        Vector1D<T>& operator+=(const Vector1D<T>& v) {
            this->m_X += v.getX();
            return *this;
        }
        Vector1D<T>& operator-=(const Vector1D<T>& v) {
            this->m_X -= v.getX();
            return *this;
        }
        Vector1D<T>& operator*=(const Vector1D<T>& v) {
            this->m_X *= v.getX();
            return *this;
        }
        Vector1D<T>& operator/=(const Vector1D<T>& v) {
            this->m_X /= v.getX();
            return *this;
        }
        Vector1D<T>& operator+=(T x) {
            this->m_X += x;
            return *this;
        }
        Vector1D<T>& operator-=(T x) {
            this->m_X -= x;
            return *this;
        }
        Vector1D<T>& operator*=(T x) {
            this->m_X *= x;
            return *this;
        }
        Vector1D<T>& operator/=(T x) {
            this->m_X /= x;
            return *this;
        }
        bool operator==(const Vector1D<T>& v) const {
            return this->m_X == v.getX();
        }
        bool operator!=(const Vector1D<T>& v) const {
            return this->m_X != v.getX();
        }
        bool operator<(const Vector1D<T>& v) const {
            return this->m_X < v.getX();
        }
        bool operator>(const Vector1D<T>& v) const {
            return this->m_X > v.getX();
        }
        bool operator<=(const Vector1D<T>& v) const {
            return this->m_X <= v.getX();
        }
        bool operator>=(const Vector1D<T>& v) const {
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
        friend std::ostream& operator<<(std::ostream& os, const Vector1D<T>& v) {
            os << v.getX();
            return os;
        }
    };
}