#include <iostream>

#include "../../../include/Window/Screen.hpp"

int main(int argc, char *argv[]) {
    std::cout << "Test Window" << std::endl;
    std::cout << "Size RAM : " << sizeof(Window::Window) << std::endl;
    Window::Screen window;
    std::cout << "Window created" << std::endl;
    std::cout << "Window created" << std::endl;
    SDL_RenderPresent(window.getRenderer());
    std::cout << "Window created" << std::endl;
    SDL_Delay(5000);
    SDL_Quit();
    return EXIT_SUCCESS;
}