#include "../../../include/RayTracing/Camera.hpp"

void Camera::moveAngleX(int angle) {
    this->setAngleX(this->getAngleX() + angle);
}

void Camera::moveAngleY(int angle) {
    this->setAngleY(this->getAngleY() + angle);
}

void Camera::moveAngleZ(int angle) {
    this->setAngleZ(this->getAngleZ() + angle);
}