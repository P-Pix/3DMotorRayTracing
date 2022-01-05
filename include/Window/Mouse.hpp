#pragma once

#include "Event.hpp"

#include <iostream>
#include <SDL2/SDL.h>

namespace Window {
    class Mouse : public Window::Event {
    private:
        bool m_LeftButton = false;
        bool m_RightButton = false;
        bool m_MiddleButton = false;

        int m_X;
        int m_Y;

    protected:

    public:
        Mouse(void);
        Mouse(const SDL_Event *event, SDL_Window* window);
        ~Mouse(void);

        int getX(void) const;
        int getY(void) const;
        bool getLeftButton(void) const;
        bool getRightButton(void) const;
        bool getMiddleButton(void) const;

        void event(void);

        /// @return true if the button is pressed
        bool leftButton(void);

        /// @return true if the button is pressed
        bool rightButton(void);
    };
}