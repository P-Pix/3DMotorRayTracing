#include "../../../include/Window/Event.hpp"

SDL_Event *Window::Event::getEvent(void) {
    return &this->m_Event;
}