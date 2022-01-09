#pragma once

#include <iostream>
#include <SDL2/SDL.h>

#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "OtherEvent.hpp"

namespace Window {
class Screen : public Window::Event{
    private:
        SDL_Window *m_Window = nullptr;
        SDL_Renderer *m_Renderer = nullptr;
        SDL_Event m_Event;

        Window::Keyboard m_Keyboard;
        Window::Mouse m_Mouse;
        Window::OtherEvent m_OtherEvent;

        std::string m_Name = "Window";

        void init(const char *Name);

        bool initSDL(void);

        bool createWindow(const char *title, int x, int y, int w, int h);

        bool createRenderer(void);

        void destroyWindow(void);

        void destroyRenderer(void);

    public:

        Screen(void);

        Screen(const char *Name);

        ~Screen(void);

        bool restart(void);

        bool isOpen(void);

        SDL_Renderer *getRenderer(void) const;

        SDL_Window *getWindow(void) const;

        void event(void);
    };
}