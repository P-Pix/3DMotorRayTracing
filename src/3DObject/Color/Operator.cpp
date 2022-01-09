#include "../../../include/3DObject/Color.hpp"

Object::Color Object::Color::operator+(const Object::Color &color) const {
    return Color(this->getRed() + color.getRed(), this->getGreen() + color.getGreen(),
                 this->getBlue() + color.getBlue(), this->getAlpha() + color.getAlpha());
}

Object::Color Object::Color::operator-(const Object::Color &color) const {
    return Color(this->getRed() - color.getRed(), this->getGreen() - color.getGreen(),
                 this->getBlue() - color.getBlue(), this->getAlpha() - color.getAlpha());
}

Object::Color Object::Color::operator*(const Object::Color &color) const {
    return Color(this->getRed() * color.getRed(), this->getGreen() * color.getGreen(),
                 this->getBlue() * color.getBlue(), this->getAlpha() * color.getAlpha());
}

Object::Color Object::Color::operator/(const Object::Color &color) const {
    return Color(this->getRed() / color.getRed(), this->getGreen() / color.getGreen(),
                 this->getBlue() / color.getBlue(), this->getAlpha() / color.getAlpha());
}

Object::Color Object::Color::operator*(float value) const {
    return Color(this->getRed() * value, this->getGreen() * value, this->getBlue() * value,
                 this->getAlpha() * value);
}

Object::Color Object::Color::operator/(float value) const {
    return Color(this->getRed() / value, this->getGreen() / value, this->getBlue() / value,
                 this->getAlpha() / value);
}

Object::Color &Object::Color::operator+=(const Object::Color &color) {
    this->setRed(this->getRed() + color.getRed());
    this->setGreen(this->getGreen() + color.getGreen());
    this->setBlue(this->getBlue() + color.getBlue());
    this->setAlpha(this->getAlpha() + color.getAlpha());
    return *this;
}

Object::Color &Object::Color::operator-=(const Object::Color &color) {
    this->setRed(this->getRed() - color.getRed());
    this->setGreen(this->getGreen() - color.getGreen());
    this->setBlue(this->getBlue() - color.getBlue());
    this->setAlpha(this->getAlpha() - color.getAlpha());
    return *this;
}

Object::Color &Object::Color::operator*=(const Object::Color &color) {
    this->setRed(this->getRed() * color.getRed());
    this->setGreen(this->getGreen() * color.getGreen());
    this->setBlue(this->getBlue() * color.getBlue());
    this->setAlpha(this->getAlpha() * color.getAlpha());
    return *this;
}

Object::Color &Object::Color::operator/=(const Object::Color &color) {
    this->setRed(this->getRed() / color.getRed());
    this->setGreen(this->getGreen() / color.getGreen());
    this->setBlue(this->getBlue() / color.getBlue());
    this->setAlpha(this->getAlpha() / color.getAlpha());
    return *this;
}

Object::Color &Object::Color::operator*=(float value) {
    this->setRed(this->getRed() * value);
    this->setGreen(this->getGreen() * value);
    this->setBlue(this->getBlue() * value);
    this->setAlpha(this->getAlpha() * value);
    return *this;
}

Object::Color &Object::Color::operator/=(float value) {
    this->setRed(this->getRed() / value);
    this->setGreen(this->getGreen() / value);
    this->setBlue(this->getBlue() / value);
    this->setAlpha(this->getAlpha() / value);
    return *this;
}