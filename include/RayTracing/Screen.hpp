#pragma once

#include "Object.hpp"
#include <SDL2/SDL.h>

class Screen : public Object {
private:
    int m_Width = 0;
    int m_Height = 0;
    SDL_Window* m_Window = nullptr;

    void init(Point::D3<int> *position, int width, int height, SDL_Window* window);

public:
    Screen(void);
    Screen(Point::D3<int> *position, int width, int height, SDL_Window* window);
    Screen(int x, int y, int z, int width, int height, SDL_Window* window);
    ~Screen(void);

    int getWidth(void);
    int getHeight(void);
    SDL_Window* getWindow(void);

    void setWidth(int width);
    void setHeight(int height);
    void setWindow(SDL_Window* window);
};