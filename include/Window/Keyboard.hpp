#pragma once

#include "Event.hpp"

#define KEY_COUNT 71

namespace Window {
    class Keyboard : public Window::Event {
    private:
        SDL_Keycode m_KeyList[KEY_COUNT];
        bool m_KeyPressed[KEY_COUNT];

        void resetList(void);

    public:
        Keyboard(void);
        Keyboard(SDL_Event* event, SDL_Window* window);
        ~Keyboard(void);
        void initList(void);
        void event(void);
        int getKey(void);

        SDL_Keycode *getKeyList(void);
    };
}