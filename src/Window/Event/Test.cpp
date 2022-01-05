#include "../../../include/Window/Event.hpp"

int main(int argc, char** argv) {
    std::cout << "Size RAM : " << sizeof(Window::Event) << std::endl;
    Window::Event event;
    event.poll();
    return EXIT_SUCCESS;
}