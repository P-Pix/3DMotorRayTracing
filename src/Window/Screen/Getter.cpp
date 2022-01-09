#include "../../../include/Window/Screen.hpp"

bool Window::Screen::isOpen(void) {
    return !this->m_OtherEvent.getQuit();
}

SDL_Renderer *Window::Screen::getRenderer(void) const {
    return this->m_Renderer;
}

SDL_Window *Window::Screen::getWindow(void) const {
    return this->m_Window;
}