#include "../../../include/RayTracing/Screen.hpp"

int Screen::getWidth(void) {
    return this->m_Width;
}

int Screen::getHeight(void) {
    return this->m_Height;
}

SDL_Window* Screen::getWindow(void) {
    return this->m_Window;
}