#include "../../../include/Window/Event.hpp"

void Window::Event::setEvent(const SDL_Event *event) {
    this->m_Event = *event;
}

void Window::Event::setWindow(SDL_Window *window) {
    this->m_Window = window;
}