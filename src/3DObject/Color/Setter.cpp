#include "../../../include/3DObject/Color.hpp"

void Object::Color::Color::setRed(Uint8 red) {
    this->m_Color.r = red;
}

void Object::Color::Color::setGreen(Uint8 green) {
    this->m_Color.g = green;
}

void Object::Color::Color::setBlue(Uint8 blue) {
    this->m_Color.b = blue;
}

void Object::Color::Color::setAlpha(Uint8 alpha) {
    this->m_Color.a = alpha;
}

void Object::Color::Color::setRedF(float red) {
    if (red < 0.0f) {
        std::cerr << "Error: Red value cannot be negative." << std::endl;
        return;
    } else if (red > 1.0f) {
        std::cerr << "Error: Red value cannot be greater than 1." << std::endl;
        return;
    }
    this->m_Color.r = static_cast<Uint8>(red * 255);
}

void Object::Color::Color::setGreenF(float green) {
    if (green < 0.0f) {
        std::cerr << "Error: Green value cannot be negative." << std::endl;
        return;
    } else if (green > 1.0f) {
        std::cerr << "Error: Green value cannot be greater than 1." << std::endl;
        return;
    }
    this->m_Color.g = static_cast<Uint8>(green * 255);
}

void Object::Color::Color::setBlueF(float blue) {
    if (blue < 0.0f) {
        std::cerr << "Error: Blue value cannot be negative." << std::endl;
        return;
    } else if (blue > 1.0f) {
        std::cerr << "Error: Blue value cannot be greater than 1." << std::endl;
        return;
    }
    this->m_Color.b = static_cast<Uint8>(blue * 255);
}

void Object::Color::Color::setAlphaF(float alpha) {
    if (alpha < 0.0f) {
        std::cerr << "Error: Alpha value cannot be negative." << std::endl;
        return;
    } else if (alpha > 1.0f) {
        std::cerr << "Error: Alpha value cannot be greater than 1." << std::endl;
        return;
    }
    this->m_Color.a = static_cast<Uint8>(alpha * 255);
}

void Object::Color::Color::setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255) {
    this->setRed(red);
    this->setGreen(green);
    this->setBlue(blue);
    this->setAlpha(alpha);
}

void Object::Color::Color::setColor(const SDL_Color &color) {
    this->m_Color = color;
}

void Object::Color::Color::setColor(float red, float green, float blue, float alpha = 1.0f) {
    this->setRedF(red);
    this->setGreenF(green);
    this->setBlueF(blue);
    this->setAlphaF(alpha);
}
