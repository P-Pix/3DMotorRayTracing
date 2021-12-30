#pragma once

#include <iostream>
#include <SDL2/SDL.h>

#include "Vector3D.hpp"

namespace Object {
    class Drawable {
    private:
        Object::Vector3D<int> m_Position;
        SDL_Renderer *m_Renderer = nullptr;

    public:
        Drawable(void);
        Drawable(int x, int y, int z, SDL_Renderer *renderer);
        Drawable(Object::Vector3D<int> position, SDL_Renderer *renderer);
        ~Drawable(void);
        void setPosition(int x, int y, int z);
        void setPosition(Object::Vector3D<int> position);
        void setRenderer(SDL_Renderer *renderer);
        Object::Vector3D<int> getPosition(void);
        SDL_Renderer *getRenderer(void);
        virtual void draw(void) = 0;
    };
}