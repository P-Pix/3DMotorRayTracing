#include "../../../include/Window/Mouse.hpp"

Window::Mouse::Mouse(void) {
}

Window::Mouse::Mouse(const SDL_Event *src, SDL_Window *window) {
    this->setEvent(src);
    this->setWindow(window);
    SDL_GetMouseState(&this->m_X, &this->m_Y);
}

Window::Mouse::~Mouse(void) {
}