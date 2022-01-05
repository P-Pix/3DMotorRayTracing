#include "../../../include/3DObject/Drawable.hpp"

void Object::Drawable::setPosition(int x, int y, int z) {
    this->m_Position.setX(x);
    this->m_Position.setY(y);
    this->m_Position.setZ(z);
}

void Object::Drawable::setPosition(Point::D3<int> *position) {
    this->m_Position = *position;
}

void Object::Drawable::setRenderer(SDL_Renderer *renderer) {
    this->m_Renderer = renderer;
}

void Object::Drawable::move(int x, int y, int z) {
    this->setPosition(this->m_Position.getX() + x, this->m_Position.getY() + y, this->m_Position.getZ() + z);
}

void Object::Drawable::move(Point::D3<int> *position) {
    this->setPosition(this->m_Position.getX() + position->getX(), this->m_Position.getY() + position->getY(),
                      this->m_Position.getZ() + position->getZ());
}