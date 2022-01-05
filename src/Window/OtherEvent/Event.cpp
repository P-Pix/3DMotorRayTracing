#include "../../../include/Window/OtherEvent.hpp"

void Window::OtherEvent::event(void) {
    if (this->getEvent()->type == SDL_QUIT) {
        this->m_Quit = true;
    }
}