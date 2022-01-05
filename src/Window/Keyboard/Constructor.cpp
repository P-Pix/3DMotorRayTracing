#include "../../../include/Window/Keyboard.hpp"

Window::Keyboard::Keyboard(void) {
    this->initList();
}

Window::Keyboard::Keyboard(SDL_Event* event, SDL_Window* window) {
    this->setWindow(window);
    this->setEvent(event);
    this->initList();
}

Window::Keyboard::~Keyboard(void) {
}

void Window::Keyboard::initList(void) {
    this->m_KeyList[0] = (SDLK_a);
    this->m_KeyList[1] = (SDLK_b);
    this->m_KeyList[2] = (SDLK_c);
    this->m_KeyList[3] = (SDLK_d);
    this->m_KeyList[4] = (SDLK_e);
    this->m_KeyList[5] = (SDLK_f);
    this->m_KeyList[6] = (SDLK_g);
    this->m_KeyList[7] = (SDLK_h);
    this->m_KeyList[8] = (SDLK_i);
    this->m_KeyList[9] = (SDLK_j);
    this->m_KeyList[10] = (SDLK_k);
    this->m_KeyList[11] = (SDLK_l);
    this->m_KeyList[12] = (SDLK_m);
    this->m_KeyList[13] = (SDLK_n);
    this->m_KeyList[14] = (SDLK_o);
    this->m_KeyList[15] = (SDLK_p);
    this->m_KeyList[16] = (SDLK_q);
    this->m_KeyList[17] = (SDLK_r);
    this->m_KeyList[18] = (SDLK_s);
    this->m_KeyList[19] = (SDLK_t);
    this->m_KeyList[20] = (SDLK_u);
    this->m_KeyList[21] = (SDLK_v);
    this->m_KeyList[22] = (SDLK_w);
    this->m_KeyList[23] = (SDLK_x);
    this->m_KeyList[24] = (SDLK_y);
    this->m_KeyList[25] = (SDLK_z);
    this->m_KeyList[26] = (SDLK_0);
    this->m_KeyList[27] = (SDLK_1);
    this->m_KeyList[28] = (SDLK_2);
    this->m_KeyList[29] = (SDLK_3);
    this->m_KeyList[30] = (SDLK_4);
    this->m_KeyList[31] = (SDLK_5);
    this->m_KeyList[32] = (SDLK_6);
    this->m_KeyList[33] = (SDLK_7);
    this->m_KeyList[34] = (SDLK_8);
    this->m_KeyList[35] = (SDLK_9);
    this->m_KeyList[36] = (SDLK_KP_0);
    this->m_KeyList[37] = (SDLK_KP_1);
    this->m_KeyList[38] = (SDLK_KP_2);
    this->m_KeyList[39] = (SDLK_KP_3);
    this->m_KeyList[40] = (SDLK_KP_4);
    this->m_KeyList[41] = (SDLK_KP_5);
    this->m_KeyList[42] = (SDLK_KP_6);
    this->m_KeyList[43] = (SDLK_KP_7);
    this->m_KeyList[44] = (SDLK_KP_8);
    this->m_KeyList[45] = (SDLK_KP_9);
    this->m_KeyList[46] = (SDLK_KP_PERIOD);
    this->m_KeyList[47] = (SDLK_KP_DIVIDE);
    this->m_KeyList[48] = (SDLK_KP_MULTIPLY);
    this->m_KeyList[49] = (SDLK_KP_MINUS);
    this->m_KeyList[50] = (SDLK_KP_PLUS);
    this->m_KeyList[51] = (SDLK_KP_ENTER);
    this->m_KeyList[52] = (SDLK_KP_EQUALS);
    this->m_KeyList[53] = (SDLK_UP);
    this->m_KeyList[54] = (SDLK_DOWN);
    this->m_KeyList[55] = (SDLK_RIGHT);
    this->m_KeyList[56] = (SDLK_LEFT);
    this->m_KeyList[57] = (SDLK_INSERT);
    this->m_KeyList[58] = (SDLK_HOME);
    this->m_KeyList[59] = (SDLK_END);
    this->m_KeyList[60] = (SDLK_PAGEUP);
    this->m_KeyList[61] = (SDLK_PAGEDOWN);
    this->m_KeyList[62] = (SDLK_F1);
    this->m_KeyList[63] = (SDLK_F2);
    this->m_KeyList[64] = (SDLK_F3);
    this->m_KeyList[65] = (SDLK_F4);
    this->m_KeyList[66] = (SDLK_F5);
    this->m_KeyList[67] = (SDLK_F6);
    this->m_KeyList[68] = (SDLK_F7);
    this->m_KeyList[69] = (SDLK_F8);
    this->m_KeyList[70] = (SDLK_F9);

    this->resetList();
}

void Window::Keyboard::resetList(void) {
    for (int i = 0; i < 71; i ++) {
        this->m_KeyPressed[i] = false;
    }
}