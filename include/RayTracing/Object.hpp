#pragma once

#include <iostream>
#include "../Struct/Point3D.hpp"

class Object {
protected:
    Point::D3<int> m_Position = {0, 0, 0};

public:
    Object(void);
    Object(Point::D3<int> *position);

    void setPosition(Point::D3<int> *position);
    void setPosition(int x, int y, int z);

    Point::D3<int> getPosition(void);

    void movePosition(Point::D3<int> *position);
    void movePosition(int x, int y, int z);
};