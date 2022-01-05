#include "../../../include/Window/Keyboard.hpp"

void Window::Keyboard::event(void) {
    this->resetList();
    for (int i = 0; i < KEY_COUNT; i++) {
        if (this->getEvent()->type == SDL_KEYDOWN) {
            if (this->m_KeyList[i] == this->getEvent()->key.keysym.sym) {
                this->m_KeyPressed[i] = true;
                std::cout << "Key = " << i << std::endl;
                return;
            }
        }
    }
}

int Window::Keyboard::getKey(void) {
    for (int i = 0; i < KEY_COUNT; i++) {
        if (this->m_KeyPressed[i]) {
            this->m_KeyPressed[i] = false;
            return i;
        }
    }
    return -1;
}

SDL_Keycode *Window::Keyboard::getKeyList(void) {
    return this->m_KeyList;
}