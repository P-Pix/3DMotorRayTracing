#pragma once

#include "Drawable.hpp"

template<typename T>
class Triangle : public Drawable {
private:
    Point::D3<T> p1, p2, p3;

public:
    Triangle(void) {
        p1 = Point::D3<T>(0, 0, 0);
        p2 = Point::D3<T>(0, 0, 0);
        p3 = Point::D3<T>(0, 0, 0);
        this->setPosition(Point::D3<T>(0, 0, 0));
    }

    Triangle(Point::D3<T> p1, Point::D3<T> p2, Point::D3<T> p3, SDL_Renderer *renderer) : Drawable(
            Point::D3<int>(0, 0, 0), *renderer) {
        this->setP1(p1);
        this->setP2(p2);
        this->setP3(p3);
        this->setPosition((p1.getX() + p2.getX() + p3.getX()) / 3, (p1.getY() + p2.getY() + p3.getY()) / 3,
                          (p1.getZ() + p2.getZ() + p3.getZ()) / 3);
    }

    ~Triangle(void) {

    }

    Point::D3<T> getP1(void) {
        return this->p1;
    }

    Point::D3<T> getP2(void) {
        return this->p2;
    }

    Point::D3<T> getP3(void) {
        return this->p3;
    }

    void setP1(Point::D3<T> p1) {
        this->p1 = p1;
    }

    void setP2(Point::D3<T> p2) {
        this->p2 = p2;
    }

    void setP3(Point::D3<T> p3) {
        this->p3 = p3;
    }

    void setP1(T x, T y, T z) {
        this->p1 = Point::D3<T>(x, y, z);
    }

    void setP2(T x, T y, T z) {
        this->p2 = Point::D3<T>(x, y, z);
    }

    void setP3(T x, T y, T z) {
        this->p3 = Point::D3<T>(x, y, z);
    }

    /**
     * Draw the triangle surface
     */
    void draw(void) override {
    }

    Triangle<T> operator+(Triangle<T> t) {
        return Triangle<T>(this->p1 + t.p1, this->p2 + t.p2, this->p3 + t.p3);
    }

    Triangle<T> operator-(Triangle<T> t) {
        return Triangle<T>(this->p1 - t.p1, this->p2 - t.p2, this->p3 - t.p3);
    }

    Triangle<T> operator*(T s) {
        return Triangle<T>(this->p1 * s, this->p2 * s, this->p3 * s);
    }

    Triangle<T> operator/(T s) {
        return Triangle<T>(this->p1 / s, this->p2 / s, this->p3 / s);
    }

    bool operator==(Triangle<T> t) {
        return (this->p1 == t.p1 && this->p2 == t.p2 && this->p3 == t.p3);
    }

    bool operator!=(Triangle<T> t) {
        return (this->p1 != t.p1 || this->p2 != t.p2 || this->p3 != t.p3);
    }

    void operator+=(Triangle<T> t) {
        this->p1 += t.p1;
        this->p2 += t.p2;
        this->p3 += t.p3;
    }

    void operator-=(Triangle<T> t) {
        this->p1 -= t.p1;
        this->p2 -= t.p2;
        this->p3 -= t.p3;
    }

    void operator*=(T s) {
        this->p1 *= s;
        this->p2 *= s;
        this->p3 *= s;
    }

    void operator/=(T s) {
        this->p1 /= s;
        this->p2 /= s;
        this->p3 /= s;
    }

    void operator=(Triangle<T> t) {
        this->p1 = t.p1;
        this->p2 = t.p2;
        this->p3 = t.p3;
    }

    void operator=(Point::D3<T> p) {
        this->p1 = p;
        this->p2 = p;
        this->p3 = p;
    }

    void operator=(T s) {
        this->p1 = Point::D3<T>(s, s, s);
        this->p2 = Point::D3<T>(s, s, s);
        this->p3 = Point::D3<T>(s, s, s);
    }

    void operator+=(Point::D3<T> p) {
        this->p1 += p;
        this->p2 += p;
        this->p3 += p;
    }

    void operator-=(Point::D3<T> p) {
        this->p1 -= p;
        this->p2 -= p;
        this->p3 -= p;
    }

    void operator*=(T s) {
        this->p1 *= s;
        this->p2 *= s;
        this->p3 *= s;
    }

    void operator/=(T s) {
        this->p1 /= s;
        this->p2 /= s;
        this->p3 /= s;
    }

    friend std::ostream &operator<<(std::ostream &os, const Triangle &triangle) {
        os << "Triangle: " << std::endl;
        os << "P1: " << triangle.p1 << std::endl;
        os << "P2: " << triangle.p2 << std::endl;
        os << "P3: " << triangle.p3 << std::endl;
        return os;
    }
};