#pragma once

#include <iostream>

class POV
{
private:

public:
    POV();
    ~POV();
    void setPOV(int x, int y, int z);
    int getX();
    int getY();
    int getZ();
    void setX(int x);
    void setY(int y);
    void setZ(int z);
    void printPOV();

    static
};