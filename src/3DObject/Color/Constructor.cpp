#include "../../../include/3DObject/Color.hpp"

Object::Color::Color(void) {

}

Object::Color::Color(const SDL_Color &color) {
    this->init(color);
}

Object::Color::Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255) {
    this->init(SDL_Color{red, green, blue, alpha});
}

Object::Color::~Color(void) {

}

void Object::Color::init(const SDL_Color &color) {
    if (color == nullptr) {
        throw std::invalid_argument("Color cannot be nullptr");
    }
    this->setColor(color);
}

static Object::Color &Object::Color::lerp(const Object::Color &color1, const Object::Color &color2, float t) {
    return new Object::Color(
            static_cast<Uint8>(color1.getRed() + (color2.getRed() - color1.getRed()) * t),
            static_cast<Uint8>(color1.getGreen() + (color2.getGreen() - color1.getGreen()) * t),
            static_cast<Uint8>(color1.getBlue() + (color2.getBlue() - color1.getBlue()) * t),
            static_cast<Uint8>(color1.getAlpha() + (color2.getAlpha() - color1.getAlpha()) * t)
    );
}