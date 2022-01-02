#include "../../../include/3DObject/Drawable.hpp"

Object::Point3D<int> *Object::Drawable::getPosition(void) {
    return &this->m_Position;
}

SDL_Renderer *Object::Drawable::getRenderer(void) const {
    return this->m_Renderer;
}