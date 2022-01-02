#include "../../../include/3DObject/Drawable.hpp"

Object::Drawable::Drawable(void) {

}

Object::Drawable::Drawable(int x, int y, int z, SDL_Renderer *renderer) {
    this->init(new Object::Point3D<int>(x, y, z), renderer);
}

Object::Drawable::Drawable(Object::Point3D<int> position, SDL_Renderer *renderer) {
    this->init(&position, renderer);
}

void Object::Drawable::init(Object::Point3D<int> *position, SDL_Renderer *renderer) {
    this->setPosition(position);
    this->setRenderer(renderer);
}

Object::Drawable::~Drawable(void) {
}