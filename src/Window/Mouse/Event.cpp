#include "../../../include/Window/Mouse.hpp"

void Window::Mouse::event(void) {
    if (this->getEvent()->type == SDL_MOUSEMOTION) {
        this->m_X = this->getEvent()->motion.x;
        this->m_Y = this->getEvent()->motion.y;
    } else if (this->getEvent()->type == SDL_MOUSEBUTTONDOWN) {
        if (this->getEvent()->button.button == SDL_BUTTON_LEFT) {
            this->m_LeftButton = true;
        } else if (this->getEvent()->button.button == SDL_BUTTON_RIGHT) {
            this->m_RightButton = true;
        } else if (this->getEvent()->button.button == SDL_BUTTON_MIDDLE) {
            this->m_MiddleButton = true;
        }
    } else if (this->getEvent()->type == SDL_MOUSEBUTTONUP) {
        if (this->getEvent()->button.button == SDL_BUTTON_LEFT) {
            this->m_LeftButton = false;
        } else if (this->getEvent()->button.button == SDL_BUTTON_RIGHT) {
            this->m_RightButton = false;
        } else if (this->getEvent()->button.button == SDL_BUTTON_MIDDLE) {
            this->m_MiddleButton = false;
        }
    }
}