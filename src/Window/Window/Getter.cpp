#include "../../../include/Window/Screen.hpp"

bool Window::Screen::isOpen() {
    return !this->m_OtherEvent.getQuit();
}