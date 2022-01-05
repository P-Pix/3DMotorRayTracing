#include "../../../include/RayTracing/Line.hpp"

Point::D3<int> *RayTracing::Line::getStart(void) {
    return &this->m_Start;
}

Point::D3<int> *RayTracing::Line::getEnd(void) {
    return &this->m_End;
}

float RayTracing::Line::getLength(void) {
    return sqrt(pow(this->m_End.getX() - this->m_Start.getX(), 2) + pow(this->m_End.getY() - this->m_Start.getY(), 2) + pow(this->m_End.getZ() - this->m_Start.getZ(), 2));
}