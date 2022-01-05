#include "../../../include/RayTracing/Camera.hpp"

Camera::Camera(void) {

}

Camera::Camera(int angleX, int angleY, int angleZ, int x, int y, int z) {
    this->init(angleX, angleY, angleZ, new Point::D3<int>(x, y, z));
}

Camera::Camera(int angleX, int angleY, int angleZ, Point::D3<int> *position) {
    this->init(angleX, angleY, angleZ, position);
}

Camera::~Camera(void) {

}

void Camera::init(int angleX, int angleY, int angleZ, Point::D3<int> *position) {
    this->setAngleX(angleX);
    this->setAngleY(angleY);
    this->setAngleZ(angleZ);
    this->setPosition(position);
}