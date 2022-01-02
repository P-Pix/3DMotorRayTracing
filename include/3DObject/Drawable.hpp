#pragma once

#include <iostream>
#include <SDL2/SDL.h>

#include "Point3D.hpp"

namespace Object {
    class Drawable {
    private:
        Object::Point3D<int> m_Position;
        SDL_Renderer *m_Renderer = nullptr;

        void init(Object::Point3D<int> *position, SDL_Renderer *renderer);

    public:
        Drawable(void);
        Drawable(int x, int y, int z, SDL_Renderer *renderer);
        Drawable(Object::Point3D<int> position, SDL_Renderer *renderer);
        ~Drawable(void);
        void setPosition(int x, int y, int z);
        void setPosition(Object::Point3D<int> *position);
        void setRenderer(SDL_Renderer *renderer);
        Object::Point3D<int> *getPosition(void);
        SDL_Renderer *getRenderer(void) const;
        virtual void draw(void) = 0;
        void move(int x, int y, int z);
        void move(Object::Point3D<int> *position);
    };
}