#include "../../../include/Window/Keyboard.hpp"

int main(int argc, char **argv) {
    std::cout << "Size RAM : " << sizeof(Window::Keyboard) << std::endl;
    SDL_Window *window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Event event;
    Window::Keyboard keyboard(&event, window);
    for (int i = 0; i < 100; i++) {
        keyboard.poll();
        keyboard.event();
        SDL_Delay(50);
    }
    return EXIT_SUCCESS;
}