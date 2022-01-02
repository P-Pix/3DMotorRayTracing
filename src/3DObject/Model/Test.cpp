#include "../../../include/3DObject/Model.hpp"

int main(int argc, char **argv) {
    SDL_Window *window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Object::Model model(0, 0, 0, renderer);
    return EXIT_SUCCESS;
}