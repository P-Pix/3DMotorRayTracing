#include "../../../include/RayTracing/Object.hpp"

Object::Object(void) {

}

Object::Object(Point::D3<int> *position) {
    this->setPosition(position);
}

void Object::setPosition(Point::D3<int> *position) {
    this->m_Position = *position;
}

void Object::setPosition(int x, int y, int z) {
    this->m_Position.set(x, y, z);
}

Point::D3<int> Object::getPosition(void) {
    return this->m_Position;
}

void Object::movePosition(Point::D3<int> *position) {
    this->setPosition(new Point::D3<int>(this->m_Position.getX() + position->getX(),
                                         this->m_Position.getY() + position->getY(),
                                         this->m_Position.getZ() + position->getZ()));
}

void Object::movePosition(int x, int y, int z) {
    this->movePosition(new Point::D3<int>(x, y, z));
}