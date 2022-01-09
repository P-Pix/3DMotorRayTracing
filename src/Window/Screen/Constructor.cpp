#include "../../../include/Window/Screen.hpp"

Window::Screen::Screen(void) {
    this->init(this->m_Name);
}

Window::Screen::Screen(const char *Name) {
    this->m_Name = Name;
    this->init(this->m_Name);
}

Window::Screen::~Screen(void) {
    this->destroyRenderer();
    this->destroyWindow();
}

void Window::Screen::init(const char *Name) {
    this->initSDL();
    this->createWindow(Name, 0, 0, 800, 600);
    this->createRenderer();
    this->set(&this->m_Event, this->m_Window);
    this->m_Keyboard.set(&this->m_Event, this->m_Window);
    this->m_Mouse.set(&this->m_Event, this->m_Window);
    this->m_OtherEvent.set(&this->m_Event, this->m_Window);
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
    if (!this->initSDL()) {
        return false;
    }
    if (!this->createWindow(this->m_Name, 0, 0, 800, 600)) {
        return false;
    }
    if (!this->createRenderer()) {
        return false;
    }
    return true;
}

void Window::Screen::event(void) {
    this->poll();
    if (this->m_Event.type == SDL_MOUSEMOTION) {
        this->m_Mouse.event();
    } else if (this->m_Event.type == SDL_KEYDOWN) {
        this->m_Keyboard.event();
    } else {
        this->m_OtherEvent.event();
    }
}