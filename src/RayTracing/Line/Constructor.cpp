#include "../../../include/RayTracing/Line.hpp"

RayTracing::Line::Line(void) {
}

RayTracing::Line::Line(RayTracing::Line *line) {
    this->m_Start = *line->getStart();
    this->m_End = *line->getEnd();
}

RayTracing::Line::Line(int startX, int startY, int startZ, int endX, int endY, int endZ) {
    this->m_Start.set(startX, startY, startZ);
    this->m_End.set(endX, endY, endZ);
}

RayTracing::Line::Line(const Point::D3<int> *start, const Point::D3<int> *end) {
    this->m_Start = *start;
    this->m_End = *end;
}

RayTracing::Line::~Line(void) {
}