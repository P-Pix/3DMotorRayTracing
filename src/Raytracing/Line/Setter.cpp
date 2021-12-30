#include "../../../include/RayTracing/Line.hpp"

void RayTracing::Line::setStart(const Object::Point3D<int> *start) {
    this->m_Start = *start;
}

void RayTracing::Line::setStart(int startX, int startY, int startZ) {
    this->m_Start.set(startX, startY, startZ);
}

void RayTracing::Line::setEnd(const Object::Point3D<int> *end) {
    this->m_End = *end;
}

void RayTracing::Line::setEnd(int endX, int endY, int endZ) {
    this->m_End.set(endX, endY, endZ);
}