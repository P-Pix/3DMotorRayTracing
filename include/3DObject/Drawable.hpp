#pragma once

#include <iostream>
#include <SDL2/SDL.h>

#include "../Struct/Point3D.hpp"

namespace Object {
    class Drawable {
    private:
        Point::D3<int> m_Position;
        SDL_Renderer *m_Renderer = nullptr;

        void init(Point::D3<int> *position, SDL_Renderer *renderer);

    public:
        Drawable(void);
        Drawable(int x, int y, int z, SDL_Renderer *renderer);
        Drawable(Point::D3<int> position, SDL_Renderer *renderer);
        ~Drawable(void);
        void setPosition(int x, int y, int z);
        void setPosition(Point::D3<int> *position);
        void setRenderer(SDL_Renderer *renderer);
        Point::D3<int> getPosition(void);
        SDL_Renderer *getRenderer(void) const;
        virtual void draw(void) = 0;
        void move(int x, int y, int z);
        void move(Point::D3<int> *position);
    };
}