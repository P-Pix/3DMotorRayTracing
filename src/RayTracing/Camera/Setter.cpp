#include "../../../include/RayTracing/Camera.hpp"

void Camera::setAngleX(int angle) {
    this->m_AngleX = angle % 360;
}

void Camera::setAngleY(int angle) {
    this->m_AngleY = angle % 360;
}

void Camera::setAngleZ(int angle) {
    this->m_AngleZ = angle % 360;
}