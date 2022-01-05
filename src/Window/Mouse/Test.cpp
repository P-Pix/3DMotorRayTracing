#include "../../../include/Window/Mouse.hpp"

int main(int argc, char **argv) {
    std::cout << "Size RAM : " << sizeof(Window::Mouse) << std::endl;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,
                                          SDL_WINDOW_SHOWN);
    SDL_Event event;
    Window::Mouse mouse(&event, window);
    while (!mouse.getLeftButton()) {
        mouse.poll();
        mouse.event();
        if (mouse.getLeftButton()) {
            std::cout << "Left button pressed" << std::endl;
        }
        std::cout << "X : " << mouse.getX() << " Y : " << mouse.getY() << std::endl;
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}