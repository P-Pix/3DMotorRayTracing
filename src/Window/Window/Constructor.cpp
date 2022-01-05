#include "../../../include/Window/Screen.hpp"

Window::Screen::Screen(void) {
    this->init("Window");
}

Window::Screen::Screen(const char *Name) {
    this->init(Name);
}

Window::Screen::~Screen(void) {
    this->destroyRenderer();
    this->destroyWindow();
}

void Window::Screen::init(const char *Name) {
    this->initSDL();
    this->createWindow(Name, 0, 0, 800, 600);
    this->createRenderer();
    this->m_Keyboard.setWindow(this->m_Window);
    this->m_Keyboard.setEvent(&this->m_Event);
    this->m_Mouse.setWindow(this->m_Window);
    this->m_Mouse.setEvent(&this->m_Event);
    this->m_OtherEvent.setWindow(this->m_Window);
    this->m_OtherEvent.setEvent(&this->m_Event);
}

bool Window::Screen::initSDL(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool Window::Screen::createWindow(const char *title, int x, int y, int w, int h) {
    this->m_Window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN);
    if (this->m_Window == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool Window::Screen::createRenderer(void) {
    this->m_Renderer = SDL_CreateRenderer(this->m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (this->m_Renderer == nullptr) {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void Window::Screen::destroyWindow(void) {
    SDL_DestroyWindow(this->m_Window);
}

void Window::Screen::destroyRenderer(void) {
    SDL_DestroyRenderer(this->m_Renderer);
}

bool Window::Screen::restart(void) {
    this->destroyRenderer();
    this->destroyWindow();
    this->createWindow("Window", 0, 0, 800, 600);
    this->createRenderer();
    return true;
}