#include "../../../include/3DObject/Color.hpp"

int main(int argc, char **argv) {
    Object::Color color;
    color.setRedF(0.5);
    color.setGreenF(0.5);
    color.setBlueF(0.5);
    color.setAlphaF(0.5);
    return EXIT_SUCCESS;
}