#include "../../../include/3DObject/Model.hpp"

Object::Model::Model(void) {

}
Object::Model::Model(Object::Model *model) {
    this->init(model->getPosition(), model->getRenderer());
}

Object::Model::Model(int x, int y, int z) {
    this->init(new Point::D3<int>(x, y, z), nullptr);
}

Object::Model::Model(int x, int y, int z, SDL_Renderer* renderer) {
    this->init(new Point::D3<int>(x, y, z), renderer);
}

Object::Model::~Model(void) {

}

void Object::Model::init(Point::D3<int> *position, SDL_Renderer *renderer) {
    this->setPosition(position);
    this->setRenderer(renderer);
}

void Object::Model::init(Point::D3<int> position, SDL_Renderer *renderer) {
    this->setPosition(&position);
    this->setRenderer(renderer);
}