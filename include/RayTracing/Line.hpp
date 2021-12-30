#pragma once

#include "../3DObject/Point3D.hpp"

namespace RayTracing {
    class Line {
    private:
        Object::Point3D<int> m_Start;
        Object::Point3D<int> m_End;

    protected:
    public:
        Line(void);
        Line(const Object::Point3D<int> *start, const Object::Point3D<int> *end);
        Line(RayTracing::Line *line);
        Line(int startX, int startY, int startZ, int endX, int endY, int endZ);
        ~Line(void);

        void setStart(const Object::Point3D<int> *start);
        void setStart(int startX, int startY, int startZ);
        void setEnd(const Object::Point3D<int> *end);
        void setEnd(int endX, int endY, int endZ);

        Object::Point3D<int> *getStart(void);
        Object::Point3D<int> *getEnd(void);

        float getLength(void);
    };
}