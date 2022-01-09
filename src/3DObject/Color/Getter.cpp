#include "../../../include/3DObject/Color.hpp"

Uint8 Object::Color::Color::getRed(void) const {
    return this->m_Color.r;
}

Uint8 Object::Color::Color::getGreen(void) const {
    return this->m_Color.g;
}

Uint8 Object::Color::Color::getBlue(void) const {
    return this->m_Color.b;
}

Uint8 Object::Color::Color::getAlpha(void) const {
    return this->m_Color.a;
}

SDL_Color getSDLColor(void){
    return this->m_Color;
}

float Object::Color::Color::getRedF(void) const {
    return this->m_Color.r / 255.0f;
}

float Object::Color::Color::getGreenF(void) const {
    return this->m_Color.g / 255.0f;
}

float Object::Color::Color::getBlueF(void) const {
    return this->m_Color.b / 255.0f;
}

float Object::Color::Color::getAlphaF(void) const {
    return this->m_Color.a / 255.0f;
}