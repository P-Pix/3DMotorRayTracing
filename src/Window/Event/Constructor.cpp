#include "../../../include/Window/Event.hpp"

Window::Event::Event(void) {
    this->m_Event = SDL_Event();
    this->m_Window = nullptr;
}

Window::Event::Event(const SDL_Event *event, SDL_Window* window) {
    this->setEvent(event);
    this->setWindow(window);
}

Window::Event::~Event(void) {
}

bool Window::Event::poll(void) {
    return SDL_PollEvent(&this->m_Event);
}