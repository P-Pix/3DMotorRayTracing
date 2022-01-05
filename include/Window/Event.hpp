#pragma once

#include <iostream>
#include <SDL2/SDL.h>

namespace Window {
    class Event {
    private:
        SDL_Event m_Event;
        SDL_Window* m_Window;

    protected:

    public:
        Event(void);
        Event(const SDL_Event *event, SDL_Window* window);
        ~Event(void);
        void setEvent(const SDL_Event *event);
        void setWindow(SDL_Window* window);
        bool poll(void);
        SDL_Event* getEvent(void);
    };
}