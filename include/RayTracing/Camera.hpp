#pragma once

#include "Object.hpp"

class Camera : public Object {
private:
    int m_AngleX = 0;
    int m_AngleY = 0;
    int m_AngleZ = 0;

    void init(int angleX, int angleY, int angleZ, Point::D3<int> *position);

public:
    Camera(void);
    Camera(int angleX, int angleY, int angleZ, Point::D3<int> *position);
    Camera(int angleX, int angleY, int angleZ, int x, int y, int z);
    ~Camera(void);

    int getAngleX(void);
    int getAngleY(void);
    int getAngleZ(void);

    void setAngleX(int angle);
    void setAngleY(int angle);
    void setAngleZ(int angle);

    void moveAngleX(int angle);
    void moveAngleY(int angle);
    void moveAngleZ(int angle);
};