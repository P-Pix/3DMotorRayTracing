#include "../../../include/Window/Mouse.hpp"

int Window::Mouse::getX(void) const {
    return this->m_X;
}

int Window::Mouse::getY(void) const {
    return this->m_Y;
}

bool Window::Mouse::getLeftButton() const {
    return this->m_LeftButton;
}

bool Window::Mouse::getRightButton(void) const {
    return this->m_RightButton;
}

bool Window::Mouse::getMiddleButton(void) const {
    return this->m_MiddleButton;
}