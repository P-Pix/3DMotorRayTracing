#include "../../../include/3DObject/Drawable.hpp"

Object::Drawable::Drawable(void) {

}

Object::Drawable::Drawable(int x, int y, int z, SDL_Renderer *renderer) {
    this->init(new Point::D3<int>(x, y, z), renderer);
}

Object::Drawable::Drawable(Point::D3<int> position, SDL_Renderer *renderer) {
    this->init(&position, renderer);
}

void Object::Drawable::init(Point::D3<int> *position, SDL_Renderer *renderer) {
    this->setPosition(position);
    this->setRenderer(renderer);
}

Object::Drawable::~Drawable(void) {
}