#include "../../../include/RayTracing/Screen.hpp"

void Screen::setWidth(int width) {
    this->m_Width = width;
}

void Screen::setHeight(int height) {
    this->m_Height = height;
}

void Screen::setWindow(SDL_Window* window) {
    this->m_Window = window;
}