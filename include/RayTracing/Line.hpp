#pragma once

#include "../Struct/Point3D.hpp"

namespace RayTracing {
    class Line {
    private:
        Point::D3<int> m_Start;
        Point::D3<int> m_End;

    protected:
    public:
        Line(void);
        Line(const Point::D3<int> *start, const Point::D3<int> *end);
        Line(RayTracing::Line *line);
        Line(int startX, int startY, int startZ, int endX, int endY, int endZ);
        ~Line(void);

        void setStart(const Point::D3<int> *start);
        void setStart(int startX, int startY, int startZ);
        void setEnd(const Point::D3<int> *end);
        void setEnd(int endX, int endY, int endZ);

        Point::D3<int> *getStart(void);
        Point::D3<int> *getEnd(void);

        float getLength(void);
    };
}