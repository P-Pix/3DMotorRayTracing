#include "../../../include/RayTracing/Screen.hpp"

Screen::Screen(void) {

}

Screen::Screen(Point::D3<int> *position, int width, int height, SDL_Window *window) {
    this->init(position, width, height, window);
}

Screen::Screen(int x, int y, int z, int width, int height, SDL_Window* window) {
    this->init(new Point::D3<int>(x, y, z), width, height, window);
}

Screen::~Screen(void) {

}

void Screen::init(Point::D3<int> *position, int width, int height, SDL_Window* window) {
    this->setPosition(position);
    this->setWidth(width);
    this->setHeight(height);
    this->setWindow(window);
}